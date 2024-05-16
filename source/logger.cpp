//
// Created by qingzhixing on 24-5-16.
//

#include "logger.hpp"

extern std::string log_level_string(LogLevel level) {
    if (level == LogLevel::LOG_LEVEL_DEBUG) return "DEBUG";
    if (level == LogLevel::LOG_LEVEL_INFO) return "INFO";
    if (level == LogLevel::LOG_LEVEL_WARN) return "WARN";
    if (level == LogLevel::LOG_LEVEL_ERROR) return "ERROR";
    if (level == LogLevel::LOG_LEVEL_FATAL) return "FATAL";

    return "UNKNOWN";
}
void Logger::log_msg(const std::string &msg, LogLevel level) {
}
void Logger::set_default_log_level(LogLevel level) {
    default_log_level = level;
}
void Logger::set_logger_stream(std::ofstream &&stream) {
    log_file_stream = std::move(stream);
}
bool Logger::set_logger_file(const std::string &file_name) {
}