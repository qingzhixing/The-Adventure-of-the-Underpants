#pragma once
#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#include <iostream>
#include <Windows.h>

#define LOW_SPEED 150
#define MID_SPEED 80
#define HIGH_SPEED 20

class Console
{
public:
    Console();

public:
    void slow_print(const char *msg, DWORD sleep_ms);
    void clear_screen();

    void hide_console_cursor(HANDLE handle);

private:
    HANDLE std_output;
};

#endif // !_CONSOLE_HPP_