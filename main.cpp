//
//  main.cpp
//  forecast-machine-cpp
//
//  Created by yuxin chen on 5/12/25.
//

#include <dto/row_data.hpp>
#include <iostream>
#include <filesystem>
#include "csv_loader.hpp"
#include <chrono>
#include <sstream>

int main(int argc, const char * argv[]) {
    // dynamically load csv on command line
    std::string file_path;
    if (argc > 1) {
        file_path = argv[1];
    } else {
        std::cerr << "Usage: " << argv[0] << " <path_to_csv>" << std::endl;
        return 1;
    }

    std::vector<RowData> series = load_csv(file_path);
    
    for(const RowData& data : series) {
        std::cout << data;
    }
    
    return 0;
}

