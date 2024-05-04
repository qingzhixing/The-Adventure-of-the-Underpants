#include "player_data.hpp"
#include "debug.hpp"

using namespace rapidjson;

PlayerData::PlayerData(string _name) : ExportableData("player_data")
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

Value PlayerData::export_data(rapidjson::Document::AllocatorType &allocator) const
{
    DEBUG(printf("Exporting player data.\n"));

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

    DEBUG(printf("Exporting player data done.\n"));

    return data;
}

void PlayerData::print_data() const
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

void PlayerData::import_data(const Value &object_data)
{
    DEBUG(printf("Importing player data\n"));

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

    DEBUG(printf("Player data imported\n"));
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
