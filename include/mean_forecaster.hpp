#pragma once

#include "forecast_engine.hpp"
#include "dto/plot_data.hpp"

class MeanForecaster : public ForecastEngine{
public:
    MeanForecaster() {
        forecast_method = "mean_forecast";
    }
    std::string const get_forecast_method() { return forecast_method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
