#include "game_setting.hpp"

using namespace rapidjson;
using namespace underpants;

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
    logger.log_msg("==== Game Setting Data ====", LogLevel::LOG_INFO);
    logger.flog_msg_info("first_enter: %s", bool_2_string(first_enter));
    logger.flog_msg_info("is_debug: %s", bool_2_string(is_debug));
    logger.flog_msg_info("skip_leading: %s", bool_2_string(skip_leading));
    logger.log_msg("==== End Game Setting Data ====\n", LogLevel::LOG_INFO);
}

void GameSetting::import_data(const Value &object_data) {
    logger.flog_msg_info("Importing game_setting\n");
    PARSE_BOOL_VALUE(first_enter);
    PARSE_BOOL_VALUE(is_debug);
    PARSE_BOOL_VALUE(skip_leading);

    logger.flog_msg_info("Importing game_setting done\n");
}