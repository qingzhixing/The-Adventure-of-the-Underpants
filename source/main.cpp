#include "main.hpp"

extern Console console;

static void init()
{
    std::wcout.imbue(std::locale("chs"));
}

int main(int argc, const char **argv)
{
    init();

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

    getchar();
    return 0;
}