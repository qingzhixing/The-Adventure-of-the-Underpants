//
// Created by qingzhixing on 24-5-16.
//
#pragma once
#ifndef UNDERPANTS_LOGGER_HPP
#define UNDERPANTS_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <string>

enum LogLevel {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
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
    Logger() : Logger(LOG_LEVEL_DEBUG) {}

public:
    void log_msg(const std::string &msg, LogLevel level = LOG_LEVEL_DEBUG);
    void set_log_level(LogLevel level);
    bool set_logger_file(const std::string &file_name);
    void set_logger_stream(std::ofstream &&stream);
    bool is_log_level_enabled(LogLevel level) const;

public:
    LogLevel log_level;
    std::ofstream log_file_stream;
};

extern Logger logger;


#endif//UNDERPANTS_LOGGER_HPP