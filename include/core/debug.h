#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <iostream>

#ifdef DEBUGMODE
#define DEBUG(module, procedure, ...)            \
    printf(module "::" procedure "::STARTED\n"); \
    __VA_ARGS__;                                 \
    printf(module "::" procedure "::FINISHED\n")
#define DEBUGC(vec)            \
    printf(#vec ": ");         \
    for (auto const &v : vec)  \
        std::cout << v << " "; \
    printf("\n");

#else
#define DEBUG(module, procedure, ...) __VA_ARGS__;
#define DEBUGC(vec) ;
#endif

#endif