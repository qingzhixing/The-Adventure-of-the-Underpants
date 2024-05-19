//
// Created by qingzhixing on 24-5-19.
//

#include <algorithm>
#include <utility>

#include "game_place/game_place.hpp"

bool GamePlace::handle_selection(const std::string &keyboard_input) const {
    std::string standardized_str = lower(trim(keyboard_input));

    for (const auto &selection: selections) {
        if (standardized_str == selection.keyboard_key) {
            selection.callback(*this);
            return true;
        }
    }

    return false;
}
std::string trim(const std::string &str) {
    std::string trimmed_str = str;

    trimmed_str.erase(0, trimmed_str.find_first_not_of(' '));
    trimmed_str.erase(trimmed_str.find_last_not_of(' ') + 1);

    return std::move(trimmed_str);
}
std::string lower(const std::string &str) {
    std::string lowered_str;

    transform(lowered_str.begin(), lowered_str.end(), lowered_str.begin(), ::tolower);

    return std::move(lowered_str);
}