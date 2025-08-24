#pragma once

#include "forecast_engine.hpp"
#include <array>

class LinearForecaster : public ForecastEngine {
public:
    LinearForecaster() {
        method = "linear";
    }
    const std::string& get_method() const { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
    std::array<double, 2> get_params(const std::vector<RowData>& data);
};
