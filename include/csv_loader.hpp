#pragma once

#include <vector>
#include <string>

#include "dto/plot_data.hpp"
#include "dto/row_data.hpp"

std::vector<RowData> load_csv(const std::string& file_path);

void write_forecast_to_csv(const std::vector<PlotData>& data, const std::string& filePath);

