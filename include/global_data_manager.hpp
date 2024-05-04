#pragma once
#ifndef __GLOBAL_DATA_MANAGER_HPP_
#define __GLOBAL_DATA_MANAGER_HPP_

#include "player_data.hpp"
#include <vector>
#include <rapidjson/document.h>
#include "game_setting.hpp"
#include <string>

class GlobalDataManager
{
public:
    void load_game_data();
    void save_game_data();
    static const char *get_exe_dir();

private:
    void add_game_info(rapidjson::Document &doc, rapidjson::Document::AllocatorType &allocator);
    void add_game_data(rapidjson::Document &doc, rapidjson::Document::AllocatorType &allocator);

    void parse_game_info(rapidjson::Value &value);
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
    const static char *DATA_FILE;
};

extern GlobalDataManager global;

#endif // !__GLOBAL_DATA_MANAGER_HPP_