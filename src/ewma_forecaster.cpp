#include "ewma_forecaster.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include "util/forecaster_registry.hpp"
#include "math.h"
#include <iomanip>

// formula: Et = alpha*Xt + (1-alpha)*Et-1

namespace {
    const bool registered = [] {
        get_forecaster_registry()["ewma"] = [] (const ArgParser& arg_parser) {
              return std::make_unique<EwmaForecaster>();
//            if (args.empty()) {
//                return std::make_unique<EwmaForecaster>();
//            }
//            else {
//                double alpha;
//                try {
//                    alpha = std::stod(args[0]);
//                } catch (std::exception& e) {
//                    throw std::runtime_error(std::string("Invalid alpha: ") + e.what());
//                }
//                
//                if(alpha < 0.0 || alpha > 1.0) {
//                    throw std::runtime_error("alpha must be between 0 and 1");
//                }
//                return std::make_unique<EwmaForecaster>(alpha);
//            }
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
