#include "main.hpp"
Console console;

int main(int argc, const char **argv)
{
    std::wcout.imbue(std::locale("chs"));
    console.set_console_cur_pos(5, 10);
    console.slow_print("underpants!", MID_SPEED);
    console.set_console_cur_pos(5, 11);
    console.slow_print("I used wanna use Chinese but failed, anyway.", HIGH_SPEED);
    getchar();
    Sleep(3000);
    return 0;
}