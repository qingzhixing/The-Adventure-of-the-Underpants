#include "console.hpp"
#include "debug.hpp"

Console console;

Console::Console()
{
	std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	hide_console_cursor(std_output);
	/*
		UNICODE: 65001
		GBK: 936
	*/
	SetConsoleOutputCP(936);
}

void Console::slow_print(const char *msg, DWORD sleep_ms, SHORT x, SHORT y)
{
	COORD old_pos = get_console_cur_pos();
	set_console_cur_pos(x, y);

	const char *pointer = msg;
	while (*pointer)
	{
		putchar(*pointer++);
		Sleep(sleep_ms);
	}

	set_console_cur_pos(old_pos);
}
void Console::clear_screen()
{
	COORD coord_screen = {0, 0}; // home for the cursor
	DWORD c_chars_written;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD console_size;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(std_output, &csbi))
	{
		return;
	}

	console_size = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.
	if (!FillConsoleOutputCharacter(std_output,		   // Handle to console screen buffer
									(TCHAR)' ',		   // Character to write to the buffer
									console_size,	   // Number of cells to write
									coord_screen,	   // Coordinates of first cell
									&c_chars_written)) // Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.
	if (!GetConsoleScreenBufferInfo(std_output, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.
	if (!FillConsoleOutputAttribute(std_output,		   // Handle to console screen buffer
									csbi.wAttributes,  // Character attributes to use
									console_size,	   // Number of cells to set attribute
									coord_screen,	   // Coordinates of first cell
									&c_chars_written)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(std_output, coord_screen);
}

void Console::hide_console_cursor(HANDLE handle)
{
	CONSOLE_CURSOR_INFO new_cursor_info = {};
	new_cursor_info.bVisible = 0;
	new_cursor_info.dwSize = 1;
	SetConsoleCursorInfo(handle, &new_cursor_info);
}

/**
	@param x - horizontal
	@param y - vertical
*/
void Console::set_console_cur_pos(SHORT x, SHORT y)
{
	COORD console_size = get_console_size();

	if (x > console_size.X || y > console_size.Y)
		return;
	COORD new_pos({x, y});
	SetConsoleCursorPosition(std_output, new_pos);
}

void Console::set_console_cur_pos(COORD pos)
{
	set_console_cur_pos(pos.X, pos.Y);
}

COORD Console::get_console_size()
{
	COORD size;

	CONSOLE_SCREEN_BUFFER_INFO console_info;
	GetConsoleScreenBufferInfo(std_output, &console_info);
	SMALL_RECT sr_window = console_info.srWindow;

	SHORT new_row, new_column;
	new_row = sr_window.Right - sr_window.Left + 1;
	new_column = sr_window.Bottom - sr_window.Top + 1;

	size.X = new_row;
	size.Y = new_column;

	return size;
}

COORD Console::get_console_cur_pos()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	GetConsoleScreenBufferInfoEx(std_output, &info);

	return info.dwCursorPosition;
}