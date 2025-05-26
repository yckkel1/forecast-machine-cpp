#pragma once

#include "forecast_engine.hpp"

class MeanForecaster : public ForecastEngine{
public:
    MeanForecaster() {
        forecast_method = "mean";
    }
    std::string const get_forecast_method() { return forecast_method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
