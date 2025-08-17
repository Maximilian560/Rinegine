#pragma once

#define main(...) \
    static_assert(false, "❌ Use rg_main() instead of main().\n" \
                        "   Entry point is managed by Rinegine engine.")

#define wmain(...) \
    static_assert(false, "❌ Use rg_main() instead of wmain().\n" \
                         "   Entry point is managed by Rinegine engine.")

#define WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow) \
    static_assert(false, "❌ Use rg_main() instead of WinMain().\n" \
                         "   Entry point is managed by Rinegine engine.")

#define wWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow) \
    static_assert(false, "❌ Use rg_main() instead of wWinMain().\n" \
                         "   Entry point is managed by Rinegine engine.")

#ifdef _UNICODE
    #define _tmain wmain
#else
    #define _tmain main
#endif

#define rg_main(...) 
#undef main\
#undef wmain\
#undef WinMain\
#undef wWinMain\
#if defined(RG_WIN) && defined(RG_UTF)\
int wmain(int argc, wchar_t *argv[])\
#else\
int main(int argc, char *argv[])\
#endif\
{\
  return Rinegine::Kernel::InterPoint(argc,argv);\
}\
Rinegine::Kernel::InterPoint(argc,argv,in...)
