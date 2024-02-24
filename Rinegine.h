#pragma once


#ifdef RG_ALL_MODULS
  #define RG_GRAPH
  #define RG_HTTPS
  #define RG_SOUND
  #define RG_EXPEREMENTAL
#endif
#ifdef RG_WIP_CONTENT
  #include "RinegineWIP/set.h"
#else
  #include "defined/set.h"
  #ifdef RG_GRAPH
    #include "graphics/set.h"
  #endif.

  #ifdef RG_EXPEREMENTAL
    #include "experemental/set.h"
  #endif

  #ifdef RG_ADDONS
    #include "addons/set.h"
  #endif

  #ifdef RG_HTTPS
    #include "https/set.h"
  #endif

  #ifdef RG_SOUND
    #include "sound/set.h"
  #endif
#endif