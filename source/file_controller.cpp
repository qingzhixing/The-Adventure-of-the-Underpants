//
// Created by qingzhixing on 24-5-16.
//

#include "file_controller.hpp"
#include <direct.h>
#include <fstream>
namespace underpants {
    std::string get_exe_dir() {
        static char path[1024];
        _getcwd(path, sizeof(path));
        return path;
    }

    std::string get_file_content(const std::string &file_name) {
        if (file_name.empty())
            return "";
        std::ifstream stream = file_ifstream(file_name);

        std::string content((std::istreambuf_iterator<char>(stream)),
                            std::istreambuf_iterator<char>());
        stream.close();
        return content;
    }

    std::ofstream file_ofstream(const std::string &file_name) {
        if (file_name.empty()) {
            throw(std::runtime_error("file_name is empty"));
        }
        std::ofstream stream(file_name);
        if (!stream.is_open()) {
            std::string err_msg = "Missing file: " + file_name;
            throw(std::runtime_error(err_msg));
        }
        return std::move(stream);
    }
    std::ifstream file_ifstream(const std::string &file_name) noexcept(false) {
        if (file_name.empty()) {
            throw(std::runtime_error("file_name is empty"));
        }
        std::ifstream stream(file_name);
        if (!stream.is_open()) {
            std::string err_msg = "Missing file: " + file_name;
            throw(std::runtime_error(err_msg));
        }
        return std::move(stream);
    }
    std::FILE *file_open(const std::string &file_name, const std::string &mode) noexcept(false) {
        FILE *file;
        errno_t err = fopen_s(&file, file_name.c_str(), mode.c_str());
        if (err != 0) {
            std::string err_msg =
                    "fopen_s error code: " + std::to_string(err) + "\nfile_name: " + file_name;
            throw(std::runtime_error(err_msg));
        }
        if (file == nullptr) {
            std::string err_msg =
                    "Missing file: " + file_name + " (file == nullptr)";
        }
        return file;
    }
    void create_file(const std::string &file_name) {
        fclose(fopen(file_name.c_str(), "a+"));
    }
}// namespace underpants