#include "global_data_manager.hpp"
#include "../game_management/file_controller.hpp"

#include "rapidjson/error/en.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include <fstream>

using namespace rapidjson;

namespace underpants {

    GlobalDataManager global = GlobalDataManager();

    const string GlobalDataManager::AUTHOR = "qingzhixing sama!";

    const string GlobalDataManager::VERSION = "0.0.1 - preview";

    const std::string &GlobalDataManager::DATA_FILE = "game_data.json";


    /**
 * @brief Import data from json.
 * @param value - root of parsing data
 */
    void GlobalDataManager::parse_game_data(rapidjson::Value &value) {
        logger.log_msg("Parsing global game data.\n", LogLevel::LOG_DEBUG);

        const char *player_data_name = player_data.json_key_name.c_str();

        if (value.HasMember(player_data_name)) {
            player_data.import_data(value[player_data_name]);
        } else {
            logger.log_msg("Missing player_data object\n", LogLevel::LOG_WARN);
        }

        const char *game_setting_name = game_setting.json_key_name.c_str();
        if (value.HasMember(game_setting_name)) {
            game_setting.import_data(value[game_setting_name]);
        } else {
            logger.log_msg("Missing game_setting object\n", LogLevel::LOG_WARN);
        }
    }

    /**
 * @brief load game data from json file.
 */
    void GlobalDataManager::load_game_data() {

        /*
        Parse.
    */

        std::ifstream stream(DATA_FILE);
        create_file(DATA_FILE);
        string content = get_file_content(DATA_FILE);
        logger.flog_msg_debug("content:\n%s\n", content.c_str());

        stream.close();

        logger.flog_msg_debug("Prepared to parse json\n");

        Document doc;
        doc.Parse(content.c_str());

        logger.flog_msg_debug("Json Parsed\n");

        if (doc.HasParseError()) {
            //        printf("Json Parse Error!\n");
            logger.flog_msg_error("Json Parse Error!\n");
            logger.flog_msg_error("Error(offset %u): %s\n", (unsigned) doc.GetErrorOffset(), GetParseError_En(doc.GetParseError()));
            return;
        }

        if (!doc.IsObject()) {
            logger.flog_msg_error("Json is not an object!\n");
            return;
        }

        if (doc.HasMember("game_data")) {
            logger.flog_msg_info("game_data exist\n");
            parse_game_data(doc["game_data"]);
        }
    }


    void GlobalDataManager::add_game_info(Document &doc, rapidjson::Document::AllocatorType &allocator) {
        Value game_info(kObjectType);
        game_info.AddMember("author", Value().SetString(AUTHOR.c_str(), AUTHOR.length(), allocator), allocator);
        game_info.AddMember("version", Value().SetString(VERSION.c_str(), VERSION.length(), allocator), allocator);
        doc.AddMember("game_info", game_info, allocator);
    }

    void GlobalDataManager::add_game_data(Document &doc, rapidjson::Document::AllocatorType &allocator) {

        Value game_data(kObjectType);

        game_data.AddMember(player_data.get_data_name_value(allocator), player_data.export_data(allocator), allocator);

        game_data.AddMember(game_setting.get_data_name_value(allocator), game_setting.export_data(allocator), allocator);

        doc.AddMember("game_data", game_data, allocator);
    }

    void GlobalDataManager::save_game_data() {
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
        try {
            file = file_open(DATA_FILE, "w");
        } catch (std::exception &e) {
            logger.log_msg(e.what(), LogLevel::LOG_ERROR);
            logger.log_msg("Failed to save game data.", LogLevel::LOG_ERROR);
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
}// namespace underpants