#pragma once
#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_

#include <Windows.h>
#include <iostream>

#define LOW_SPEED 150
#define MID_SPEED 80
#define HIGH_SPEED 20

enum TextColorPreset {
    INTENSITY = FOREGROUND_INTENSITY,// 增强
    BLACK = 0,
    BLUE = FOREGROUND_BLUE,
    GREEN = FOREGROUND_GREEN,
    CYAN = BLUE | GREEN,// 青色
    RED = FOREGROUND_RED,
    MAGENTA = RED | BLUE,// 洋红,粉紫色
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

inline void debug_print_coord(COORD pos, const char *msg = "pos-info");
inline void debug_print_coord(SHORT X, SHORT Y, const char *msg = "pos-info");
void debug_print_console_info(HANDLE handle);

class Console {
public:
    Console();

public:
    /**
        @brief: slow_print at Cursor on (x,y)
    */
    Console &slow_print(const std::string &msg, DWORD sleep_ms = HIGH_SPEED, COORD pos = {-1, -1}, int wAttributes = TextColorPreset::DEFAULT);
    Console &slow_print(const std::string &msg, int wAttributes);
    Console &slow_print(const std::string &msg, COORD pos);

    Console &clear_screen();

    static void hide_console_cursor(HANDLE handle);

    /**
        @param x - horizontal pos
        @param y - vertical pos
    */
    Console &set_console_cur_pos(SHORT x, SHORT y);
    Console &set_console_cur_pos(COORD pos);

    Console &set_console_text_attr(int wAttributes);

    COORD get_console_size();

    COORD get_console_cur_pos();

private:
    HANDLE std_output;
};

#endif// !_CONSOLE_HPP_