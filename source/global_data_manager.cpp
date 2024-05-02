#include "global_data_manager.hpp"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

using namespace rapidjson;

GlobalDataManager global;

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

    Value value(kObjectType);
    value.AddMember("author", "qingzhixing sama!", doc.GetAllocator());

    doc.SetObject();
    doc.AddMember("game_info", value, doc.GetAllocator());

    FILE *file = fopen("game_data.json", "w");

    char writeBuffer[65536];
    FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

    PrettyWriter<FileWriteStream> writer(os); // 注意，可以不使用PrettyWriter，不过，写出来的结构不好看，Pretty会将json写成树结构
    doc.Accept(writer);

    fclose(file);
}