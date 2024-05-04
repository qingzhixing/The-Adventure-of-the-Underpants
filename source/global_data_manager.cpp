#include "global_data_manager.hpp"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>

using namespace rapidjson;

GlobalDataManager global;

const string GlobalDataManager::AUTHOR = "qingzhixing sama!";

const string GlobalDataManager::VERSION = "0.0.1 - preview";

const char *GlobalDataManager::DATA_FILE = "game_data.json";

const char *GlobalDataManager::get_exe_dir()
{
    static char path[1024];
    _getcwd(path, sizeof(path));
    return path;
}

#pragma region import_data

void GlobalDataManager::parse_game_data(rapidjson::Value &value)
{
    const char *player_data_name = player_data.data_name.c_str();
    if (value.HasMember(player_data_name))
    {
        player_data.import_data(value[player_data_name]);
    }

    const char *game_setting_name = game_setting.data_name.c_str();
    if (value.HasMember(game_setting_name))
    {
        player_data.import_data(value[game_setting_name]);
    }
}

void GlobalDataManager::load_game_data()
{
    /*
        read file
    */
    FILE *file;
    errno_t err = fopen_s(&file, DATA_FILE, "r");
    if (err != 0)
    {
        printf("fopen_s error: %d\n", err);
        fclose(file);
        return;
    }
    if (file == nullptr)
    {
        printf("Missing file: %s, (file == nullptr)\n", DATA_FILE);
        fclose(file);
        return;
    }

    /*
        Parse.
    */

    std::ifstream stream(file);
    IStreamWrapper wrapper(stream);
    stream.close();

    DEBUG(printf(DELETE_ME "Prepared to parse json\n"));

    Document doc;
    doc.ParseStream(wrapper);

    DEBUG(printf(DELETE_ME "Json Parsed\n"));

    if (doc.HasParseError())
    {
        printf("Json Parse Error!\n");
        fprintf(stdout, "\nError(offset %u): %s\n", (unsigned)doc.GetErrorOffset(), GetParseError_En(doc.GetParseError()));
        HALT();
        fclose(file);
        return;
    }

    if (!doc.IsObject())
    {
        printf("Json is not an object!\n");
        fclose(file);
        return;
    }

    if (doc.HasMember("game_data"))
    {
        DEBUG(printf("game_data exist\n"));
        parse_game_data(doc["game_data"]);
    }

    fclose(file);
}

#pragma endregion

#pragma region save_data
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

    game_data.AddMember(player_data.get_data_name_value(allocator), player_data.export_data(allocator), allocator);

    game_data.AddMember(game_setting.get_data_name_value(allocator), game_setting.export_data(allocator), allocator);

    doc.AddMember("game_data", game_data, allocator);
}

void GlobalDataManager::save_game_data()
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
    errno_t err = fopen_s(&file, DATA_FILE, "w");
    if (err != 0)
    {
        printf("fopen_s error: %d\n", err);
        fclose(file);
        return;
    }

    char writeBuffer[65536];
    FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

    /*
        注意，可以不使用PrettyWriter，不过，写出来的结构不好看，Pretty会将json写成树结构
    */
    PrettyWriter<FileWriteStream> writer(os);
    doc.Accept(writer);

    fclose(file);
}

#pragma endregion