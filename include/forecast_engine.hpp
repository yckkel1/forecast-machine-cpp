#pragma once

#include "dto/plot_data.hpp"
#include "dto/row_data.hpp"

#include <iostream>
#include <vector>

class ForecastEngine {
protected:
    std::string method;
public:
    virtual std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) = 0;
    virtual ~ForecastEngine() = default;
};
