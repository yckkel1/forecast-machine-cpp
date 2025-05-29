#pragma once

#include <string>
#include <map>

class ArgParser {
public:
    void parse(int argc, const char* argv[]);

    const std::string& get(const std::string& key) const;
    const std::string& get_or_default(const std::string& key, const std::string& default_value) const;

private:
    std::map<std::string, std::string> arg_map;
    void validate() const;
};
