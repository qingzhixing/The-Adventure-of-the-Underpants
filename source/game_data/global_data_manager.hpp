#pragma once
#ifndef GLOBAL_DATA_MANAGER_HPP_
#define GLOBAL_DATA_MANAGER_HPP_

#include "game_setting.hpp"
#include "player_data.hpp"
#include "rapidjson/document.h"
#include <string>
#include <vector>

namespace underpants {
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
        const static std::string &DATA_FILE;
    };

    extern GlobalDataManager global;
}// namespace underpants


#endif// !GLOBAL_DATA_MANAGER_HPP_