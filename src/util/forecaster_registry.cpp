#include "util/forecaster_registry.hpp"
#include "util/arg_parser.hpp"

std::unordered_map<std::string, ForecasterFactory>& get_forecaster_registry() {
    static std::unordered_map<std::string, ForecasterFactory> registry;
    return registry;
}

std::unique_ptr<ForecastEngine> create_forecaster(const std::string& forecast_method, const ArgParser& arg_parser) {
    auto& registry = get_forecaster_registry();
    auto it = registry.find(forecast_method);
    if (it != registry.end()) {
        return it->second(arg_parser);
    }
    throw std::invalid_argument("Invalid forecast method: " + forecast_method);
}
