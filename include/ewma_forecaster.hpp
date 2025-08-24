#pragma once

#include "forecast_engine.hpp"

class EwmaForecaster : public ForecastEngine {
private:
    double alpha;
public:
    EwmaForecaster(double alpha) : alpha(alpha) { method = "ewma"; }
    double get_alpha() const { return alpha; }
    const std::string& get_method() const { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
