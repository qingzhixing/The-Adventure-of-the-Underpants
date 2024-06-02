//
// Created by qingzhixing on 24-5-16.
//

#pragma once
#ifndef UNDERPANTS_FILE_CONTROLLER_HPP
#define UNDERPANTS_FILE_CONTROLLER_HPP


#include <fstream>
#include <string>

namespace underpants {
    std::string get_exe_dir();
    std::string get_file_content(const std::string &file_name);
    std::ofstream file_ofstream(const std::string &file_name) noexcept(false);
    std::ifstream file_ifstream(const std::string &file_name) noexcept(false);
    std::FILE *file_open(const std::string &file_name, const std::string &mode) noexcept(false);
    void create_file(const std::string &file_name);

    class FileController {
    };
}// namespace underpants


#endif//UNDERPANTS_FILE_CONTROLLER_HPP