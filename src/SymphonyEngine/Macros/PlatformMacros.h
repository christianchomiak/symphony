#pragma once

#ifdef _DEBUG
#   define DEBUG_ONLY(...) __VA_ARGS__
#else
#   define DEBUG_ONLY(...)
#endif