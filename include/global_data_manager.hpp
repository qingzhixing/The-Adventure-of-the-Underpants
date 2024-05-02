#pragma once
#ifndef __GLOBAL_DATA_MANAGER_HPP_
#define __GLOBAL_DATA_MANAGER_HPP_

#include "player_data.hpp"
#include <vector>

class GlobalDataManager
{
public:
    void load_player_data();
    void save_player_data();
    static const char *get_exe_dir();

public:
    typedef std::vector<ExportableData> ExportableDataArray;
    ExportableDataArray data_array;

public:
    /*
        game_info:
    */
    const static string AUTHOR;
    const static string VERSION;
};

extern GlobalDataManager global;

#endif // !__GLOBAL_DATA_MANAGER_HPP_