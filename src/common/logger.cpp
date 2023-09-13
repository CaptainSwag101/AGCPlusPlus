#include "logger.h"

Logger::Logger() = default;

void Logger::initialize_database(const std::string& filename, const InitArguments& config) {
    database = new SQLite::Database(filename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    database->exec("PRAGMA journal_mode = WAL;");
    database->exec("PRAGMA synchronous = NORMAL;");

    transaction = new SQLite::Transaction(*database, SQLite::TransactionBehavior::DEFERRED);

    database->exec("DROP TABLE IF EXISTS 'INFO';");
    database->exec("CREATE TABLE 'INFO' ('Timestamp' TEXT, 'Machine Type' TEXT, 'Rope File' TEXT);");

    // Get current time/date
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    // Store execution metadata into log
    database->exec("INSERT INTO 'INFO' VALUES ('" + timestamp.str() + "', '" + config.machine_type + "', '" + config.rope_file + "');");
}

void Logger::initialize_cpu_table(const std::string& column_info){
    if (cpu_table_initialized)
        throw std::runtime_error("Attempted to initialize_log CPU state table multiple times.");

    database->exec("DROP TABLE IF EXISTS 'CPU STATE';");
    database->exec("CREATE TABLE 'CPU STATE' (" + column_info + ");");

    cpu_table_initialized = true;
}

void Logger::log_cpu(const std::string& state_info) {
    if (!cpu_table_initialized)
        throw std::runtime_error("The CPU state table was used before being initialized.");

    if (transaction == nullptr)
        transaction = new SQLite::Transaction(*database, SQLite::TransactionBehavior::DEFERRED);

    database->exec("INSERT INTO 'CPU STATE' VALUES (" + state_info + ");");
}

void Logger::commit_cpu() {
    if (transaction != nullptr) {
        transaction->commit();
        delete transaction;
        transaction = nullptr;
    }
}

Logger::~Logger() {
    if (transaction != nullptr) transaction->commit();
}
