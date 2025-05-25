//
//  main.cpp
//  forecast-machine-cpp
//
//  Created by yuxin chen on 5/12/25.
//

#include "dto/row_data.hpp"
#include <iostream>
#include <filesystem>
#include "csv_loader.hpp"
#include <chrono>
#include <sstream>
#include "mean_forecaster.hpp"
#include "util/data_utils.hpp"

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
    if (argc != 3) {
        std::cerr << "Usage: ./forecast_machine <file_path> <forecast_steps>\n";
        return 1;
    }

    std::string file_path = argv[1];
    int steps_ahead = std::stoi(argv[2]);

    std::vector<RowData> source_data = load_csv(file_path);
    
//    for(const RowData& data : source_data) {
//        std::cout << data.getDate();
//    }
    MeanForecaster meanForecaster;
    std::vector<PlotData> output_data = meanForecaster.forecast(source_data, steps_ahead);
    std::string begin_date = util::date_to_compact_string(output_data.begin()->getDate());
    std::string end_date = util::date_to_compact_string(output_data.back().getDate());
    
    std::string output_file_path =  "output/" + meanForecaster.get_forecast_method() + "_" + begin_date + "_" + end_date + ".csv";
    write_forecast_to_csv(output_data, output_file_path);
    
    return 0;
}

