#include "util/error_evaluator.hpp"
#include <numeric>
#include <cmath>

namespace {
    void validate_input(const std::vector<PlotData>& forecast, const std::vector<PlotData>& actual) {
        if (forecast.empty() || forecast.size() != actual.size()) {
            throw std::runtime_error("Invalid error evaluation: forecast and actual vectors must be same size and non-empty");
        }
    }
}

double ErrorEvaluator::mean_absolute_error(const std::vector<PlotData>& forecast,
                                                  const std::vector<PlotData>& actual) {
    validate_input(forecast, actual);
    double error_sum = std::inner_product(forecast.begin(), forecast.end(), actual.begin(),
                                          0.0, std::plus<>(), [] (const PlotData& f, const PlotData& a) {
        return std::abs(f.getValue() - a.getValue());
    });
    return error_sum / forecast.size();
}

double ErrorEvaluator::root_mean_squared_error(const std::vector<PlotData>& forecast,
                               const std::vector<PlotData>& actual) {
    validate_input(forecast, actual);
    double error_sum = std::inner_product(forecast.begin(), forecast.end(), actual.begin(),
                                          0.0, std::plus<>(), [] (const PlotData& f, const PlotData& a) {
        return pow((f.getValue() - a.getValue()), 2.0);
    });
    return std::sqrt(error_sum / forecast.size());
}

