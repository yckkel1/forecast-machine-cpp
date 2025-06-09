#include "util/env_config.hpp"
#include "dotenv.h"

void EnvConfig::init() {
    env = Dotenv();
    if(!env.load(".env")) {
        throw std::runtime_error("Failed to load .env");
    }
}

std::string EnvConfig::get(const std::string& key, const std::string& default_value = "") {
    return env.get(key, default_value);
}

