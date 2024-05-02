#pragma once
#ifndef __GLOBAL_DATA_MANAGER_HPP_
#define __GLOBAL_DATA_MANAGER_HPP_

#include "player_data.hpp"

class GlobalDataManager
{
public:
    void load_player_data();
    void save_player_data();
    static const char *get_exe_dir();

public:
    PlayerData player_data;
};

extern GlobalDataManager global;

#endif // !__GLOBAL_DATA_MANAGER_HPP_