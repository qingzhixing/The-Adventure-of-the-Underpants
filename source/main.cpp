#include "main.hpp"
Console console;

int main(int argc, const char **argv)
{
    console.slow_print("underpants!", HIGH_SPEED);
    console.clear_screen();
    Sleep(3000);
    return 0;
}