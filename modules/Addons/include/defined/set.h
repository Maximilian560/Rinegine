#pragma once // Предотвращает повторное включение данного заголовочного файла

#if defined(RG_SYS_WINDOWS) && defined(RG_NETWORK)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include "defined/set.h" // Включает основные определения, используемые в проекте

#include "convert/set.h"

#include "debug/set.h"

#include "allocator/set.h"

// #include "pointer.h"
// #include "raw_array.h"
// #include "pointers.h"
// #include "FuncPointer.h"
// #include "array.h" // Включает определения для работы с массивами
// #include "matrix.h" // Включает определения для работы с матрицами
// #include "matrix3D.h" // Включает определения для работы с трёхмерными матрицами
// #include "map.h"
// #include "random.h"

#include "types/set.h"

#include "files/set.h"
//#include "lang.h" // Включает определения, связанные с языковыми настройками

// #ifdef RG_GC_ENABLED
// #include "GCallocator.h"
// #endif


// #ifdef RG_ENCODING
// #include "encoding.h"
// #endif

#include "init/set.h"

//#ifndef RG_GRAPH
#include "main/set.h"
//#endif
//#include "timer.h"

// Комментарии сгенерированы с помощью GPT-4
