#pragma once
#include <set>

enum class ArgType {
    BOOLEAN,
    STRING,
    DOUBLE,
    INTEGER
};

struct ArgSpec {
    ArgType type;
    bool required;
    double double_min_value = 0.0;
    double double_max_value = 1.0;
    int int_min_value = 0;
    int int_max_value = 100;
    // if specified value not in allowed values, throw error
    std::set<std::string> allowed_values;
    std::string default_value;
    
    static ArgSpec Boolean(bool required, const std::string& default_value="false") {
        return {ArgType::BOOLEAN, required, 0.0, 1.0, 0, 100, {}, default_value};
    }
    
    static ArgSpec String(bool required, std::set<std::string> allowed_vals = {}, const std::string& default_value="") {
        return {ArgType::STRING, required, 0.0, 1.0, 0, 100, allowed_vals, default_value};
    }
    
    static ArgSpec Double(bool required, double double_min_val = 0.0, double double_max_val = 1.0, const std::string& default_value="0.0") {
        return {ArgType::DOUBLE, required, double_min_val, double_max_val, 0, 100, {}, default_value};
    }
    
    static ArgSpec Integer(bool required, int int_min_val = 0, int int_max_val = 100, const std::string& default_value="0") {
        return {ArgType::INTEGER, required, 0.0, 1.0, int_min_val, int_max_val, {}, default_value};
    }
};
