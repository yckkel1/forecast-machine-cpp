//
//  main.cpp
//  forecast-machine-cpp
//
//  Created by yuxin chen on 5/12/25.
//

#include <iostream>
#include <filesystem>
#include "basic_forecast.hpp"

int main(int argc, const char * argv[]) {
    
    std::string file_path = "data/sp500_sample.csv";
    std::vector<double> series = load_csv_column(file_path);

    if (series.empty()) {
        std::cerr << "Error: Failed to load data from " << std::endl;
        return 1;
    }

    for (double close : series) {
        std::cout << close << std::endl;
    }
    
    return 0;
}

