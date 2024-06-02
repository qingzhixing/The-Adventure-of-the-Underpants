//
// Created by qingzhixing on 24-6-2.
//

#include "string_util.hpp"
#include <algorithm>
#include <string>

namespace underpants {

    std::string format_case(const std::string &str, bool to_lower) {
        std::string result;
        result = str;

        auto unary_op = (to_lower ? ::tolower : ::toupper);

        transform(result.begin(), result.end(), result.begin(), unary_op);

        return result;
    }
    std::string trim(const std::string &str) {
        std::string result;
        result = str;

        result.erase(
                result.begin(),
                std::find_if(
                        result.begin(),
                        result.end(),
                        [](int ch) {
                            return !std::isspace(ch);
                        }));

        result.erase(
                std::find_if(
                        result.rbegin(),
                        result.rend(),
                        [](int ch) {
                            return !std::isspace(ch);
                        })
                        .base(),
                result.end());

        return result;
    }
    std::string standardize_string(const std::string &str, bool enable_trim, bool enable_format_case, bool to_lower) {
        std::string result;
        result = str;

        if (enable_trim) {
            result = trim(result);
        }

        if (enable_format_case) {
            result = format_case(result, to_lower);
        }

        return result;
    }
}// namespace underpants