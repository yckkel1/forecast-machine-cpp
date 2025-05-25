#pragma once

#include <iostream>
#include <chrono>

class PlotData {
private:
    std::chrono::year_month_day date;
    double value;
public:
    PlotData(std::chrono::year_month_day date, double value): date(date), value(value) {}
    
    std::chrono::year_month_day getDate() const {return date; }
    double getValue() const { return value; }
};
