#pragma once

#include "forecast_engine.hpp"
#include <array>

class LinearForecaster : public ForecastEngine {
public:
    LinearForecaster() {
        forecast_method = "linear";
    }
    std::string const get_forecast_method() { return forecast_method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
    std::array<double, 2> get_params(const std::vector<RowData>& data);
};
