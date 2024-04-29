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
    void slow_print(const std::string &msg, DWORD sleep_ms, SHORT x = -1, SHORT y = -1);

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
    INTENSITY = FOREGROUND_INTENSITY, // 增强
    BLACK = 0,
    BLUE = FOREGROUND_BLUE,
    GREEN = FOREGROUND_GREEN,
    CYAN = BLUE | GREEN, // 青色
    RED = FOREGROUND_RED,
    MAGENTA = RED | BLUE, // 洋红,粉紫色
    YELLOW = RED | GREEN,
    WHITE = RED | BLUE | GREEN,
    GREY = BLACK | INTENSITY,
    INTENSITY_BLACK = INTENSITY | BLACK,
    INTENSITY_BLUE = INTENSITY | BLUE,
    INTENSITY_GREEN = INTENSITY | GREEN,
    INTENSITY_CYAN = INTENSITY | CYAN,
    INTENSITY_RED = INTENSITY | RED,
    INTENSITY_MAGENTA = INTENSITY | MAGENTA,
    INTENSITY_YELLOW = INTENSITY | YELLOW,
    INTENSITY_WHITE = INTENSITY | WHITE,
    DEFAULT = WHITE,
};

#endif // !_CONSOLE_HPP_