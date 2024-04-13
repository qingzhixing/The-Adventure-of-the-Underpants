#pragma once
#ifndef _TYPES_HPP_
#define _TYPES_HPP_
#include <Windows.h>

DWORD operator"" _s(long double secounds)
{
    return u_int(secounds * 1000);
}

#endif // !_TYPES_HPP_