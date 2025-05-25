#include "dto/row_data.hpp"
#include "util/data_utils.hpp"
#include <string>
#include <iostream>
#include <sstream>

std::ostream& operator<< (std::ostream& os, const RowData& row_data) {
    std::string date_str = util::date_to_string(row_data.getDate());
    
    os << "Date: " << date_str << " ";
    os << "Open: " << row_data.getOpen() << " ";
    os << "Low: " << row_data.getLow() << " ";
    os << "High: " << row_data.getHigh() << " ";
    os << "Close: " << row_data.getClose() << " ";
    os << "Volume: " << row_data.getVolume() << std::endl;
    return os;
}


