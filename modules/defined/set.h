#pragma once // Предотвращает повторное включение данного заголовочного файла

#include "defined.h" // Включает основные определения, используемые в проекте

#include "folder.h"

#include "debug.h"

#include "allocator.h" // Включает определения для работы с аллокатором памяти

#include "readfiles.h" // Включает функционал для чтения файлов

#include "array.h" // Включает определения для работы с массивами

#include "matrix.h" // Включает определения для работы с матрицами

#include "lang.h" // Включает определения, связанные с языковыми настройками

#ifdef RG_GC_ENABLED
    #include "GCallocator.h"
#endif

#include "pointer.h"

#include "FuncPointer.h"

#include "rg_main.h"

#include "otherDefine.h"

#include "rinegine.h" // Включает основные определения движка RinEngine

#include "init.h"
// Комментарии сгенерированы с помощью GPT-4
