// src/mean_forecaster.cpp

#include "forecast_engine.hpp"

#include <iostream>
#include <vector>
#include <numeric>

class MeanForecaster : public ForecastEngine{
public:
    std::vector<double> forecast(const std::vector<double>& data, int steps_ahead) override {
        // returns a vector of length steps_ahead, where each element is mean of data
        if(data.empty() || steps_ahead <= 0) {
            return {};
        }
        
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double mean = sum / static_cast<double>(data.size());
        return std::vector<double>(steps_ahead, mean);
    }
};
