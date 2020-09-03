#pragma once
// Cross-platform file/path/folder definitions

#include <string>

namespace PurrFX
{
#ifdef _WIN32
		typedef wchar_t      pathchar_t;
		typedef std::wstring pathstring;
#define PATHSTR(string) L##string
#else
		typedef char         pathchar_t;
		typedef std::string  pathstring;
#define PATHSTR(string) string
#endif
}