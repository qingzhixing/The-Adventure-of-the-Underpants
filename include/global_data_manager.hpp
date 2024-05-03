#pragma once
#ifndef __GLOBAL_DATA_MANAGER_HPP_
#define __GLOBAL_DATA_MANAGER_HPP_

#include "player_data.hpp"
#include <vector>
#include <rapidjson/document.h>

class GlobalDataManager
{
public:
    void load_player_data();
    void save_player_data();
    static const char *get_exe_dir();

private:
    void add_game_info(rapidjson::Document &doc, rapidjson::Document::AllocatorType &allocator);
    void add_game_data(rapidjson::Document &doc, rapidjson::Document::AllocatorType &allocator);

public:
    /*
        game_data
    */
    PlayerData player_data;

public:
    /*
        game_info:
    */
    const static string AUTHOR;
    const static string VERSION;
};

extern GlobalDataManager global;

#endif // !__GLOBAL_DATA_MANAGER_HPP_