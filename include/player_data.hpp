#pragma once
#ifndef __PLAYER_HPP_
#define __PLAYER_HPP_

#include <string>
#include <iostream>
#include "exportable_data.hpp"
#include "../lib/include/rapidjson/document.h"

using std::string;

class PlayerData : public ExportableData
{
public:
    PlayerData(string player_name);
    PlayerData();

public:
    rapidjson::Value export_data(rapidjson::Document::AllocatorType &allocator) const override;
    void import_data(const rapidjson::Value &object_data) override;
    void print_data() const override;

public:
    void add_experience(int exp);

    void add_cleanliness(int value);

    void add_blood(int value);

    void add_magic(int value);

    void add_attack(int value);

    void add_defense(int value);

    void lose_blood(int blood_off);

    void lose_magic(int magic_off);

    void lose_cleanliness(int cleanliness_off);

    bool is_dead() const;

    void upgrade();

    inline int upgrade_experience() const;

    inline int experience_to_upgrade() const;

public:
    string name;
    int level;
    int experience;
    int blood;
    int max_blood;
    int magic;
    int max_magic;
    int cleanliness;
    int max_cleanliness;
    int attack;
    int defense;
};

#endif // !__PLAYER_HPP_