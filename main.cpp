//
//  main.cpp
//  forecast-machine-cpp
//
//  Created by yuxin chen on 5/12/25.
//

#include <iostream>
#include <filesystem>
#include "csv_loader.hpp"

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
    std::string file_path;
    if (argc > 1) {
        file_path = argv[1];
    } else {
        std::cerr << "Usage: " << argv[0] << " <path_to_csv>" << std::endl;
        return 1;
    }

    std::vector<double> series = load_csv_column(file_path);

    if (series.empty()) {
        std::cerr << "Error: Failed to load data from " << std::endl;
        return 1;
    }

//    for (double close : series) {
//        std::cout << close << std::endl;
//    }
    
    return 0;
}

