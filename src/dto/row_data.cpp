#pragma once

#include <string>
#include <chrono>
#include <iostream>

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

    std::chrono::year_month_day getDate() const { return date; }
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    unsigned long getVolume() const { return volume; }
};

