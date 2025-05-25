#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include "forecast_engine.hpp"

using ForecasterFactory = std::function<std::unique_ptr<ForecastEngine>()>;

std::unordered_map<std::string, ForecasterFactory>& get_forecaster_registry();

std::unique_ptr<ForecastEngine> create_forecaster(const std::string& forecast_method);
