#include "service/mysql_service.hpp"
#include "mysqlx/xdevapi.h"
#include "memory"
#include "util/env_config.hpp"
#include "dto/row_data.hpp"
#include <algorithm>
#include "util/data_utils.hpp"

class MysqlService::Impl {
public:
    Impl() : session(create_session()),
    history_data_schema(EnvConfig::get("HISTORY_DATA_SCHEMA")),
    forecast_schema(EnvConfig::get("FORECAST_SCHEMA")) {}
    
    std::vector<RowData> load_history_data(const std::string& ticker, const std::string& start_date, const std::string& end_date) {
        if(!is_valid(ticker)) {
            throw std::invalid_argument("Failed to load history data; Invalid ticker " + ticker);
        }
        std::vector<RowData> data;
        mysqlx::Schema schema(session, history_data_schema);
        mysqlx::Table table = schema.getTable(get_table_name_from_ticker(ticker), true);
//        std::cout << "Using Schema: " << history_data_schema << std::endl;
//        std::cout << "Using Table: " << table.getName() << std::endl;
        
        mysqlx:: RowResult res = table.select("CAST(DATE AS CHAR) AS DATE", "OPEN", "HIGH", "LOW", "CLOSE", "VOLUME")
                                        .where("DATE BETWEEN :start_date AND :end_date")
                                        .bind("start_date", start_date)
                                        .bind("end_date", end_date)
                                        .execute();
        for (const mysqlx::Row& row : res) {
//            std::cout << "Number of Col: " << row.colCount() << std::endl;
//            for (std::size_t i = 0; i < row.colCount(); ++i) {
//                if (row[i].isNull()) {
//                    std::cout << "NULL ";
//                } else {
//                    std::cout << row[i] << " ";
//                }
//            }
            data.emplace_back(
                util::parse_date_string(row[0].get<std::string>()), // DATE
                row[1].get<double>(), // OPEN
                row[2].get<double>(), // HIGH
                row[3].get<double>(), // LOW
                row[4].get<double>(), // CLOSE
                static_cast<uint64_t>(row[5].get<int64_t>()) // VOLUME
            );
        }
        return data;
    }
    
    void insert_history_data(const std::string& ticker, const std::vector<RowData>& data) {
        if(data.empty()) {
            throw std::invalid_argument("Failed to insert history data; data is empty");
        }
        mysqlx::Schema schema(session, history_data_schema);
        mysqlx::Table table = schema.getTable(get_table_name_from_ticker(ticker), true);
        mysqlx::TableInsert insert = table.insert("DATE", "OPEN", "HIGH", "LOW", "CLOSE", "VOLUME");

        for (const auto& row : data) {
            insert.values(
                util::date_to_string(row.getDate()),
                row.getOpen(),
                row.getHigh(),
                row.getLow(),
                row.getClose(),
                static_cast<int64_t>(row.getVolume())  // cast to avoid uint mismatch
            );
        }

        insert.execute();
    }
    
private:
    mysqlx::Session session;
    std::string history_data_schema;
    std::string forecast_schema;
    mysqlx::Session create_session() {
        EnvConfig::init();
        return mysqlx::Session(
            mysqlx::SessionOption::HOST, EnvConfig::get("DB_HOST"),
            mysqlx::SessionOption::PORT, std::stoi(EnvConfig::get("DB_PORT")),
            mysqlx::SessionOption::USER, EnvConfig::get("DB_USER"),
            mysqlx::SessionOption::PWD, EnvConfig::get("DB_PASSWORD")
        );
    }
    std::string get_table_name_from_ticker(const std::string& ticker) {
        std::string table_name = "T_" + ticker;
        std::transform(table_name.begin(), table_name.end(), table_name.begin(), ::toupper);
        return table_name;
    }
    bool is_valid(const std::string& s) {
        return std::all_of(s.begin(), s.end(), ::isalnum);
    }
};

MysqlService::MysqlService() : impl(std::make_unique<Impl>()) {}
MysqlService::~MysqlService() = default;

std::vector<RowData> MysqlService::load_history_data(const std::string& ticker, const std::string& start_date, const std::string& end_date) {
    return impl->load_history_data(ticker, start_date, end_date);
}

void MysqlService::insert_history_data(const std::string& ticker, const std::vector<RowData>& data) {
    return impl->insert_history_data(ticker, data);
}
