#include "util/sql_manager.hpp"
#include <fstream>
#include <sstream>

std::string SqlManager::load_sql(const std::string& sql_file_path) {
    std::ifstream file(sql_file_path);
    if (!file) {
        throw std::runtime_error("Failed to open SQL file: " + sql_file_path);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
