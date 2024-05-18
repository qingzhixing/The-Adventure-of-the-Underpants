#include "game_data/game_setting.hpp"

#include <iostream>
using namespace rapidjson;

GameSetting::GameSetting() : ExportableData("game_setting") {}

Value GameSetting::export_data(rapidjson::Document::AllocatorType &allocator) const {
    logger.flog_msg_debug("Exporting game_setting\n");

    Value data(kObjectType);
    data.AddMember("first_enter", first_enter, allocator);
    data.AddMember("is_debug", is_debug, allocator);
    data.AddMember("skip_leading", skip_leading, allocator);

    logger.flog_msg_debug("Exporting game_setting done\n");

    return data;
}

void GameSetting::log_data() const {
    logger.log_msg("==== Game Setting Data ====", LOG_LEVEL_INFO);
    logger.flog_msg_info("first_enter: %s", first_enter ? "true" : "false");
    logger.flog_msg_info("is_debug: %s", is_debug ? "true" : "false");
    logger.flog_msg_info("skip_leading: %s", skip_leading ? "true" : "false");
    logger.log_msg("==== End Game Setting Data ====\n", LOG_LEVEL_INFO);
}

void GameSetting::import_data(const Value &object_data) {
    DEBUG(printf("Importing game_setting\n"));
    PARSE_BOOL_VALUE(first_enter);
    PARSE_BOOL_VALUE(is_debug);
    PARSE_BOOL_VALUE(skip_leading);

    DEBUG(printf("Importing game_setting done\n"));
}