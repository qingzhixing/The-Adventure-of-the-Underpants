#include "player_data.hpp"

using namespace rapidjson;

PlayerData::PlayerData(string _name)
{
    name = _name;
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

Value PlayerData::export_data(rapidjson::CrtAllocator &allocator) const
{
    Value data(kArrayType);
    Value name_value(kStringType);
    return data;
}

void PlayerData::add_experience(int exp)
{
    experience += exp;
    upgrade();
}

void PlayerData::add_cleanliness(int value)
{
    cleanliness += value;
    if (cleanliness > max_cleanliness)
        cleanliness = max_cleanliness;
}

void PlayerData::add_blood(int value)
{
    blood += value;
    if (blood > max_blood)
        blood = max_blood;
}

void PlayerData::add_magic(int value)
{
    magic += value;
    if (magic > max_magic)
        magic = max_magic;
}

void PlayerData::add_attack(int value)
{
    attack += value;
}

void PlayerData::add_defense(int value)
{
    defense += value;
}

void PlayerData::lose_blood(int blood_off)
{
    blood -= blood_off;
    if (blood < 0)
        blood = 0;
}

void PlayerData::lose_magic(int magic_off)
{
    magic -= magic_off;
    if (magic < 0)
        magic = 0;
}

void PlayerData::lose_cleanliness(int cleanliness_off)
{
    cleanliness -= cleanliness_off;
    if (cleanliness < 0)
        cleanliness = 0;
}

bool PlayerData::is_dead() const
{
    return blood == 0;
}

void PlayerData::upgrade()
{
    if (experience >= upgrade_experience())
    {
        level++;
        cleanliness = max_cleanliness;
        blood = max_blood;
        magic = max_magic;
        experience -= upgrade_experience();
        attack += 5;
        defense += 5;
    }
}

inline int PlayerData::upgrade_experience() const
{
    return level * 100;
}

inline int PlayerData::experience_to_upgrade() const
{
    return experience - upgrade_experience();
}

void PlayerData::print_player_data()
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Experience: " << experience << std::endl;
    std::cout << "Blood: " << blood << "/" << max_blood << std::endl;
    std::cout << "Magic: " << magic << "/" << max_magic << std::endl;
    std::cout << "Cleanliness: " << cleanliness << "/" << max_cleanliness << std::endl;
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Defense: " << defense << std::endl;
}