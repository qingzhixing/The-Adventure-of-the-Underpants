#pragma once
#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#ifndef NDEBUG
#define DEBUG_ENABLED true
#include <iostream>
#define DEBUG(CodeSegment) \
   do                      \
   {                       \
      CodeSegment;         \
   } while (0)
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
#define DEBUG_ENABLED false
#define DEBUG(CodeSegment) ((void)0)
#define JUDGE(CONDITION) ((void)0)
#define ASSERT(CONDITION) ((void)0)
#endif

#define HALT(CodeSegment) \
   do                     \
   {                      \
      CodeSegment;        \
   } while (true)
#define DELETE_ME "DELETE ME! "

#endif // !_DEBUG_HPP_