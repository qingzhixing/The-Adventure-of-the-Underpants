#include "main.hpp"

extern GlobalDataManager global;

static PlayerData &player = global.player_data;

static GameSetting &setting = global.game_setting;

extern Console console;

static void init()
{
    global.load_game_data();
    player.print_data();
    setting.print_data();
}

inline void first_enter()
{
    /**
        @brief: loading into game
    */
    console.slow_print("underpants!", MID_SPEED, 5, 10);
    console.slow_print("I used wanna use Chinese but failed, anyway.", HIGH_SPEED, 5, 11);
    Sleep(1.5_s);
    console.clear_screen();

    /**
        @brief: Introduction
    */
    console.slow_print("Welcome to Underpants' World!", LOW_SPEED, 30, 8);
    console.slow_print("You are an UNDERPANTS, the resident of this world.", MID_SPEED, 25, 10);
    console.slow_print("You are selected to gain the EVOLUTION.", MID_SPEED, 30, 12);
    console.slow_print("Now! Start your adventure!", HIGH_SPEED, 30, 15);
    Sleep(1.5_s);
    console.clear_screen();

    /**
     * @brief Get Player Data
     */

    console.slow_print("Please enter your name: ", HIGH_SPEED, 30, 8);
    console.set_console_text_attr(TextColorPreset::INTENSITY_YELLOW);

    // read a line of name
    std::getline(std::cin, player.name);
    console.set_console_text_attr(TextColorPreset::DEFAULT);

    // save data
    global.save_game_data();

    console.slow_print("Hello, " + player.name + "!\n", HIGH_SPEED, 30, 10);
    player.print_data();
    Sleep(1.5_s);
}

inline void not_first_enter()
{

    console.slow_print("underpants!", HIGH_SPEED, 5, 10);
    Sleep(1.5_s);
    console.clear_screen();

    console.slow_print("Hello, " + player.name + "!\n", HIGH_SPEED, 30, 10);
    console.slow_print("Welcome back to Underpants' World!", HIGH_SPEED, 30, 12);
    console.slow_print("Now! Start your adventure!", HIGH_SPEED, 30, 16);
    Sleep(1.5_s);
    console.clear_screen();

    Sleep(1.5_s);
}

int main(int argc, const char **argv)
{
    init();

    if (setting.first_enter)
    {
        first_enter();
        setting.first_enter = false;
        global.save_game_data();
    }
    else
    {
        not_first_enter();
    }

    while (true)
    {
    }
    return 0;
}