#pragma once

#include "util/data_utils.hpp"
#include <cstdint>

class RowData {
private:
    std::chrono::year_month_day date;
    double open;
    double high;
    double low;
    double close;
    uint64_t volume;
public:
    RowData(std::chrono::year_month_day date, double open, double high, double low, double close, uint64_t volume)
    : date(date), open(open), high(high), low(low), close(close), volume(volume) {}
    
    RowData(std::string date, double open, double high, double low, double close, uint64_t volume)
    : date(util::parse_date_string(date)), open(open), high(high), low(low), close(close), volume(volume) {}
    
    std::chrono::year_month_day getDate() const { return date; }
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    uint64_t getVolume() const { return volume; }
    
    friend std::ostream& operator<< (std::ostream& os, const RowData& row_data);
};
