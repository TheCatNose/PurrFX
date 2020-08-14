#pragma once

#define CLASS_MAKE_NON_COPYABLE(className) \
    className& operator=(const className&) = delete; \
    className(const className&) = delete;

#define CLASS_USE_DEFAULT_CONSTRUCTOR(className) \
    className() = default;

#define CLASS_DISABLE_DEFAULT_CONSTRUCTOR(className) \
    className() = delete;
