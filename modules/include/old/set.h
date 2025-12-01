#pragma once



#ifdef RG_ALL_MODULS
  #define RG_GRAPH
  #define RG_NETWORK
  #define RG_SOUND
  #define RG_NEURAL
  #define RG_EXPEREMENTAL
#endif
#if defined(RG_GRAPH) && defined(RG_ENCODING)
  #warning RG_GRAPH always include RG_ENCODING, you shouldn''t define RG_ENCODING when RG_GRAPH is defined
  #undef RG_ENCODING
#endif

#ifdef RG_ADDONS
  #include "addons/modules.h"
#endif

#include "defined/set.h"


#ifdef RG_GRAPH
  #include "graphics/set.h"
#endif

#ifdef RG_NETWORK
  #include "network/set.h"
#endif

#ifdef RG_SOUND
  #include "sound/set.h"
#endif

#ifdef RG_NEURAL
  #include "neural/set.h"
#endif

#ifdef RG_EXPEREMENTAL
  #include "experimental/set.h"
#endif

#ifdef RG_ADDONS
  #include "addons/set.h"
#endif


#ifndef  RG_DEF_INIT
#define  RG_DEF_INIT
#endif
#ifndef  RG_GRAPH_INIT
#define  RG_GRAPH_INIT
#endif
#ifndef  RG_NETWORK_INIT
#define  RG_NETWORK_INIT
#endif
#ifndef  RG_SOUND_INIT
#define  RG_SOUND_INIT
#endif
#ifndef  RG_NEURAL_INIT
#define  RG_NEURAL_INIT
#endif
#ifndef  RG_EXPEREMENTAL_INIT
#define  RG_EXPEREMENTAL_INIT
#endif
#ifndef  RG_ADDONS_INIT
#define  RG_ADDONS_INIT
#endif

void RG_FullInit(){
  RG_DEF_INIT;
  RG_GRAPH_INIT;
  RG_NETWORK_INIT;
  RG_SOUND_INIT;
  RG_NEURAL_INIT;
  RG_EXPEREMENTAL_INIT;
  RG_ADDONS_INIT;
}

#ifndef  RG_DEF_TERMINATE
#define  RG_DEF_TERMINATE
#endif
#ifndef  RG_GRAPH_TERMINATE
#define  RG_GRAPH_TERMINATE
#endif
#ifndef  RG_NETWORK_TERMINATE
#define  RG_NETWORK_TERMINATE
#endif
#ifndef  RG_SOUND_TERMINATE
#define  RG_SOUND_TERMINATE
#endif
#ifndef  RG_NEURAL_TERMINATE
#define  RG_NEURAL_TERMINATE
#endif
#ifndef  RG_EXPEREMENTAL_TERMINATE
#define  RG_EXPEREMENTAL_TERMINATE
#endif
#ifndef  RG_ADDONS_TERMINATE
#define  RG_ADDONS_TERMINATE
#endif

void RG_FullTerminate() {
  RG_DEF_TERMINATE;
  RG_GRAPH_TERMINATE;
  RG_NETWORK_TERMINATE;
  RG_SOUND_TERMINATE;
  RG_NEURAL_TERMINATE;
  RG_EXPEREMENTAL_TERMINATE;
  RG_ADDONS_TERMINATE;
}

// #undef RG_LOG_DEBUG_2
// #undef RG_LOG_INFO_2
// #undef RG_LOG_WARN_2
// #undef RG_LOG_ERROR_2
// #undef RG_LOG_FATAL_2
// #undef RG_LOG_MEM_2
// #undef RG_LOG_DEBUG_1
// #undef RG_LOG_INFO_1
// #undef RG_LOG_WARN_1
// #undef RG_LOG_ERROR_1
// #undef RG_LOG_FATAL_1
// #undef RG_LOG_MEM_1
#undef RG_LOG_LOCK_DEBUG
#undef RG_LOG_LOCK_INFO
#undef RG_LOG_LOCK_WARN
#undef RG_LOG_LOCK_WARNING
#undef RG_LOG_LOCK_ERROR
#undef RG_LOG_LOCK_FATAL
#undef RG_LOG_LOCK_CRITICAL
#undef RG_LOG_LOCK_MEM
#undef RG_LOG_LOCK_DEBUG_2
#undef RG_LOG_LOCK_INFO_2
#undef RG_LOG_LOCK_WARN_2
#undef RG_LOG_LOCK_ERROR_2
#undef RG_LOG_LOCK_FATAL_2
#undef RG_LOG_LOCK_MEM_2
#undef RG_LOG_LOCK_DEBUG_1
#undef RG_LOG_LOCK_INFO_1
#undef RG_LOG_LOCK_WARN_1
#undef RG_LOG_LOCK_ERROR_1
#undef RG_LOG_LOCK_FATAL_1
#undef RG_LOG_LOCK_MEM_1