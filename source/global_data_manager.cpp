#include "global_data_manager.hpp"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

using namespace rapidjson;

GlobalDataManager global;

const string GlobalDataManager::AUTHOR = "qingzhixing sama!";

const string GlobalDataManager::VERSION = "0.0.1 - preview";

void GlobalDataManager::load_player_data()
{
    printf("Unimplemented: load_player_data\n");
}

const char *GlobalDataManager::get_exe_dir()
{
    static char path[1024];
    _getcwd(path, sizeof(path));
    return path;
}

void GlobalDataManager::save_player_data()
{
    printf("Unimplemented: save_player_data\n");
    Document doc;
    doc.SetObject();

    /*
        game_info
    */
    Value game_info(kObjectType);
    game_info.AddMember("author", AUTHOR, doc.GetAllocator());
    game_info.AddMember("version", VERSION, doc.GetAllocator());
    doc.AddMember("game_info", game_info, doc.GetAllocator());

    /*
        game_data
    */
    // TODO:
    // Value game_data(kObjectType);
    // game_data.AddMember("player_data")

    FILE *file = fopen("game_data.json", "w");

    char writeBuffer[65536];
    FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

    PrettyWriter<FileWriteStream> writer(os); // 注意，可以不使用PrettyWriter，不过，写出来的结构不好看，Pretty会将json写成树结构
    doc.Accept(writer);

    fclose(file);
}