#pragma once

#include "util/data_utils.hpp"
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace util {
    std::chrono::year_month_day parse_date_string(const std::string& date_string) {
        std::istringstream ss(date_string);
        std::tm tm = {};
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (ss.fail()) {
            throw std::runtime_error("Failed to parse date: " + date_string);
        }
        return std::chrono::year{tm.tm_year + 1900} /
               std::chrono::month{static_cast<unsigned>(tm.tm_mon + 1)} /
               std::chrono::day{static_cast<unsigned>(tm.tm_mday)};
    }

    std::string date_to_string(const std::chrono::year_month_day& ymd) {
        std::ostringstream ss;
        ss << static_cast<int>(ymd.year()) << "-";
        ss << static_cast<unsigned>(ymd.month()) << "-";
        ss << static_cast<unsigned>(ymd.day());
        return ss.str();
    }

    std::string date_to_compact_string(const std::chrono::year_month_day& ymd) {
        std::ostringstream ss;
        ss << static_cast<int>(ymd.year());
        ss << static_cast<unsigned>(ymd.month());
        ss << static_cast<unsigned>(ymd.day());
        return ss.str();
    }

    std::unordered_map<std::string, int> parse_csv_headers(const std::string& header_line) {
        std::unordered_map<std::string, int> header_map;
        int idx = 0;
        std::istringstream ss(header_line);
        std::string column_name;
        while(std::getline(ss, column_name, ',')) {
            header_map[trim(column_name)] = idx++;
        }
        return header_map;
    }

    std::vector<std::string> split_csv_line (const std::string& line) {
        std::vector<std::string> row;
        std::istringstream ss(line);
        std::string field;
        while(std::getline(ss, field, ',')) {
            row.push_back(trim(field));
        }
        return row;
    }

    std::string trim(const std::string& str) {
        auto begin = std::find_if_not(str.begin(), str.end(), ::isspace);
        auto end   = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
        if (begin >= end) return "";
        return std::string(begin, end);
    }
}

