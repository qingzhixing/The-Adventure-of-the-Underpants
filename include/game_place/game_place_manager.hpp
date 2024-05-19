//
// Created by qingzhixing on 24-5-19.
//

#pragma once
#ifndef UNDERPANTS_GAME_PLACE_MANAGER_HPP
#define UNDERPANTS_GAME_PLACE_MANAGER_HPP


#include "game_place.hpp"
#include <memory>
typedef std::unique_ptr<GamePlace> GamePlacePtr;

class GamePlaceManager {

public:
    GamePlaceManager() = default;
    ~GamePlaceManager() = default;

public:
    bool display_game_place();
    [[nodiscard]] const GamePlacePtr &get_player_pos_place();
    void handle_input();

public:
    std::vector<GamePlacePtr> game_places;
    std::string runtime_player_pos_place;
};


#endif//UNDERPANTS_GAME_PLACE_MANAGER_HPP