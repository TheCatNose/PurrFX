#pragma once

#define CLASS_MAKE_NON_COPYABLE(className) \
    private: \
    className& operator=(const className&) = delete; \
    className(const className&) = delete;

#define CLASS_USE_DEFAULT_CONSTRUCTOR(className) \
    public: \
    className() = default; \
    private:

#define CLASS_DISABLE_DEFAULT_CONSTRUCTOR(className) \
    private: \
    className() = delete;
