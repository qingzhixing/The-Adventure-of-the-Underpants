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

void GlobalDataManager::add_game_info(Document &doc, rapidjson::Document::AllocatorType &allocator)
{
    Value game_info(kObjectType);
    game_info.AddMember("author", Value().SetString(AUTHOR.c_str(), AUTHOR.length(), allocator), allocator);
    game_info.AddMember("version", Value().SetString(VERSION.c_str(), VERSION.length(), allocator), allocator);
    doc.AddMember("game_info", game_info, allocator);
}
void GlobalDataManager::add_game_data(Document &doc, rapidjson::Document::AllocatorType &allocator)
{

    Value game_data(kObjectType);
    auto player_data_value = player_data.export_data(allocator);
    Value player_data_name;
    player_data_name.SetString(player_data.data_name.c_str(), player_data.data_name.length(), allocator);

    game_data.AddMember(player_data_name, player_data_value, allocator);
    doc.AddMember("game_data", game_data, allocator);
}

void GlobalDataManager::save_player_data()
{
    Document doc;
    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.SetObject();

    /*
        game_info
    */

    add_game_info(doc, allocator);

    /*
        game_data
    */

    add_game_data(doc, allocator);

    FILE *file;
    errno_t err = fopen_s(&file, "game_data.json", "w");
    if (err != 0)
    {
        printf("fopen_s error: %d\n", err);
        return;
    }

    char writeBuffer[65536];
    FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

    PrettyWriter<FileWriteStream> writer(os); // 注意，可以不使用PrettyWriter，不过，写出来的结构不好看，Pretty会将json写成树结构
    doc.Accept(writer);

    fclose(file);
}