#pragma once

#include <vector>
#include <string>

#include "dto/row_data.hpp"

std::vector<RowData> load_csv(const std::string& file_path);

