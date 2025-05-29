#pragma once

#include "forecast_engine.hpp"

class EwmaForecaster : public ForecastEngine {
private:
    double alpha;
public:
    EwmaForecaster(double alpha) : alpha(alpha) { method = "ewma"; }
    double const get_alpha() { return alpha; }
    std::string const get_method() { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
