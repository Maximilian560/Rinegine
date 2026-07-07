#pragma once

#ifdef RG_ALL_ADDONS
// #define SL_ContestSilhouette
#define RG_Useless_addon
#define RG_POV_CAM
#define RG_WEB_SERVER
#define RG_JOYSTICK
#define RG_LANG
#define RG_PLAYER
#define RG_META_PARSE
#define RG_MOD_MANAGER
#define RG_TESTS
#define RG_GUI
#endif

#ifdef RG_FPS_CAM
#define RG_GRAPH
#endif

#ifdef RG_WEB_SERVER
#define RG_NETWORK
#endif

#if defined(RG_JOYSTICK) || defined(RG_GUI)
#define RG_GRAPH
#endif

#if defined(RG_MOD_MANAGER) && !defined(RG_META_PARSE) 
#define RG_META_PARSE
#endif