#pragma once

#define CLASS_MAKE_NON_COPYABLE(className) \
    className& operator=(const className&) = delete; \
    className(const className&) = delete; \
    className() = default;

#define CLASS_DISABLE_DEFAULT_CONSTRUCTOR(className) \
    className() = delete;
