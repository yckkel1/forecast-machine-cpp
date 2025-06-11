#pragma once

#include <string>
#include <vector>
#include "dto/row_data.hpp"
#include <chrono>

class MysqlService {
private:
    class Impl;
    std::unique_ptr<Impl> impl;
public:
    MysqlService();
    std::vector<RowData> load_data(const std::string& ticker, const std::string& start_date, const std::string& end_date);
    void insert_data(const std::vector<RowData>& data);
    ~MysqlService();
};
