#pragma once

#include "dto/plot_data.hpp"
#include <vector>

class ErrorEvaluator {
public:
    // Compares forecasted prices with actual prices
    static double mean_absolute_error(const std::vector<PlotData>& forecast,
                                      const std::vector<PlotData>& actual);

    static double root_mean_squared_error(const std::vector<PlotData>& forecast,
                                          const std::vector<PlotData>& actual);
};
