#include "forecast_runner.hpp"
#include "util/csv_manager.hpp"
#include "util/arg_parser.hpp"
#include "util/data_utils.hpp"
#include "util/error_evaluator.hpp"
#include "util/forecaster_registry.hpp"
#include "util/constants.hpp"
#include "service/mysql_service.hpp"

#include <iostream>
#include <memory>
#include <cmath>

void ForecastRunner::run(int argc, const char* argv[]) {
    ArgParser arg_parser;
    arg_parser.parse(argc, argv);
    
    std::string data_source = arg_parser.get(constants::params::DATA_SOURCE);
    std::vector<RowData> data;
    if(data_source == constants::datasource::CSV) {
        data = load_csv(arg_parser.get(constants::params::INPUT_FILE_PATH));
    }
    else {
        std::string start_date = arg_parser.get(constants::params::START_DATE);
        std::cout << "start_date: " << start_date << std::endl;
        std::string end_date = arg_parser.get(constants::params::END_DATE);
        std::cout << "end_date: " << end_date << std::endl;
        std::string ticker = arg_parser.get(constants::params::TICKER);
        MysqlService mysql_service;
        data = mysql_service.load_history_data(ticker, start_date, end_date);
    }

    if (data.empty()) {
        throw std::runtime_error("Input CSV is empty.");
    }

    std::string method = arg_parser.get(constants::params::METHOD);
    std::unique_ptr<ForecastEngine> forecaster = create_forecaster(method, arg_parser);

    if (arg_parser.get(constants::operations::FORECAST) == constants::TRUE_VAL) {
        int steps_ahead = std::stoi(arg_parser.get(constants::params::STEPS_AHEAD));
        std::vector<PlotData> forecasted = forecaster->forecast(data, steps_ahead);

        std::string out_path = util::output_file_path(forecasted, method);
        write_csv(forecasted, out_path);
        std::cout << "Forecast written to: " << out_path << "\n";
    }

    if (arg_parser.get(constants::operations::EVALUATE) == constants::TRUE_VAL) {
        double ratio = std::stod(arg_parser.get(constants::params::TRAIN_RATIO));
        int split_pos = static_cast<int>(ratio * data.size());

        if (split_pos <= 0 || split_pos >= data.size()) {
            throw std::runtime_error("Invalid train_ratio: not enough data to split.");
        }

        std::vector<RowData> train(data.begin(), data.begin() + split_pos);
        std::vector<RowData> test(data.begin() + split_pos, data.end());

        std::vector<PlotData> forecasted = forecaster->forecast(train, static_cast<int>(test.size()));
        std::cout << "forecasted size: " << forecasted.size() << std::endl;

        std::vector<PlotData> actual;
        if (arg_parser.get(constants::params::METHOD) == constants::methods::EWMA) {
            // ewma is not applicable for predicting
            for (const RowData& r : train) {
                actual.emplace_back(r.getDate(), r.getClose());
            }
        }
        else {
            for (const RowData& r : test) {
                actual.emplace_back(r.getDate(), r.getClose());
            }
        }

        double mae = ErrorEvaluator::mean_absolute_error(forecasted, actual);
        double rmse = ErrorEvaluator::root_mean_squared_error(forecasted, actual);

        std::cout << "Evaluation Metrics:\n";
        std::cout << "MAE: " << mae << "\n";
        std::cout << "RMSE: " << rmse << "\n";
    }
}

