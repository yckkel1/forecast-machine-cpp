#pragma once

#include <string>

class SqlManager {
public:
    static std::string load_sql(const std::string& sql_file_path);
};
