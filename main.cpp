#include "forecast_runner.hpp"
#include "service/mysql_service.hpp"
#include "util/csv_manager.hpp"

int main(int argc, const char * argv[]) {
    ForecastRunner runner;
    runner.run(argc, argv);
}

