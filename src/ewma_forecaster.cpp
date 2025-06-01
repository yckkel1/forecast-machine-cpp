#include "ewma_forecaster.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include "util/forecaster_registry.hpp"
#include "math.h"
#include <iomanip>
#include "util/constants.hpp"

// formula: Et = alpha*Xt + (1-alpha)*Et-1

namespace {
    const bool registered = [] {
        get_forecaster_registry()["ewma"] = [] (const ArgParser& arg_parser) {
            double alpha = std::stod(arg_parser.get(constants::params::ALPHA));
            return std::make_unique<EwmaForecaster>(alpha);
        };
        return true;
    } ();
}

std::vector<PlotData> EwmaForecaster::forecast(const std::vector<RowData>& data, int steps_ahead) {
    double alpha = get_alpha();
    std::vector<PlotData> plotData;
    plotData.emplace_back(data[0].getDate(), data[0].getClose());
    for (size_t i=1; i<data.size(); i++) {
        double value = alpha * plotData[i-1].getValue() + (1.0 - alpha) * data[i].getClose();
        plotData.emplace_back(data[i].getDate(), value);
    }
    return plotData;
}
