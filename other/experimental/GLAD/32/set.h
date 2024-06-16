#pragma once

#ifndef RG_GL_VERSION
    #define RG_GL_VERSION 33
#endif
#if RG_GL_VERSION == 20
    #include "20/src/glad.h"
#endif

#if RG_GL_VERSION == 33
    #include "33/src/glad.h"
#endif

#if RG_GL_VERSION == 46
    #include "46/src/glad.h"
#endif