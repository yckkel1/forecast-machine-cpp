#include "holt_forecaster.hpp"
#include "util/arg_parser.hpp"
#include "util/forecaster_registry.hpp"
#include "util/constants.hpp"

namespace {
    const bool registered = [] {
        get_forecaster_registry()["holt"] = [] (const ArgParser& arg_parser) {
            double alpha = std::stod(arg_parser.get(constants::params::ALPHA));
            double beta = std::stod(arg_parser.get(constants::params::BETA));
            return std::make_unique<HoltForecaster>(alpha, beta);
        };
        return true;
    } ();
}

std::vector<PlotData> HoltForecaster::forecast(const std::vector<RowData>& data, int steps_ahead) {
    // ℓₜ   = α * yₜ + (1 - α) * (ℓₜ₋₁ + bₜ₋₁)
    // bₜ   = β * (ℓₜ - ℓₜ₋₁) + (1 - β) * bₜ₋₁
    double alpha = get_alpha();
    double beta = get_beta();
    double level = data[0].getClose();
    double prevLevel = data[0].getClose();
    double trend = data[1].getClose() - data[0].getClose();
    double prevTrend = data[1].getClose() - data[0].getClose();
    for(std::size_t i = 1; i < data.size(); i++) {
        double curClose = data[i].getClose();
        prevLevel = level;
        level = alpha * curClose + (1 - alpha) * (level + trend);
        prevTrend = trend;
        trend = beta * (level - prevLevel) + (1 - beta) * prevTrend;
    }
    std::vector<PlotData> plotData;
    std::chrono::year_month_day last_date = data.back().getDate();
    int days = static_cast<int>(data.size());
    for(int step = 1; step <= steps_ahead; step++) {
        double value = level + step * trend;
        plotData.emplace_back(
            std::chrono::year_month_day(std::chrono::sys_days(last_date) + std::chrono::days(step)), value
        );
    }
    return plotData;
}
