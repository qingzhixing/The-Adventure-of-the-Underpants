#include "console.hpp"
#include "debug.hpp"
#include "logger.hpp"
#include <string>

namespace underpants {
    Console console;

    Console::Console() {
        std_output = GetStdHandle(STD_OUTPUT_HANDLE);
        set_console_cur_pos(0, 0);
        enable_cursor_display(false);
    }

#pragma region console_debug

    void debug_log_coord(ConsoleCoord pos, const char *msg) {
        DEBUG({
            logger.flog_msg_debug("%s : {X: %d, Y: %d}\n", msg, pos.x, pos.y);
        });
    }
    void debug_log_coord(int X, int Y, const char *msg) {
        debug_log_coord({X, Y}, msg);
    }

    void debug_log_console_info(HANDLE handle) {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(handle, &info);
        logger.log_msg("==== CONSOLE_SCREEN_BUFFER_INFO ====", LogLevel::LOG_INFO);
        logger.flog_msg_info("Console size: (%d, %d)", info.srWindow.Right - info.srWindow.Left + 1, info.srWindow.Bottom - info.srWindow.Top + 1);
        logger.flog_msg_info("Console cursor pos: (%d, %d)", info.dwCursorPosition.X, info.dwCursorPosition.Y);
        logger.flog_msg_info("Console text attr: %d", info.wAttributes);
        logger.flog_msg_info("Console dwSize: (%d, %d)", info.dwSize.X, info.dwSize.Y);
        logger.flog_msg_info("Console dwMaximumWindowSize: (%d, %d)", info.dwMaximumWindowSize.X, info.dwMaximumWindowSize.Y);
        logger.log_msg("==== END CONSOLE_SCREEN_BUFFER_INFO ====\n", LogLevel::LOG_INFO);
    }

#pragma endregion

#pragma region slow_print

    Console &Console::slow_print(const std::string &msg, DWORD sleep_ms, ConsoleCoord pos, bool restore_cursor, int wAttributes) {
        ConsoleCoord old_pos = get_console_cur_pos();
        set_console_cur_pos(pos);

        set_console_text_attr(wAttributes);

        for (auto c: msg) {
            printf("%c", c);
            Sleep(sleep_ms);
        }

        set_console_text_attr(TextColorPreset::DEFAULT);

        if (restore_cursor) {
            set_console_cur_pos(old_pos);
        }
        return *this;
    }

    Console &Console::slow_print(const std::string &msg, int wAttributes, bool restore_cursor) {
        return slow_print(msg, HIGH_SPEED, {-1, -1}, restore_cursor, wAttributes);
    }

    Console &Console::slow_print(const std::string &msg, ConsoleCoord pos, bool restore_cursor) {
        return slow_print(msg, HIGH_SPEED, pos, restore_cursor);
    }


    Console &Console::slow_print_then(const std::string &msg, DWORD sleep_ms, ConsoleCoord pos, int wAttributes) {
        return slow_print(msg, sleep_ms, pos, false, wAttributes);
    }
    Console &Console::slow_print_then(const std::string &msg, int wAttributes) {
        return slow_print(msg, wAttributes, false);
    }
    Console &Console::slow_print_then(const std::string &msg, ConsoleCoord pos) {
        return slow_print(msg, pos, false);
    }

#pragma endregion

#pragma region console_basic_func

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


    void Console::set_cursor_visible(HANDLE handle, bool visible) {
        CONSOLE_CURSOR_INFO new_cursor_info{};
        new_cursor_info.bVisible = visible;
        new_cursor_info.dwSize = 1;
        SetConsoleCursorInfo(handle, &new_cursor_info);
    }

    Console &Console::enable_cursor_display(bool visible) {
        set_cursor_visible(std_output, visible);
        return *this;
    }

    /**
    @param x - horizontal
    @param y - vertical
*/
    Console &Console::set_console_cur_pos(int x, int y) {
        COORD console_size = get_console_size();

        //    logger.flog_msg_debug("Getting Console size: (%d, %d)\n", console_size.X, console_size.Y);

        if (x > console_size.X || y > console_size.Y || x < 0 || y < 0) {
            debug_log_coord(x, y, "Invalid pos");
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

    ConsoleCoord Console::get_console_cur_pos() {
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(std_output, &info);

        //    debug_log_console_info(std_output);

        return ConsoleCoord(info.dwCursorPosition);
    }

    Console &Console::set_console_text_attr(int wAttributes) {
        SetConsoleTextAttribute(std_output, WORD(wAttributes));
        return *this;
    }
    const HANDLE &Console::get_std_output() const {
        return std_output;
    }

#pragma endregion
}// namespace underpants