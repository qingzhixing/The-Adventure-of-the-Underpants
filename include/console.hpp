#pragma once
#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

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

struct ConsoleCoord {
    explicit ConsoleCoord(COORD coord) { x = coord.X, y = coord.Y; }
    ConsoleCoord(int X, int Y) : x(X), y(Y) {}
    int x, y;
};

void debug_print_coord(ConsoleCoord pos, const char *msg = "pos-info");
void debug_print_coord(int X, int Y, const char *msg = "pos-info");
void debug_print_console_info(HANDLE handle);

class Console {
public:
    Console();

public:
    /**
        @brief: slow_print at Cursor on (x,y)
    */
    Console &slow_print(const std::string &msg, DWORD sleep_ms = HIGH_SPEED, ConsoleCoord pos = {-1, -1}, int wAttributes = TextColorPreset::DEFAULT);
    Console &slow_print(const std::string &msg, int wAttributes);
    Console &slow_print(const std::string &msg, ConsoleCoord pos);

    Console &clear_screen();

    static void hide_console_cursor(HANDLE handle);

    /**
        @param x - horizontal pos
        @param y - vertical pos
    */
    Console &set_console_cur_pos(int x, int y);
    Console &set_console_cur_pos(ConsoleCoord pos);

    Console &set_console_text_attr(int wAttributes);

    COORD get_console_size();

    ConsoleCoord get_console_cur_pos();

private:
    HANDLE std_output;
};

#endif// !CONSOLE_HPP_