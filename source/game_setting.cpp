#include "game_setting.hpp"
#include "debug.hpp"

#include <iostream>
#include <rapidjson/document.h>
using namespace rapidjson;

GameSetting::GameSetting() : ExportableData("game_setting") {}

Value GameSetting::export_data(rapidjson::Document::AllocatorType &allocator) const
{
    DEBUG(printf("Exporting game_setting\n"));

    Value data(kObjectType);
    data.AddMember("first_enter", first_enter, allocator);
    data.AddMember("is_debug", is_debug, allocator);
    data.AddMember("skip_leading", skip_leading, allocator);

    DEBUG(printf("Exporting game_setting done\n"));

    return data;
}

void GameSetting::print_data() const
{
    std::cout << "GameSetting: " << std::endl;
    std::cout << "first_enter: " << bool_2_string(first_enter) << std::endl;
    std::cout << "is_debug: " << bool_2_string(is_debug) << std::endl;
    std::cout << "skip_leading" << bool_2_string(skip_leading) << std::endl;
}

void GameSetting::import_data(const Value &object_data)
{
    DEBUG(printf("Importing game_setting\n"));
    PARSE_BOOL_VALUE(first_enter);
    PARSE_BOOL_VALUE(is_debug);
    PARSE_BOOL_VALUE(skip_leading);

    DEBUG(printf("Importing game_setting done\n"));
}