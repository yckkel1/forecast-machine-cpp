#include "util/arg_parser.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "util/constants.hpp"
#include <algorithm>

void ArgParser::parse(int argc, const char* argv[]) {
    initialize_specs();
    if (argc < 4) {
        throw new std::invalid_argument("Required arguments: ./forecast_machine --data_source=... --method=... --evaluate(=true)/--forecast(=true)");
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto eq = arg.find('=');
        if (!arg.starts_with("--") || eq == std::string::npos) {
            throw std::invalid_argument("All arguments must be in --key(=value) format");
        }
        std::string key = arg.substr(2, eq-2);
        std::string value = arg.substr(eq+1);
        validate_and_store(key, value);
    }
    validate_and_set_default();
}

const std::string& ArgParser::get(const std::string& key) const {
    auto it = arg_map.find(key);
    if (it == arg_map.end()) {
        throw std::runtime_error("Missing required argument: --" + key);
    }
    return it->second;
}

void ArgParser::validate_and_store(const std::string& key, const std::string& value) {
    if (arg_specs.find(key) == arg_specs.end()) {
        throw std::runtime_error("Unknown argument: --" + key);
    }

    const ArgSpec& spec = arg_specs[key];
    switch (spec.type) {
        case ArgType::BOOLEAN: {
            if (value != constants::TRUE_VAL && value != constants::FALSE_VAL) {
                throw std::runtime_error("Boolean flag --" + key + " must be true or false");
            }
            break;
        }
        case ArgType::DOUBLE: {
            double val = std::stod(value);
            if (val < spec.double_min_value || val > spec.double_max_value) {
                throw std::runtime_error("Argument --" + key + " must be between " +
                    std::to_string(spec.double_min_value) + " and " + std::to_string(spec.double_max_value));
            }
            break;
        }
        case ArgType::INTEGER: {
            int val = std::stoi(value);
            if (val < spec.int_min_value || val > spec.int_max_value) {
                throw std::runtime_error("Argument --" + key + " must be between " +
                    std::to_string(spec.int_min_value) + " and " + std::to_string(spec.int_max_value));
            }
            break;
        }
        case ArgType::STRING:
            if (!spec.allowed_values.empty() && spec.allowed_values.find(value) == spec.allowed_values.end()) {
                throw std::runtime_error("Invalid value for --" + key);
            }
            break;
    }

    arg_map[key] = value;
}

void ArgParser::validate_and_set_default() {
    for(auto [key, spec] : arg_specs) {
        if(arg_map.find(key) == arg_map.end()) {
            if(spec.required) {
                throw std::invalid_argument("Required command line argument: " + key + " missing.");
            }
            arg_map[key] = spec.default_value;
        }
    }
    std::set<std::string> all_operations = constants::operations::ALL_OPERATIONS;
    
    if (std::all_of(all_operations.begin(), all_operations.end(), [&](const std::string& key) {
        return arg_map.at(key) == constants::FALSE_VAL;
    })) {
        throw std::invalid_argument("Specify at least one of operations");
    }
}

void ArgParser::initialize_specs() {
    arg_specs[constants::params::ALPHA] = ArgSpec::Double(false, constants::DEFAULT_ALPHA_FLOOR, constants::DEFAULT_ALPHA_CEILING, constants::DEFAULT_ALPHA);
    arg_specs[constants::params::BETA] = ArgSpec::Double(false, constants::DEFAULT_BETA_FLOOR, constants::DEFAULT_BETA_CEILING, constants::DEFAULT_BETA);
    arg_specs[constants::params::TRAIN_RATIO] = ArgSpec::Double(false, constants::DEFAULT_TRAIN_RATIO_FLOOR, constants::DEFAULT_TRAIN_RATIO_CEILING, constants::DEFAULT_TRAIN_RATIO);
    arg_specs[constants::params::STEPS_AHEAD] = ArgSpec::Integer(false, constants::DEFAULT_STEPS_AHEAD_FLOOR, constants::DEFAULT_STEPS_AHEAD_CEILING, constants::DEFAULT_STEPS_AHEAD);
    arg_specs[constants::params::METHOD] = ArgSpec::String(true, constants::methods::ALL_METHODS);
    arg_specs[constants::operations::FORECAST] = ArgSpec::Boolean(false);
    arg_specs[constants::operations::EVALUATE] = ArgSpec::Boolean(false);
    arg_specs[constants::params::DATA_SOURCE] = ArgSpec::String(true, constants::datasource::ALL_DATASOURCES);
    arg_specs[constants::params::INPUT_FILE_PATH] = ArgSpec::String(false);
    arg_specs[constants::params::TICKER] = ArgSpec::String(false);
    arg_specs[constants::params::START_DATE] = ArgSpec::String(false);
    arg_specs[constants::params::END_DATE] = ArgSpec::String(false);
}

