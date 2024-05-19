//
// Created by qingzhixing on 24-5-19.
//

#include <algorithm>
#include <utility>

#include "game_place/game_place.hpp"

static void debug_log_selection(const Selection &selection) {
    logger.flog_msg_debug("==== selection info ====");
    logger.flog_msg_debug("selection_name: %s", selection.selection_name.c_str());
    logger.flog_msg_debug("keyboard_key: %s", selection.keyboard_key.c_str());
    logger.flog_msg_debug("callback: %p", selection.callback);
    logger.flog_msg_debug("==== end selection info ====\n");
}

bool GamePlace::handle_selection(const std::string &keyboard_input) const {
    std::string standardized_str = lower(trim(keyboard_input));

    logger.flog_msg_debug("==== GamePlace::handle_selection() ====");
    logger.flog_msg_debug("standardized_str: %s", standardized_str.c_str());

    for (const auto &selection: selections) {

        debug_log_selection(selection);

        if (standardized_str == selection.keyboard_key) {
            logger.flog_msg_debug("==== END GamePlace::handle_selection() ====\n");
            selection.callback(*this);
            return true;
        }
    }
    logger.flog_msg_warn("Missing selection: %s", standardized_str.c_str());
    logger.flog_msg_debug("==== END GamePlace::handle_selection() ====");
    return false;
}
std::string trim(const std::string &str) {
    std::string trimmed_str = str;

    trimmed_str.erase(0, trimmed_str.find_first_not_of(' '));
    trimmed_str.erase(trimmed_str.find_last_not_of(' ') + 1);

    return std::move(trimmed_str);
}
std::string lower(const std::string &str) {
    std::string lowered_str = str;

    transform(lowered_str.begin(), lowered_str.end(), lowered_str.begin(), ::tolower);

    return std::move(lowered_str);
}