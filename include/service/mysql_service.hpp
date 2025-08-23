#pragma once

#include <string>
#include <vector>
#include "dto/row_data.hpp"
#include <chrono>
#include <memory>

class MysqlService {
private:
    class Impl;
    std::unique_ptr<Impl> impl;
public:
    MysqlService();
    std::vector<RowData> load_history_data(const std::string& ticker, const std::string& start_date, const std::string& end_date);
    void insert_history_data(const std::string& ticker, const std::vector<RowData>& data);
    ~MysqlService();
};
