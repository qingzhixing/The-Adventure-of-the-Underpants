#pragma once
#ifndef TYPES_HPP_
#define TYPES_HPP_
#include <Windows.h>

namespace underpants {
    DWORD operator"" _s(long double seconds);
}
#endif// !TYPES_HPP_