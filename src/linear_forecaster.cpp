#include "linear_forecaster.hpp"
#include <cmath>
#include "util/forecaster_registry.hpp"

namespace {
    const bool registered = [] {
        get_forecaster_registry()["linear"] = [] (const ArgParser& arg_parser) {
            return std::make_unique<LinearForecaster>();
        };
        return true;
    } ();
}

std::vector<PlotData> LinearForecaster::forecast(const std::vector<RowData>& data, int steps_ahead) {
    if(data.empty() || steps_ahead <= 0) {
        return {};
    }
    std::vector<PlotData> plotData;
    std::array<double, 2> params = get_params(data);
    
    std::chrono::year_month_day last_date = data.back().getDate();
    int days = static_cast<int>(data.size());
    for(int step = 1; step <= steps_ahead; step++) {
        double value = (step + days) * params[0] + params[1];
        plotData.emplace_back(
            std::chrono::year_month_day(std::chrono::sys_days(last_date) + std::chrono::days(step)), value
        );
    }
    return plotData;
}

std::array<double, 2> LinearForecaster::get_params(const std::vector<RowData>& data) {
    std::array<double, 2> params; // params[0]: slope, params[1]: intercept
    double t = 0.0, t_squared = 0.0, y = 0.0, ty = 0.0;
    for(auto i=0; i<data.size(); i++) {
        double ti = static_cast<double>(i);
        t += ti;
        t_squared += pow(ti, 2.0);
        y += data[i].getClose();
        ty += ti * data[i].getClose();
    }
    double N = static_cast<double>(data.size());
    double denominator = (N * t_squared) - pow(t, 2.0);
    if (std::abs(denominator) < 1e-10) {
        throw std::runtime_error("Invalid Linear regression: zero or near-zero denominator.");
    }
    params[0] = ( (N * ty) - (t * y) ) / denominator;
    params[1] = ( y - (params[0]*t) ) / N;
    return params;
}
