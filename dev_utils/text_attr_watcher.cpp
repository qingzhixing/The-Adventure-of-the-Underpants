#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    unsigned short basic_text_attr = 7;
    HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);
    for (unsigned short attr = 1; attr <= 60; attr++)
    {
        SetConsoleTextAttribute(std_output, basic_text_attr);
        printf("text attr: %d, display ", attr);
        SetConsoleTextAttribute(std_output, attr);
        printf("TEXT 123abc");
        SetConsoleTextAttribute(std_output, basic_text_attr);
        puts("");
    }
    getchar();
    return 0;
}