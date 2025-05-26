#include "mean_forecaster.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include "util/forecaster_registry.hpp"

namespace {
    const bool registered = [] {
        get_forecaster_registry()["mean"] = [] (const std::vector<std::string>& args) {
            return std::make_unique<MeanForecaster>();
        };
        return true;
    } ();
}

std::vector<PlotData> MeanForecaster::forecast(const std::vector<RowData>& data, int steps_ahead) {
    // returns a vector of length steps_ahead, where each element is mean of data
    if(data.empty() || steps_ahead <= 0) {
        return {};
    }
    std::vector<PlotData> plotData;
    
    std::chrono::year_month_day last_date = data.back().getDate();
    
    double sum = std::accumulate(data.begin(), data.end(), 0.0, [](double sum, const RowData& data) {
        return sum + data.getClose();
    });
    
    double mean = sum / static_cast<double>(data.size());
    
    for(int step = 1; step <= steps_ahead; step++) {
        plotData.emplace_back(
            std::chrono::year_month_day(std::chrono::sys_days(last_date) + std::chrono::days(step)), mean
        );
    }
    
    return plotData;
}
