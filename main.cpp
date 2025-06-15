#include "forecast_runner.hpp"
#include "service/mysql_service.hpp"
#include "util/csv_manager.hpp"

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
//    ForecastRunner runner;
//    runner.run(argc, argv);
    try {
        MysqlService mysql_service;
        std::vector<RowData> data = load_csv("data/ndq_20000101_20250606.csv");
//        mysql_service.insert_history_data("ndq", data);
//        mysql_service.insert_history_data("spx", data);
        std::vector<RowData> results = mysql_service.load_history_data("ndq", "2020-01-01", "2020-01-05");
        for(auto r : results) {
            std::cout << r << std::endl;
        }
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Fatal exception: " << ex.what() << "\n";
        return 1;
    }
}

