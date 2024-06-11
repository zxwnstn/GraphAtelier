#pragma once

#include <stdexcept>

#define DEBUG_BREAK __debugbreak()

#if BUILD_DEBUG
	#define Assert(x) if(!x) { DEBUG_BREAK; throw std::runtime_error(#x); }
#else
	#define Assert(x) x;
#endif
