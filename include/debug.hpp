#pragma once
#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <fstream>
#include <iostream>

#ifndef NDEBUG
#define DEBUG_ENABLED true
#define DEBUG(CodeSegment) \
    do {                   \
        CodeSegment;       \
    } while (0)
#define JUDGE(CONDITION)                               \
    if (CONDITION) {                                   \
    } else {                                           \
        printf("Condition false: %s\n", (#CONDITION)); \
    }
#define ASSERT(CONDITION)                              \
    if (CONDITION) {                                   \
    } else {                                           \
        printf("Condition false: %s\n", (#CONDITION)); \
        HALT();                                        \
    }
#else
#define DEBUG_ENABLED false
#define LOG_DEBUG(CodeSegment) ((void) 0)
#define JUDGE(CONDITION) ((void) 0)
#define ASSERT(CONDITION) ((void) 0)
#endif

#define HALT(CodeSegment) \
    do {                  \
        CodeSegment;      \
    } while (true)
#define DELETE_ME "DELETE ME! "

#define CANCEL(CodeSegment) ((void) 0)

#endif// !DEBUG_HPP_