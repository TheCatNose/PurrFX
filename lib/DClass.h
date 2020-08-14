#pragma once

#define CLASS_MAKE_NON_COPYABLE(className) \
    className& operator=(const className&) = delete; \
    className(const className&) = delete; \
    className() = default;
