//
// Created by qingzhixing on 24-5-16.
//

#include "logger.hpp"
#include "file_controller.hpp"
#include <chrono>

Logger logger(LOG_LEVEL_DEBUG);

extern std::string log_level_string(LogLevel level) {
    if (level == LogLevel::LOG_LEVEL_DEBUG) return "DEBUG";
    if (level == LogLevel::LOG_LEVEL_INFO) return "INFO";
    if (level == LogLevel::LOG_LEVEL_WARN) return "WARN";
    if (level == LogLevel::LOG_LEVEL_ERROR) return "ERROR";
    if (level == LogLevel::LOG_LEVEL_FATAL) return "FATAL";

    return "UNKNOWN";
}
void Logger::log_msg(const std::string &msg, LogLevel level) {
    if (!is_log_level_enabled(level)) return;
    std::string real_msg =
            std::format("[{0}] [{1}] {2}", get_formated_time(), log_level_string(level), msg);
    log_file_stream << real_msg << std::endl;
}
void Logger::set_log_level(LogLevel level) {
    log_level = level;
}
void Logger::set_logger_stream(std::ofstream &&stream) {
    log_file_stream = std::move(stream);
}
bool Logger::set_logger_file(const std::string &file_name) {
    try {
        create_file(file_name);
        log_file_stream = file_ofstream(file_name);
    } catch (std::exception &e) {
        printf("[ERROR!] %s logger file open failed: %s\n", get_formated_time().c_str(), e.what());
        return false;
    }
    return true;
}

bool Logger::is_log_level_enabled(LogLevel level) const {
    return level >= log_level;
}

std::string get_formated_time() {
    auto time_point = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(time_point);
    char buf[20];
    strftime(buf, 20, "%d.%m.%Y %H:%M:%S", localtime(&time));
    return {buf};
}