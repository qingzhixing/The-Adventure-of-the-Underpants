#pragma once

#ifndef NDEBUG
#include <iostream>
#define DEBUG(CodeSegment) {CodeSegment;}
#define JUDGE(CONDITION) \
   if(CONDITION){}        \
   else{ printf("Condition false: %s\n",(#CONDITION)); }
#define ASSERT(CONDITION) \
   if(CONDITION){}        \
   else{ \
		printf("Condition false: %s\n",(#CONDITION)); \
		Halt();\
	}
#else
#define DEBUG(CodeSegment) ((void)0)
#define JUDGE(CONDITION) ((void)0)
#define ASSERT(CONDITION) ((void)0)
#endif

#define HALT(CodeSegment)	while(true){CodeSegment;}