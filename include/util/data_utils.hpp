#pragma once

#include <iostream>
#include <chrono>
#include <vector>

namespace util {

    std::chrono::year_month_day parse_date_string(const std::string& date_string);

    std::string date_to_string(const std::chrono::year_month_day& ymd);

    std::unordered_map<std::string, int> parse_csv_headers (const std::string& header_line);

    std::vector<std::string> split_csv_line (const std::string& line);

    std::string trim(const std::string& str);
}
