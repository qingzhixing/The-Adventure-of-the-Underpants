//
// Created by qingzhixing on 24-6-2.
//

#ifndef UNDERPANTS_STRING_UTIL_HPP
#define UNDERPANTS_STRING_UTIL_HPP
#include <string>

namespace underpants {

    std::string trim(const std::string &str);
    std::string format_case(const std::string &str, bool to_lower = true);
    std::string standardize_string(const std::string &str, bool enable_trim = true, bool enable_format_case = true, bool to_lower = true);

}// namespace underpants

#endif//UNDERPANTS_STRING_UTIL_HPP