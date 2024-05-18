#pragma once
#ifndef GLOBAL_DATA_MANAGER_HPP_
#define GLOBAL_DATA_MANAGER_HPP_

#include "game_data/game_setting.hpp"
#include "game_data/player_data.hpp"
#include <rapidjson/document.h>
#include <string>
#include <vector>

class GlobalDataManager {
public:
    void load_game_data();

    void save_game_data();


private:
    static void add_game_info(rapidjson::Document &doc, rapidjson::Document::AllocatorType &allocator);

    void add_game_data(rapidjson::Document &doc, rapidjson::Document::AllocatorType &allocator);

    void parse_game_data(rapidjson::Value &value);

public:
    /*
        game_data
    */
    PlayerData player_data;
    GameSetting game_setting;

public:
    /*
        game_info:
    */
    const static string AUTHOR;
    const static string VERSION;

public:
    const static std::string &DATA_FILE;
};

extern GlobalDataManager global;

#endif// !GLOBAL_DATA_MANAGER_HPP_