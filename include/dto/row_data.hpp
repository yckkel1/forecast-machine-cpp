#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>

class RowData {
private:
    std::chrono::year_month_day date;
    double open;
    double high;
    double low;
    double close;
    unsigned long volume;
public:
    RowData(std::chrono::year_month_day date, double open, double high, double low, double close, unsigned long volume)
    : date(date), open(open), high(high), low(low), close(close), volume(volume) {}
    
    RowData(std::string date, double open, double high, double low, double close, unsigned long volume)
    : date(fromStringToDate(date)), open(open), high(high), low(low), close(close), volume(volume) {}
    
    std::chrono::year_month_day getDate() const { return date; }
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    unsigned long getVolume() const { return volume; }
    
    static std::chrono::year_month_day fromStringToDate (const std::string& date_string) {
        std::istringstream ss(date_string);
        std::tm tm = {};
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (ss.fail()) {
            throw std::runtime_error("Invalid date string: " + date_string);
        }
        return std::chrono::year{tm.tm_year + 1900} /
        std::chrono::month{static_cast<unsigned>(tm.tm_mon + 1)} /
        std::chrono::day{static_cast<unsigned>(tm.tm_mday)};
    }
};
