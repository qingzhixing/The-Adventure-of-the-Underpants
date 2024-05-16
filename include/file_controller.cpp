//
// Created by qingzhixing on 24-5-16.
//

#include "file_controller.hpp"
#include "debug.hpp"
#include <direct.h>
#include <fstream>
std::string get_exe_dir() {
    static char path[1024];
    _getcwd(path, sizeof(path));
    return path;
}

std::string get_file_content(const std::string &file_name) {
    if (file_name.empty())
        return "";
    std::ifstream stream(file_name);
    if (!stream.is_open()) {
        DEBUG(printf("Failed to open file\n"));
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(stream)),
                        std::istreambuf_iterator<char>());
    stream.close();
    return content;
}