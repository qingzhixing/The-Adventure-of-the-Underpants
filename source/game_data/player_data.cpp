#include "player_data.hpp"

#include "../game_management/debug.hpp"
#include <utility>

using namespace rapidjson;

namespace underpants {
    PlayerData::PlayerData(string _name) : ExportableData("player_data") {
        name = std::move(_name);
        level = 1;
        experience = 0;
        blood = 100;
        max_blood = 100;
        magic = 100;
        max_magic = 100;
        cleanliness = 100;
        max_cleanliness = 100;
        attack = 10;
        defense = 10;
    }

    PlayerData::PlayerData() : PlayerData("no-named") {}

    Value PlayerData::export_data(rapidjson::Document::AllocatorType &allocator) const {
        logger.flog_msg_debug("Exporting player data.\n");

        Value data(kObjectType);
        data.AddMember(MEMBER_2_STR(name), Value().SetString(name.c_str(), name.length(), allocator), allocator);
        data.AddMember(MEMBER_2_STR(level), level, allocator);
        data.AddMember(MEMBER_2_STR(experience), experience, allocator);
        data.AddMember(MEMBER_2_STR(blood), blood, allocator);
        data.AddMember(MEMBER_2_STR(max_blood), max_blood, allocator);
        data.AddMember(MEMBER_2_STR(magic), magic, allocator);
        data.AddMember(MEMBER_2_STR(max_magic), max_magic, allocator);
        data.AddMember(MEMBER_2_STR(cleanliness), cleanliness, allocator);
        data.AddMember(MEMBER_2_STR(max_cleanliness), max_cleanliness, allocator);
        data.AddMember(MEMBER_2_STR(attack), attack, allocator);
        data.AddMember(MEMBER_2_STR(defense), defense, allocator);

        logger.flog_msg_debug("Exporting player data done.\n");

        return data;
    }

    void PlayerData::log_data() const {
        logger.flog_msg_info("==== Player Data ====");
        logger.flog_msg_info("Name: %s", name.c_str());
        logger.flog_msg_info("Level: %d", level);
        logger.flog_msg_info("Experience: %d", experience);
        logger.flog_msg_info("Blood: %d", blood);
        logger.flog_msg_info("Max Blood: %d", max_blood);
        logger.flog_msg_info("Magic: %d", magic);
        logger.flog_msg_info("Max Magic: %d", max_magic);
        logger.flog_msg_info("Cleanliness: %d", cleanliness);
        logger.flog_msg_info("Max Cleanliness: %d", max_cleanliness);
        logger.flog_msg_info("Attack: %d", attack);
        logger.flog_msg_info("Defense: %d", defense);
        logger.flog_msg_info("==== End Player Data ====\n");
    }

    void PlayerData::import_data(const Value &object_data) {
        logger.flog_msg_debug("Importing player data\n");

        PARSE_STRING_VALUE(name);
        PARSE_INT_VALUE(level);
        PARSE_INT_VALUE(experience);
        PARSE_INT_VALUE(blood);
        PARSE_INT_VALUE(max_blood);
        PARSE_INT_VALUE(magic);
        PARSE_INT_VALUE(max_magic);
        PARSE_INT_VALUE(cleanliness);
        PARSE_INT_VALUE(max_cleanliness);
        PARSE_INT_VALUE(attack);
        PARSE_INT_VALUE(defense);

        logger.flog_msg_debug("Player data imported\n");
    }

    void PlayerData::add_experience(int exp) {
        experience += exp;
        upgrade();
    }

    void PlayerData::add_cleanliness(int value) {
        cleanliness += value;
        if (cleanliness > max_cleanliness)
            cleanliness = max_cleanliness;
    }

    void PlayerData::add_blood(int value) {
        blood += value;
        if (blood > max_blood)
            blood = max_blood;
    }

    void PlayerData::add_magic(int value) {
        magic += value;
        if (magic > max_magic)
            magic = max_magic;
    }

    void PlayerData::add_attack(int value) {
        attack += value;
    }

    void PlayerData::add_defense(int value) {
        defense += value;
    }

    void PlayerData::lose_blood(int blood_off) {
        blood -= blood_off;
        if (blood < 0)
            blood = 0;
    }

    void PlayerData::lose_magic(int magic_off) {
        magic -= magic_off;
        if (magic < 0)
            magic = 0;
    }

    void PlayerData::lose_cleanliness(int cleanliness_off) {
        cleanliness -= cleanliness_off;
        if (cleanliness < 0)
            cleanliness = 0;
    }

    bool PlayerData::is_dead() const {
        return blood == 0;
    }

    void PlayerData::upgrade() {
        if (experience >= upgrade_experience()) {
            level++;
            cleanliness = max_cleanliness;
            blood = max_blood;
            magic = max_magic;
            experience -= upgrade_experience();
            attack += 5;
            defense += 5;
        }
    }

    inline int PlayerData::upgrade_experience() const {
        return level * 100;
    }

    inline int PlayerData::experience_to_upgrade() const {
        return experience - upgrade_experience();
    }
}// namespace underpants