#include "forecast_runner.hpp"
#include "service/mysql_service.hpp"

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
//    ForecastRunner runner;
//    runner.run(argc, argv);
    try {
        MysqlService mysql_service;
        std::vector<RowData> results = mysql_service.load_data("ndq", "2020-01-01", "2020-01-05");
        std::cout << "success" << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Fatal exception: " << ex.what() << "\n";
        return 1;
    }
}

