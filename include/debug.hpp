#pragma once
#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#ifndef NDEBUG
#include <iostream>
#define DEBUG(CodeSegment) \
   {                       \
      CodeSegment;         \
   }
#define JUDGE(CONDITION)                             \
   if (CONDITION)                                    \
   {                                                 \
   }                                                 \
   else                                              \
   {                                                 \
      printf("Condition false: %s\n", (#CONDITION)); \
   }
#define ASSERT(CONDITION)                            \
   if (CONDITION)                                    \
   {                                                 \
   }                                                 \
   else                                              \
   {                                                 \
      printf("Condition false: %s\n", (#CONDITION)); \
      HALT();                                        \
   }
#else
#define DEBUG(CodeSegment) ((void)0)
#define JUDGE(CONDITION) ((void)0)
#define ASSERT(CONDITION) ((void)0)
#endif

#define HALT(CodeSegment) \
   while (true)           \
   {                      \
      CodeSegment;        \
   }
#define DELETE_ME "DELETE ME! "

#endif // !_DEBUG_HPP_