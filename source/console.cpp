#include "console.hpp"

Console::Console()
{
	std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	hide_console_cursor(std_output);
}

void Console::slow_print(const char *msg, DWORD sleep_ms)
{
	const char *pointer = msg;
	while (*pointer)
	{
		putchar(*pointer++);
		Sleep(sleep_ms);
	}
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