#pragma once
#ifndef TYPES_HPP_
#define TYPES_HPP_
#include <Windows.h>

DWORD operator"" _s(long double seconds) {
    return u_int(seconds * 1000);
}

#endif// !TYPES_HPP_