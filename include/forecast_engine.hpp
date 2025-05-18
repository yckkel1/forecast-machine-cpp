#pragma once

#include <iostream>
#include <vector>

class ForecastEngine {
public:
    virtual std::vector<double> forecast(const std::vector<double>& data, int steps_ahed);
    virtual ~ForecastEngine() = default;
};
