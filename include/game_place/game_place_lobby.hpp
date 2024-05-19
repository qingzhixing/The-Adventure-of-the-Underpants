//
// Created by qingzhixing on 24-5-19.
//

#pragma once
#ifndef UNDERPANTS_GAME_PLACE_LOBBY_HPP
#define UNDERPANTS_GAME_PLACE_LOBBY_HPP

#include "game_place.hpp"

class GamePlaceLobby : public GamePlace {
public:
    GamePlaceLobby();

public:
    [[nodiscard]] bool display() const override;
};

#endif//UNDERPANTS_GAME_PLACE_LOBBY_HPP