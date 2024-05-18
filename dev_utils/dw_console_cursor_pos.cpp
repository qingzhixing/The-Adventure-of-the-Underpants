#include <iostream>
#include <windows.h>

void print_pos() {
    // Get the current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD cursorPos = csbi.dwCursorPosition;
    printf("#\nCursor position: (%d, %d)\n", cursorPos.X, cursorPos.Y);
}

void print_pos_ex() {
    CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
    csbiex.cbSize = sizeof(csbiex);
    GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &csbiex);
    COORD cursorPos = csbiex.dwCursorPosition;
    printf("^\nCursor position: (%d, %d)\n", cursorPos.X, cursorPos.Y);
}

int main() {
    print_pos();
    // Move the cursor to position (10, 10)
    COORD cursorPos = {10, 10};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
    print_pos_ex();

    getchar();
    return 0;
}