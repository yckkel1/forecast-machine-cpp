#include "util/arg_parser.hpp"
#include <iostream>
#include "util/constants.hpp"

void ArgParser::parse(int argc, const char* argv[]) {
    if (argc < 4) {
        throw new std::runtime_error("Required arguments: ./forecast_machine --input_file_path=... --forecast_method=... --evaluate(=true)/--forecast(=true)");
    }
    
    for(int i=0; i<argc; i++) {
        std::string arg = argv[i];
        if (!arg.starts_with("--")) {
            throw std::invalid_argument("All arguments must be in --key(=value) format");
        }
        auto eq = arg.find('=');
        if(arg.find('=') == std::string::npos) {
            args_map[arg.substr(2)] = "true";
        }
        else {
            args_map[arg.substr(2, eq-2)] = arg.substr(eq+1);
        }
    }
    
    if(!args_map.contains(constants::FORECAST) && !args_map.contains(constants::EVALUATE)) {
        throw std::runtime_error("Specify if this is forecast(--forecast) or evaluate(--evaluate)");
    }
    if(args_map.contains(constants::FORECAST) && args_map.contains(constants::EVALUATE)) {
        throw std::runtime_error("Cannot run forecast and evaluate ");
    }
}

std::string ArgParser::get(const std::string& key) const {
    auto it = args_map.find(key);
    if (it != args_map.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Missing required argument: --" + key);
    }
}

std::string ArgParser::get_or_default(const std::string& key, const std::string& default_value) {
    auto it = args_map.find(key);
    return it != args_map.end() ? it->second : default_value;
}
