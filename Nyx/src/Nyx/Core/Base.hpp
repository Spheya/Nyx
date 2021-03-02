#pragma once

#define NYX_EXPAND_MACRO(x) x
#define NYX_STRINGIFY_MACRO(x) #x

#ifdef NYX_DEBUG
	#ifndef NYX_ENABLE_LOGGER
		#define NYX_ENABLE_LOGGER
	#endif

	#ifndef NYX_ENABLE_ASSERTS
		#define NYX_ENABLE_ASSERTS
	#endif
#endif