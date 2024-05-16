#include "console.hpp"
#include "debug.hpp"
#include <string>

Console console;

Console::Console() {
    std_output = GetStdHandle(STD_OUTPUT_HANDLE);
    set_console_cur_pos(0, 0);
    // hide_console_cursor(std_output);
    /*
        UNICODE: 65001
        GBK: 936
    */
    // SetConsoleOutputCP(936);
}

void debug_print_coord(ConsoleCoord pos, const char *msg) {
    DEBUG({
        printf("%s : {X: %d, Y: %d}\n", msg, pos.x, pos.y);
    });
}
void debug_print_coord(int X, int Y, const char *msg) {
    debug_print_coord({X, Y}, msg);
}

Console &Console::slow_print(const std::string &msg, DWORD sleep_ms, ConsoleCoord pos, int wAttributes) {
    ConsoleCoord old_pos = get_console_cur_pos();
    //    //TODO: delete this
    //    debug_print_coord(old_pos, "old_pos");
    //    debug_print_coord(pos, "new_pos");

    set_console_cur_pos(pos);

    set_console_text_attr(wAttributes);

    for (auto c: msg) {
        printf("%c", c);
        Sleep(sleep_ms);
    }

    set_console_cur_pos(old_pos);

    set_console_text_attr(TextColorPreset::DEFAULT);
    return *this;
}

Console &Console::slow_print(const std::string &msg, int wAttributes) {
    return slow_print(msg, HIGH_SPEED, {-1, -1}, wAttributes);
}

Console &Console::slow_print(const std::string &msg, ConsoleCoord pos) {
    return slow_print(msg, HIGH_SPEED, pos);
}

Console &Console::clear_screen() {
    COORD coord_screen = {0, 0};// home for the cursor
    DWORD c_chars_written;
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    DWORD console_size;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(std_output, &bufferInfo)) {
        return *this;
    }

    console_size = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(std_output,       // Handle to console screen buffer
                                    (TCHAR) ' ',      // Character to write to the buffer
                                    console_size,     // Number of cells to write
                                    coord_screen,     // Coordinates of first cell
                                    &c_chars_written))// Receive number of characters written
    {
        return *this;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(std_output, &bufferInfo)) {
        return *this;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(std_output,            // Handle to console screen buffer
                                    bufferInfo.wAttributes,// Character attributes to use
                                    console_size,          // Number of cells to set attribute
                                    coord_screen,          // Coordinates of first cell
                                    &c_chars_written))     // Receive number of characters written
    {
        return *this;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(std_output, coord_screen);
    return *this;
}

void Console::hide_console_cursor(HANDLE handle) {
    CONSOLE_CURSOR_INFO new_cursor_info = {};
    new_cursor_info.bVisible = 0;
    new_cursor_info.dwSize = 1;
    SetConsoleCursorInfo(handle, &new_cursor_info);
}

/**
    @param x - horizontal
    @param y - vertical
*/
Console &Console::set_console_cur_pos(int x, int y) {
    COORD console_size = get_console_size();

    //     FIXME!: 这里到底为啥错了？
    if (x > console_size.X || y > console_size.Y || x < 0 || y < 0) {
        // FIXME!: delete this
        debug_print_coord(x, y, "Invalid pos");
        return *this;
    }
    SetConsoleCursorPosition(std_output, COORD{(short) x, (short) y});

    return *this;
}

Console &Console::set_console_cur_pos(ConsoleCoord pos) {
    return set_console_cur_pos(pos.x, pos.y);
}

COORD Console::get_console_size() {
    COORD size;

    CONSOLE_SCREEN_BUFFER_INFO console_info;
    GetConsoleScreenBufferInfo(std_output, &console_info);
    SMALL_RECT sr_window = console_info.srWindow;

    int new_row, new_column;
    new_row = sr_window.Right - sr_window.Left + 1;
    new_column = sr_window.Bottom - sr_window.Top + 1;

    if (new_row < 0 || new_column < 0)
        return {-1, -1};

    size.X = SHORT(new_row);
    size.Y = SHORT(new_column);

    return size;
}

void debug_print_console_info(HANDLE handle) {
    DEBUG({
        CONSOLE_SCREEN_BUFFER_INFOEX info;
        GetConsoleScreenBufferInfoEx(handle, &info);

        printf("cbSize: %lu\n", info.cbSize);
        printf("dwSize: %d, %d\n", info.dwSize.X, info.dwSize.Y);
        printf("dwCursorPosition: %d, %d\n", info.dwCursorPosition.X, info.dwCursorPosition.Y);
        printf("wAttributes: %d\n", info.wAttributes);
        printf("srWindow: %d, %d, %d, %d\n", info.srWindow.Left, info.srWindow.Top, info.srWindow.Right, info.srWindow.Bottom);

        printf("dwMaximumWindowSize: %d, %d\n", info.dwMaximumWindowSize.X, info.dwMaximumWindowSize.Y);
        printf("wPopupAttributes: %d\n", info.wPopupAttributes);

        printf("bFullscreenSupported: %d\n", info.bFullscreenSupported);
    });
}

// FIXME!: 获取的信息貌似不对,查看microsoft有无提供GetConsoleScreenBufferInfoEx的错误检测
ConsoleCoord Console::get_console_cur_pos() {
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    GetConsoleScreenBufferInfoEx(std_output, &info);

    debug_print_console_info(std_output);

    return ConsoleCoord(info.dwCursorPosition);
}

Console &Console::set_console_text_attr(int wAttributes) {
    SetConsoleTextAttribute(std_output, WORD(wAttributes));
    return *this;
}