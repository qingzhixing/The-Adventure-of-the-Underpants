#pragma once
#ifndef _OUTPUT_HPP_
#define _OUTPUT_HPP_

#include <iostream>
#include <Windows.h>

#define LOW_SPEED 150
#define MID_SPEED 80
#define HIGH_SPEED 20
void slow_print(const char* msg,DWORD sleep_ms);
void clear_screen();

#endif // !_OUTPUT_HPP_