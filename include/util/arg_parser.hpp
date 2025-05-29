#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

class ArgParser {
private:
    std::unordered_map<std::string, std::string> args_map;
public:
    ArgParser() = default;
    
    void parse(int argc, const char* argv[]);
    std::string get(const std::string& key) const;
    std::string get_or_default(const std::string& key, const std::string& default_value);
};
