#pragma once
#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <iostream>
#include <fstream>

#ifndef NDEBUG
#define DEBUG_ENABLED true
#define DEBUG(CodeSegment) \
	do                     \
	{                      \
		CodeSegment;       \
	} while (0)
#define JUDGE(CONDITION)                               \
	if (CONDITION)                                     \
	{                                                  \
	}                                                  \
	else                                               \
	{                                                  \
		printf("Condition false: %s\n", (#CONDITION)); \
	}
#define ASSERT(CONDITION)                              \
	if (CONDITION)                                     \
	{                                                  \
	}                                                  \
	else                                               \
	{                                                  \
		printf("Condition false: %s\n", (#CONDITION)); \
		HALT();                                        \
	}
#else
#define DEBUG_ENABLED false
#define DEBUG(CodeSegment) ((void)0)
#define JUDGE(CONDITION) ((void)0)
#define ASSERT(CONDITION) ((void)0)
#endif

#define HALT(CodeSegment) \
	do                    \
	{                     \
		CodeSegment;      \
	} while (true)
#define DELETE_ME "DELETE ME! "

#define CANCEL(CodeSegment) ((void)0)

std::string get_file_content(const char *file);

#endif // !_DEBUG_HPP_