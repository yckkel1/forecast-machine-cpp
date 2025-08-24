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
    double get_alpha() const { return alpha; }
    double get_beta() const { return beta; }
    const std::string& get_method() const { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
