#include "csv_manager.hpp"
#include "dto/plot_data.hpp"
#include "dto/row_data.hpp"
#include "util/data_utils.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<RowData> load_csv(const std::string& file_path) {
//    std::cout << std::filesystem::current_path() << std::endl;
    std::vector<RowData> values;
    std::ifstream file(file_path);
    
    std::string header_line;
    if(std::getline(file, header_line)) {
        std::cout << "header: " << header_line << std::endl;
    }
    
    std::unordered_map<std::string, int> header_map = util::parse_csv_headers(header_line);
    
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row = util::split_csv_line(line);
        if(row.size() != header_map.size()) {
            throw new std::runtime_error("Invalid csv data");
        }
        
        try {
            RowData rowData (
                util::parse_date_string(row[header_map["Date"]]),
                std::stod(row[header_map["Open"]]),
                std::stod(row[header_map["High"]]),
                std::stod(row[header_map["Low"]]),
                std::stod(row[header_map["Close"]]),
                std::stoull(row[header_map["Volume"]])
            );
            values.push_back(rowData);
        } catch (const std::invalid_argument& e) {
            throw new std::runtime_error(std::string("Invalid input: ") + e.what());
        } catch (const std::out_of_range& e) {
            throw new std::runtime_error(std::string("Value out of range: ") + e.what());
        } catch (const std::runtime_error& e) {
            throw new std::runtime_error(std::string("Date parsing failed: ") + e.what());
        }
    }

    return values;
}

void write_csv(const std::vector<PlotData>& data, const std::string& filePath) {
    std::ofstream out(filePath);
    if(!out.is_open()) {
        throw std::runtime_error("Failed to open: " + filePath);
    }
    
    out << "date,value\n";
    for (const PlotData& entry : data) {
        out << util::date_to_string(entry.getDate()) << "," << entry.getValue() << "\n";
    }
    
    out.close();
}

