#pragma once
#ifndef __GLOBAL_DATA_MANAGER_HPP_
#define __GLOBAL_DATA_MANAGER_HPP_

#include "player.hpp"

class GlobalDataManager
{
public:
    void load_player_data();
    void save_player_data();

public:
    Player player_data;
};

extern GlobalDataManager global;

#endif // !__GLOBAL_DATA_MANAGER_HPP_