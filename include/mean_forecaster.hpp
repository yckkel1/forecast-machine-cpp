#pragma once

#include "forecast_engine.hpp"

class MeanForecaster : public ForecastEngine{
public:
    MeanForecaster() {
        method = "mean";
    }
    std::string const get_method() { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
