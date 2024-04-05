#include "output.hpp"

void slow_print(const char* msg,DWORD sleep_ms){
    const char* pointer = msg;
    while(*pointer){
        putchar(*pointer++);
        Sleep(sleep_ms);
    }
}