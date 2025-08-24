#pragma once

#include "forecast_engine.hpp"

class MeanForecaster : public ForecastEngine{
public:
    MeanForecaster() {
        method = "mean";
    }
    const std::string& get_method() const { return method; }
    std::vector<PlotData> forecast(const std::vector<RowData>& data, int steps_ahead) override;
};
