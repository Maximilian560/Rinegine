#pragma once

#include "defined/set.h"

#ifdef RG_ALL_MODULS
  #define RG_GRAPH
  #define RG_EXPEREMENTAL
  #define RG_HTTPS
  #define RG_SOUND
#endif

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