//
// Created by qingzhixing on 24-5-16.
//

#include "logger.hpp"
#include "file_controller.hpp"
#include <chrono>
#include <cstdarg>

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

static const int buf_size = 2048;
static std::string formatted_string(const char *_format, va_list args) {

    char buf[buf_size];
    vsnprintf(buf, buf_size, _format, args);
    return {buf};
}

void Logger::flog_msg_debug(const char *_format, ...) {
    std::string msg;
    va_list args;
    va_start(args, _format);
    msg = formatted_string(_format, args);
    va_end(args);
    log_msg(msg, LogLevel::LOG_LEVEL_DEBUG);
}
void Logger::flog_msg_info(const char *_format, ...) {
    std::string msg;
    va_list args;
    va_start(args, _format);
    msg = formatted_string(_format, args);
    va_end(args);
    log_msg(msg, LogLevel::LOG_LEVEL_INFO);
}
void Logger::flog_msg_warn(const char *_format, ...) {
    std::string msg;
    va_list args;
    va_start(args, _format);
    msg = formatted_string(_format, args);
    va_end(args);
    log_msg(msg, LogLevel::LOG_LEVEL_WARN);
}
void Logger::flog_msg_error(const char *_format, ...) {
    std::string msg;
    va_list args;
    va_start(args, _format);
    msg = formatted_string(_format, args);
    va_end(args);
    log_msg(msg, LogLevel::LOG_LEVEL_ERROR);
}
void Logger::flog_msg_fatal(const char *_format, ...) {
    std::string msg;
    va_list args;
    va_start(args, _format);
    msg = formatted_string(_format, args);
    va_end(args);
    log_msg(msg, LogLevel::LOG_LEVEL_FATAL);
}

std::string get_formated_time() {
    auto time_point = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(time_point);
    char buf[20];
    strftime(buf, 20, "%d.%m.%Y %H:%M:%S", localtime(&time));
    return {buf};
}