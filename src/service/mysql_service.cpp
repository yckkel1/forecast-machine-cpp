#include "service/mysql_service.hpp"
#include "util/env_config.hpp"
#include <memory>
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/connection.h"
#include "jdbc/cppconn/prepared_statement.h"
#include "util/constants.hpp"
#include "util/sql_manager.hpp"
#include "util/data_utils.hpp"
#include <regex>

class MysqlService::Impl {
public:
    Impl() {
        EnvConfig::init();
        std::string host = EnvConfig::get("DB_HOST");
        std::string user = EnvConfig::get("DB_USER");
        std::string password = EnvConfig::get("DB_PASSWORD");
        std::string port = EnvConfig::get("DB_PORT");
        std::string host_name = host + ":" + port;
        driver = sql::mysql::get_driver_instance();
        conn = std::unique_ptr<sql::Connection>(driver->connect(host_name, user, password));
    }
    
    std::vector<RowData> load_data(const std::string& ticker, const std::string& start_date, const std::string& end_date) {
        if(!constants::tickers::PATHS.count(ticker)) {
            throw std::runtime_error("ticker data is not available");
        }
        
        std::string sql_file_path = std::string(SQL_BASE_PATH) + constants::QUERIES_DIR + constants::tickers::PATHS.at(ticker);
        std::vector<RowData> results;
        std::string sql = SqlManager::load_sql(sql_file_path);
        sql = std::regex_replace(sql, std::regex("\\{SCHEMA\\}"), get_history_data_schema());
        
        std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement(sql));
        stmt->setString(1, util::to_sql_date_string(start_date));
        stmt->setString(2, util::to_sql_date_string(end_date));
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        while (res->next()) {
            results.emplace_back(
                util::parse_date_string(res->getString("DATE")),
                res->getDouble("OPEN"),
                res->getDouble("HIGH"),
                res->getDouble("LOW"),
                res->getDouble("CLOSE"),
                static_cast<uint64_t>(res->getInt64("VOLUME"))
            );
        }
        
        std::cout << "size of results: " << results.size() << std::endl;
        return results;
    }
            
private:
    sql::mysql::MySQL_Driver* driver;
    std::unique_ptr<sql::Connection> conn;
    std::string get_history_data_schema() {
        return EnvConfig::get("HISTORY_DATA_SCHEMA");
    }
    std::string get_forecast_schema() {
        return EnvConfig::get("FORECAST");
    }
};

MysqlService::MysqlService() : impl(std::make_unique<Impl>()) {}
MysqlService::~MysqlService() = default;

std::vector<RowData> MysqlService::load_data(const std::string& ticker, const std::string& start_date, const std::string& end_date) {
    return impl->load_data(ticker, start_date, end_date);
}

//TODO: Define insert 


