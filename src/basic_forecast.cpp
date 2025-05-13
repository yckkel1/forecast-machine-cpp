#include "csv_loader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

constexpr int CLOSE = 4;  // Index of "Close" column in sp500.csv

std::vector<double> load_csv_column(const std::string& file_path) {
    std::vector<double> values;
    std::ifstream file(file_path);
    std::string line;

    bool is_first_line = true;
    while (std::getline(file, line)) {
        if (is_first_line) {
            is_first_line = false;
            continue;  // skip header
        }

        std::stringstream ss(line);
        std::string cell;
        int col_index = 0;

        while (std::getline(ss, cell, ',')) {
            if (col_index == CLOSE) {
                try {
                    values.push_back(std::stod(cell));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Warning: invalid number format in CSV: " << cell << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Warning: number out of range in CSV: " << cell << std::endl;
                }
                break;
            }
            ++col_index;
        }
    }

    return values;
}

