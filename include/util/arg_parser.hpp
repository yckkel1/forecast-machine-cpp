#pragma once

#include <string>
#include <map>
#include "util/arg_spec.hpp"

class ArgParser {
public:
    void parse(int argc, const char* argv[]);

    const std::string& get(const std::string& key) const;
    
private:
    std::map<std::string, std::string> arg_map;
    std::map<std::string, ArgSpec> arg_specs;
    void validate_and_store(const std::string& key, const std::string& value);
    void validate_and_set_default();
    void initialize_specs();
};
