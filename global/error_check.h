#pragma once

#include "core.h"

#include <string>
#include <iostream>
#include <cassert>

#ifdef DEBUG
#define GL_CALL(function) \
    do { \
        function; \
        check_error(); \
    } while (0)
#else
#define GL_CALL(function) \
    function;
#endif

void check_error();
