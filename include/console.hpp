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
    /**
        @brief: slow_print at Cursor on (x,y)
    */
    void slow_print(const char *msg, DWORD sleep_ms, SHORT x = -1, SHORT y = -1);

    void clear_screen();

    void hide_console_cursor(HANDLE handle);

    /**
        @param x - horizontal pos
        @param y - vertical pos
    */
    void set_console_cur_pos(SHORT x, SHORT y);
    void set_console_cur_pos(COORD pos);

    void set_console_text_attr(WORD wAttributes);

    COORD get_console_size();

    COORD get_console_cur_pos();

private:
    HANDLE std_output;
};

enum TextColorPreset
{
    BLUE = FOREGROUND_BLUE,
    GREEN = FOREGROUND_GREEN,
    RED = FOREGROUND_RED,
    PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,

};

#endif // !_CONSOLE_HPP_