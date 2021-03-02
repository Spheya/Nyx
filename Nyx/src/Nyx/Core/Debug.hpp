#pragma once

#include "Base.hpp"
#include "Logger.hpp"

#ifdef NYX_DEBUG
	#ifdef NYX_PLATFORM_WINDOWS
		#define NYX_INTERNAL_DISPLAY_DEBUGBREAK_WARNING
		#define NYX_INTERNAL_DEBUGBREAK() __debugbreak()
		#define NYX_INTERNAL_DEBUGBREAK_MESSAGE "Debug break occured"
	#else
		#define NYX_INTERNAL_DISPLAY_DEBUGBREAK_WARNING NYX_CORE_WARN("Debug breaks are not supported on this platform or no platform has been defined.");
		#define NYX_INTERNAL_DEBUGBREAK()
		#define NYX_INTERNAL_DEBUGBREAK_MESSAGE "A debug break would've occured"
	#endif		
#else
	#define NYX_INTERNAL_DISPLAY_DEBUGBREAK_WARNING
	#define NYX_INTERNAL_DEBUGBREAK()
	#define NYX_INTERNAL_DEBUGBREAK_MESSAGE "A debug break would've occured"
#endif

#define NYX_INTERNAL_DEBUGBREAK_IMPL(type, msg) { NYX##type##ERROR("{0}: {1}", NYX_INTERNAL_DEBUGBREAK_MESSAGE, msg); NYX_INTERNAL_DEBUGBREAK(); }
#define NYX_DEBUGBREAK(msg) NYX_INTERNAL_DEBUGBREAK_IMPL(_, msg)
#define NYX_CORE_DEBUGBREAK(msg) NYX_INTERNAL_DEBUGBREAK_IMPL(_CORE_, msg)

#ifdef NYX_ENABLE_ASSERTS

	#define NYX_ASSERT(expression, msg) {if(!(expression)){NYX_ERROR("Assertion failed: {0}", msg);NYX_DEBUGBREAK("Assertion failed");}}
	#define NYX_CORE_ASSERT(expression, msg) {if(!(expression)){NYX_CORE_ERROR("Assertion failed: {0}", msg);NYX_CORE_DEBUGBREAK("Assertion failed");}}

	#define NYX_WARN_ASSERT(expression, msg) {if(!(expression)){NYX_WARN("Assertion failed: {0}", msg);}}
	#define NYX_CORE_WARN_ASSERT(expression, msg) {if(!(expression)){NYX_CORE_WARN("Assertion failed: {0}", msg);}}

#else
	
	#define NYX_ASSERT(...)
	#define NYX_CORE_ASSERT(...)

	#define NYX_WARN_ASSERT(...)
	#define NYX_CORE_WARN_ASSERT(...)

#endif