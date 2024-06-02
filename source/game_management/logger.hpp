//
// Created by qingzhixing on 24-5-16.
//
#pragma once
#ifndef UNDERPANTS_LOGGER_HPP
#define UNDERPANTS_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace underpants {
    enum class LogLevel : short {
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR,
        LOG_FATAL
    };

    std::string log_level_string(LogLevel level);

    std::string get_formated_time();

    class Logger {
        constexpr static const std::string DEFAULT_LOG_FILE = "./log.txt";

    public:
        explicit Logger(LogLevel level, std::ofstream &&log_stream)
            : log_level(level), log_file_stream(std::move(log_stream)) {}
        explicit Logger(LogLevel level)
            : log_level(level) {
            set_logger_file(DEFAULT_LOG_FILE);
        }
        Logger() : Logger(LogLevel::LOG_DEBUG) {}

    public:
        void log_msg(const std::string &msg, LogLevel level = LogLevel::LOG_DEBUG);
        void flog_msg_debug(const char *_format, ...);
        void flog_msg_info(const char *_format, ...);
        void flog_msg_warn(const char *_format, ...);
        void flog_msg_error(const char *_format, ...);
        void flog_msg_fatal(const char *_format, ...);
        void set_log_level(LogLevel level);
        bool set_logger_file(const std::string &file_name);
        void set_logger_stream(std::ofstream &&stream);
        bool is_log_level_enabled(LogLevel level) const;

    public:
        LogLevel log_level;
        std::ofstream log_file_stream;
    };

    extern Logger logger;
}// namespace underpants


#endif//UNDERPANTS_LOGGER_HPP