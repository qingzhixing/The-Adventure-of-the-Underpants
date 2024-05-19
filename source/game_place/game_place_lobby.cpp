//
// Created by qingzhixing on 24-5-19.
//

#include "game_place/game_place_lobby.hpp"
#include "console.hpp"
#include "game_data/global_data_manager.hpp"
#include "logger.hpp"
#include <format>

extern Console console;

static void display_game_info(const GamePlace &place) {
    logger.flog_msg_debug("==== %s ====", __FUNCTION__);
    logger.flog_msg_debug("Previous place: %s", place.place_name.c_str());
    logger.flog_msg_debug("==== END %s ====\n", __FUNCTION__);

    console.slow_print(std::format("Game Version: {} \n", GlobalDataManager::VERSION), {30, 20});
}

GamePlaceLobby::GamePlaceLobby() {
    place_name = "Lobby";
    selections.emplace_back(
            "Game Info",
            "i",
            display_game_info);
}
bool GamePlaceLobby::display() const {
    console.clear_screen();

    console.slow_print("Welcome to the Lobby!", {30, 10});

    console.slow_print("Please select an option:", {30, 12});

    console.set_console_cur_pos({5, 14});

    for (const auto &selection: selections) {
        console.slow_print(selection.selection_string(), DWORD(5));
    }

    return true;
}