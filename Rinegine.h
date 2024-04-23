#pragma once

#if defined(RG_GLFW_NATIVE_WIN32)
	#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#ifdef RG_WIP_CONTENT
  #include "Rwip/set.h"
#else
  #include "Rmain/set.h"
#endif