#pragma once

#include "forecast_engine.hpp"

class EwmaForecaster : public ForecastEngine {
private:
    double alpha;
public:
    EwmaForecaster() : alpha(0.3) { forecast_method = "ewma"; }
    EwmaForecaster(double alpha) : alpha(alpha) { forecast_method = "ewma"; }
    double const get_alpha() { return alpha; }
    std::string const get_forecast_method() { return forecast_method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
