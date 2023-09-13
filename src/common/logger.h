#include "global_definitions.hpp"
#include <map>
#include <string>
#include <tuple>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Database.h>

#pragma once

using namespace agcplusplus;

class Logger {
public:
    explicit Logger();
    ~Logger();
    void initialize_database(const std::string& filename, const InitArguments& config);
    void initialize_cpu_table(const std::string& column_info);

    void log_cpu(const std::string& state_info);

    void commit_cpu();

private:
    SQLite::Database* database;
    SQLite::Transaction* transaction;
    bool cpu_table_initialized = false;
    bool memory_table_initialized = false;
};
