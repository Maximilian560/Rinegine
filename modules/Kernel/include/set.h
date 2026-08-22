#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/kernel"

#ifndef RG_DEBUG
#define RG_DEBUG
#endif
#include "setup.hpp"
#include "include.h"
#include "typedef.h"
#include "encoding.h"
#include "general.h"

#include "include.h"        //[done]
#include "defined/set.h"    //[done]
#include "debug/set.h"      //[done]
#include "impl.hpp"         //[done]
#include "util.hpp"         //[done]
#include "allocator/set.h"  //[done]
#include "types/set.hpp"    //[done]
#include "convert/set.h"    //[done]
#include "pointer/set.h"    //[todo]
#include "array/set.h"      //[done]
#include "matrix/set.hpp"   //[todo]
#include "map/set.h"        //[todo]
#include "files/set.h"      //[done]
#include "defined.hpp"      //[done]

#include "main.h"
#include "kernel.h"
#include "other_define.h"
#include "interPoint.h"