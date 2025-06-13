#pragma once

#include <string>
#include "dotenv.h"

class EnvConfig {
private:
    static Dotenv env;
public:
    static void init();
    static std::string get(const std::string& key);
};
