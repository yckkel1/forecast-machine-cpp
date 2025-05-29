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
#include "util/forecaster_registry.hpp"

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
    



    std::vector<RowData> source_data;
    try {
        source_data = load_csv(input_file_path);
    } catch (const std::exception& e) {
        std::cerr << "Failed to load CSV: " << e.what() << std::endl;
        return 1;
    }

    if (source_data.empty()) {
        std::cerr << "Input data is empty" << std::endl;
        return 1;
    }
    
//    for(const RowData& data : source_data) {
//        std::cout << data.getDate();
//    }
    std::unique_ptr<ForecastEngine> forecaster;
    std::vector<PlotData> output_data;
    try {
        forecaster = create_forecaster(forecast_method, args);
        std::cout << "Using forecast method: " << forecast_method << std::endl;
        output_data = forecaster->forecast(source_data, steps_ahead);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    
    try {
        std::string output_file_path = util::output_file_path(output_data, forecast_method);
        write_csv(output_data, output_file_path);
    } catch (const std::exception& e) {
        std::cerr << "Failed to write forecast to csv: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}

