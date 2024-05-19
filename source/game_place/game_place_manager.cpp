//
// Created by qingzhixing on 24-5-19.
//

#include "game_place/game_place_manager.hpp"
#include "console.hpp"
#include "logger.hpp"

extern Console console;

bool GamePlaceManager::display_game_place() {
    const auto &place = get_player_pos_place();

    logger.flog_msg_debug("player is at {%s}\n", place->place_name.c_str());
    return place->display();
}

const GamePlacePtr &GamePlaceManager::get_player_pos_place() {
    for (const auto &place: game_places) {
        if (place->place_name == runtime_player_pos_place) {
            return place;
        }
    }
    logger.flog_msg_error("Player is at an unknown place! {%s}\n", runtime_player_pos_place.c_str());
    const auto &new_place = game_places.front();
    runtime_player_pos_place = new_place->place_name;
    return new_place;
}
void GamePlaceManager::handle_input() {
    bool correct_input_flag = false;
    do {
        std::string input;
        getline(std::cin, input);

        auto success = get_player_pos_place()->handle_selection(input);

        correct_input_flag = success;

        if (!correct_input_flag) {
            logger.flog_msg_info("wrong input: %s", input.c_str());
            console.slow_print(std::format("wrong input: {}\n", input), 0, {5, 0});
        }
    } while (!correct_input_flag);


    // TODO:使用handler_input更改runtime_player_pos_place状态
    //  而不是get_player_pos_place().handle_selection(input);
}