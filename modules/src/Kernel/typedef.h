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
} // namespace Rinegine
