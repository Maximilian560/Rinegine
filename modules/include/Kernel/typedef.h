#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/typedef"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef int16_t int16;
#ifdef RG_WIN
typedef __int32 int32;
#else
typedef __int32_t int32;
#ifndef WORD
typedef uint16_t WORD;
#endif
#ifndef DWORD
typedef uint32_t DWORD;
#endif
#endif
typedef long int lint;
typedef long unsigned int luint;

namespace Rinegine {
  enum CONSOLE_COLOR {
    C_BLACK = 0,
    C_RED,
    C_GREEN,
    C_YELLOW,
    C_BLUE,
    C_MAGENTA,
    C_CYAN,
    C_WHITE,
    C_TEXT = 30,
    C_BACKGROUND = 40,
    C_BRIGHT = 60
  };

  namespace Log {
    enum Types { CRITICAL, ERR, WARNING, INFO, DEBUG, MEM };
  }
  enum Mouse_State {
    MNPress,
    MPress,
    MRelease,
  };

  enum ErrorRinegine {
    RG_OWN_ERROR = -1,                 //-1
    RG_ERROR_WINDOWS_NO_CREATED,       // 0
    RG_ERROR_FREETYPE,                 // 1
    RG_ERROR_FREETYPE_FONTS_NOT_FOUND, // 2
    RG_ERROR_OUT_OF_MEMORY,            // 3
    RG_ERROR_FREETYPE_CHAR_NOT_LOAD,   // 4
    RG_ERROR_GLFW_INIT_ERR,            // 5
    RG_ERROR_FILE_NOT_FOUND,           // 6
    RG_ERROR_RGARRAY_SIZE0,            // 7
    RG_ERROR_RGARRAY_SIZE1,            // 8
    RG_ERROR_RGARRAY_SIZE2,            // 9
    RG_ERROR_LOAD_NOT4CNT_IMAGE,       // 10
    RG_ERROR_MATERIAL_MISUSE,          // 11
    RG_ERROR_RGMATRIX_SIZE0,           // 12
    RG_ERROR_LOAD_TEXTURE,             // 13
    RG_ERROR_PLANET_NOT_FOUND,         // 14
    RG_ERROR_BLOCK_TYPE_INCORRECT,     // 15
    RG_ERROR_FIND_TEXTURE,             // 16
  };

  enum s_delete_errors {
    SD_NO_ERR = 0,
    SD_NO_RG_TYPE,
    SD_PTR_IS_NULLPTR,
    SD_DEALOC_ERROR
  };
  struct DATA_OUT{
    size_t size = 0;
    char magnum[2] = {'R', 'G'};
  };
} // namespace Rinegine
