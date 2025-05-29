#include "util/arg_parser.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "util/constants.hpp"

void ArgParser::parse(int argc, const char* argv[]) {
    if (argc < 4) {
        throw new std::invalid_argument("Required arguments: ./forecast_machine --input_file_path=... --method=... --evaluate(=true)/--forecast(=true)");
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (!arg.starts_with("--")) {
            throw std::invalid_argument("All arguments must be in --key(=value) format");
        }
        auto eq = arg.find('=');
        if(arg.find('=') == std::string::npos) {
            arg_map[arg.substr(2)] = constants::TRUE_VAL;
        }
        else {
            arg_map[arg.substr(2, eq-2)] = arg.substr(eq+1);
        }
    }

    validate();
}

const std::string& ArgParser::get(const std::string& key) const {
    auto it = arg_map.find(key);
    if (it == arg_map.end()) {
        throw std::runtime_error("Missing required argument: --" + key);
    }
    return it->second;
}

const std::string& ArgParser::get_or_default(const std::string& key, const std::string& default_value) const {
    auto it = arg_map.find(key);
    if (it == arg_map.end()) {
        return default_value;
    }
    return it->second;
}

void ArgParser::validate() const {
    if (!arg_map.contains(constants::INPUT_FILE_PATH)) {
        throw std::runtime_error("Missing required --input_file_path");
    }
    if (!arg_map.contains(constants::METHOD)) {
        throw std::runtime_error("Missing required --method");
    }
    if (!arg_map.contains(constants::operations::FORECAST) && !arg_map.contains(constants::operations::EVALUATE)) {
        throw std::runtime_error("Either --forecast or --evaluate must be specified");
    }
}

