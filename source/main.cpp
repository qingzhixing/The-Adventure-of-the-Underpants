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
    console.slow_print("Welcome to Underpants' World!", LOW_SPEED, 30, 10);
    return 0;
}