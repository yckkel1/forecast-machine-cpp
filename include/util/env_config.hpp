#pragma once

#include <string>
#include "dotenv.h"

class EnvConfig {
private:
    static DotEnv env;
public:
    static void init();
    static std::string get(const std::string& key, const std::string& default_value);
}
