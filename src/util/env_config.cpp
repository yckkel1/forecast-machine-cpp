#include "util/env_config.hpp"
#include "dotenv.h"

Dotenv EnvConfig::env;

void EnvConfig::init() {
    if(!env.load(".env")) {
        throw std::runtime_error("Failed to load .env");
    }
}

std::string EnvConfig::get(const std::string& key) {
    return env.get(key);
}

