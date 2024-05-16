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

class Logger {
public:
    explicit Logger(LogLevel level, std::ofstream &&log_stream)
        : default_log_level(level), log_file_stream(std::move(log_stream)) {}
    explicit Logger(LogLevel level)
        : default_log_level(level) {
        set_logger_file("./log.txt");
    }
    Logger() : Logger(LOG_LEVEL_DEBUG) {}

public:
    void log_msg(const std::string &msg, LogLevel level = LOG_LEVEL_DEBUG);
    void set_default_log_level(LogLevel level);
    bool set_logger_file(const std::string &file_name);
    void set_logger_stream(std::ofstream &&stream);

public:
    LogLevel default_log_level;
    std::ofstream log_file_stream;
};


#endif//UNDERPANTS_LOGGER_HPP