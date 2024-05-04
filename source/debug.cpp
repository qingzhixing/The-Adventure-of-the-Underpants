#include "debug.hpp"
#include <iostream>
#include <fstream>
std::string get_file_content(const char *file)
{
    if (file == nullptr)
        return "";
    std::ifstream stream(file);
    if (!stream.is_open())
    {
        DEBUG(printf("Failed to open file\n"));
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(stream)),
                        std::istreambuf_iterator<char>());
    stream.close();
    return content;
}