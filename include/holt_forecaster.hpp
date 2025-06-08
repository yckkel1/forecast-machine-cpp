#pragma once

#include "forecast_engine.hpp"

class HoltForecaster : public ForecastEngine {
private:
    double alpha;
    double beta;
public:
    HoltForecaster(double alpha, double beta) : alpha(alpha), beta(beta) {
        method = "holt";
    };
    double const get_alpha() { return alpha; }
    double const get_beta() { return beta; }
    std::string const get_method() { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
