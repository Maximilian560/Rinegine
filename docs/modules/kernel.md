# Kernel Module

The Kernel module is the core of Rinegine. It provides custom memory management, logging, string utilities, containers, mathematical types, random number generation, file operations, and platform abstraction.

## Inclusion Chain

The `Kernel/set.h` includes sub-headers in this strict order:

```
version.h → include.h → encoding.h → define.h → typedef.h → kernel.h → other_define.h → interPoint.h
```

The documentation below follows this same order.

---

## 1. version.h

### Macros

```cpp
#define RG_V_MAJOR 0
#define RG_V_MINOR 3
#define RG_V_PATCH 0
#define RG_V_WIP   1
```

### Constants

```cpp
namespace Rinegine {
    constexpr const char* VERSION = "0.3.0";
    constexpr const char* EDITION = "Beginning";
}
```

### Functions

```cpp
void GetVersion(int& major, int& minor, int& patch, int& wip);
void GetVersion(int& major, int& minor, int& patch);
```

---

## 2. include.h

Pulls in standard and platform headers required by all subsequent headers:

```cpp
#include <iostream>
#include <cstdint>
#include <functional>
#include <type_traits>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <sys/mman.h>
#endif
```

---

## 3. encoding.h

UTF-8 encoding/decoding utilities:

```cpp
namespace Rinegine::Kernel {
    std::wstring utf8_decode(const std::string& in);   // UTF-8 → wide string
    std::string  utf8_encode(const std::wstring& in);  // Wide string → UTF-8
}
```

---

## 4. define.h

### 4.1 Type Alias

```cpp
typedef unsigned int uint;
```

### 4.2 Platform Detection

| Macro | Condition |
|-------|-----------|
| `RG_x64` | `__x86_64__ \|\| _M_X64 \|\| __aarch64__` |
| `RG_x32` | `__i386__ \|\| _M_IX86 \|\| __arm__` |
| `RG_x86` | `_M_IX86` |
| `RG_WINos`, `RG_WIN`, `RG_Win`, `RG_Windows` | `_WIN32` |
| `RG_Linuxos`, `RG_Linux`, `RG_LINUX`, `RG_LNX` | `__linux__` |

### 4.3 Unicode Toggle

`RG_UTF` is defined when `UNICODE` is set (automatic on Windows). On Linux it is forcibly undefined with `#warning`. When `RG_UTF` is active, `_GLIBCXX_USE_WCHAR_T` is also defined.

### 4.4 Utility Macros

```cpp
#define UINT_MAX 4294967295          // If not already defined
#define rg_min(a, b)  (a < b ? a : b)
#define rg_max(a, b)  (a > b ? a : b)
#define elif          else if
#define to_rvalue(T)  const T&
#define to_rrvalue(T) const T
```

### 4.5 Loop Helpers

**Forward loops (0 to count-1):**

```cpp
RG_FOR_CYCLEi(count)           // int i
RG_FOR_CYCLEj(count)           // int j
RG_FOR_CYCLEk(count)           // int k
RG_FOR_CYCLEx(count)           // int x
RG_FOR_CYCLEy(count)           // int y
RG_FOR_CYCLEz(count)           // int z
RG_FOR_CYCLE(name, count)      // int <name>
RG_FOR_CYCLEty(type, name, count)  // <type> <name>
```

**Reverse loops (count down to 0 inclusive):**

```cpp
RG_RevFOR_CYCLEi(count)        // int i
RG_RevFOR_CYCLEj(count)        // int j
RG_RevFOR_CYCLEk(count)        // int k
RG_RevFOR_CYCLEx(count)        // int x
RG_RevFOR_CYCLEy(count)        // int y
RG_RevFOR_CYCLEz(count)        // int z
RG_FOR_CYCLErev(name, count)   // int <name>
RG_RevFOR_CYCLE(type, name, count)  // <type> <name>
```

### 4.6 String/Stream Type Switching

When `RG_UTF` is **defined**:

```cpp
#define rg_cout       std::wcout
#define rg_ostrem     std::wostream
#define rg_cin        std::wcin
#define rg_string     std::wstring
#define rg_char       wchar_t
#define rg_to_string_(in)  std::to_wstring(in)
#define RG_L          L""
```

When `RG_UTF` is **not defined**:

```cpp
#define rg_cout       std::cout
#define rg_ostrem     std::ostream
#define rg_cin        std::cin
#define rg_string     std::string
#define rg_char       char
#define rg_to_string_(in)  std::to_string(in)
#define RG_L          // empty
```

### 4.7 Configuration Constants

```cpp
#define RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER  16
#define RG_ERROR_STRING    "E6filenofound"
#define RG_ERROR_WSTRING   L"E6filenofound"
```

### 4.8 Debug Counters

```cpp
[[maybe_unused]] static uint  rg_count_temp = 0;
[[maybe_unused]] static int   rg_count_temp_deb = 0;

#define rg_count         // Prints "<counter>, <file>:<line>", increments
#define rg_count_clear   // Resets rg_count_temp to 0
#define rg_count_deb     // Logs via RG_LOG_LOCK_DEBUG with counter
#define rg_count_deb_clear  // Resets rg_count_temp_deb to 0
```

### 4.9 Conversion Functions

```cpp
inline std::wstring rg_to_stringw(const std::string&);   // utf8_decode
inline std::wstring rg_to_stringw(const std::wstring&);  // identity
inline std::string  rg_to_stringa(const std::string&);   // identity
inline std::string  rg_to_stringa(const std::wstring&);  // utf8_encode
```

With `RG_UTF`:

```cpp
inline rg_string rg_to_string(const int&);           // to_wstring
inline rg_string rg_to_string(const std::string&);   // utf8_decode
inline rg_string rg_to_string(const char*);          // utf8_decode
inline rg_string rg_to_string(const wchar_t*);       // identity
inline std::wostream& operator<<(std::wostream&, const std::string&);
```

Without `RG_UTF`:

```cpp
inline rg_string rg_to_string(const std::string&);   // identity
inline rg_string rg_to_string(const std::wstring&);  // utf8_encode
inline rg_string rg_to_string(const char*);          // identity
inline rg_string rg_to_string(const wchar_t*);       // utf8_encode
```

### 4.10 Logging Macros

All logging is guarded by `#ifdef RG_DEBUG`. When `RG_DEBUG` is **not** defined, every log macro expands to `{}`.

**Log levels** (defined later in `typedef.h`, referenced here):

| Level | Enum value |
|-------|------------|
| `CRITICAL` | 0 |
| `ERR` | 1 |
| `WARNING` | 2 |
| `INFO` | 3 |
| `DEBUG` | 4 |
| `MEM` | 5 |

**Variadic helper** — selects 1- or 2-argument version:

```cpp
#define GET_MACRO(_1, _2, NAME, ...) NAME
```

**Public macros** — pass `__FILE__`, `__LINE__`:

```cpp
RG_LOG_DEBUG("msg")
RG_LOG_INFO("msg")
RG_LOG_WARN("msg")          // also RG_LOG_WARNING
RG_LOG_ERROR("msg")
RG_LOG_FATAL("msg")         // also RG_LOG_CRITICAL
RG_LOG_MEM("msg")
```

Two-argument form:

```cpp
RG_LOG_DEBUG("msg", extra_flag, "filename", line)
```

Each expands to `Kernel::Debug::addl(Log::LEVEL, msg, extra, __FILE__, __LINE__)`.

**Lock macros** — when `RGLOCK_DEBUG` is defined, use `RG_HERE_FILE_NAME` and line `-1`:

```cpp
RG_LOG_LOCK_DEBUG("msg")
RG_LOG_LOCK_INFO("msg")
RG_LOG_LOCK_WARN("msg")
RG_LOG_LOCK_ERROR("msg")
RG_LOG_LOCK_FATAL("msg")
RG_LOG_LOCK_CRITICAL("msg")
RG_LOG_LOCK_MEM("msg")
```

When `RGLOCK_DEBUG` is **not** defined, lock macros alias the public macros (with `__FILE__`, `__LINE__`).

---

## 5. typedef.h

Also sets `RG_HERE_FILE_NAME` to `"kernel/typedef"`.

### Type Aliases

```cpp
typedef unsigned int    uint;
typedef unsigned char   uchar;
typedef uint8_t         uint8;
typedef uint16_t        uint16;
typedef int16_t         int16;
// Windows: typedef __int32 int32;
// Linux:   typedef __int32_t int32;
typedef long int        lint;
typedef long unsigned int luint;

// If not already defined:
typedef uint16_t WORD;
typedef uint32_t DWORD;
```

### CONSOLE_COLOR

```cpp
enum CONSOLE_COLOR {
    C_BLACK = 0, C_RED, C_GREEN, C_YELLOW, C_BLUE, C_MAGENTA, C_CYAN, C_WHITE,
    C_TEXT = 30, C_BACKGROUND = 40, C_BRIGHT = 60
};
```

### Log::Types

```cpp
namespace Rinegine::Log {
    enum Types { CRITICAL, ERR, WARNING, INFO, DEBUG, MEM };
}
```

### Mouse_State

```cpp
enum Mouse_State { MNPress, MPress, MRelease };
```

### ErrorRinegine

```cpp
enum ErrorRinegine {
    RG_OWN_ERROR = -1,                  // -1
    RG_ERROR_WINDOWS_NO_CREATED,        //  0
    RG_ERROR_FREETYPE,                  //  1
    RG_ERROR_FREETYPE_FONTS_NOT_FOUND,  //  2
    RG_ERROR_OUT_OF_MEMORY,             //  3
    RG_ERROR_FREETYPE_CHAR_NOT_LOAD,    //  4
    RG_ERROR_GLFW_INIT_ERR,             //  5
    RG_ERROR_FILE_NOT_FOUND,            //  6
    RG_ERROR_RGARRAY_SIZE0,             //  7
    RG_ERROR_RGARRAY_SIZE1,             //  8
    RG_ERROR_RGARRAY_SIZE2,             //  9
    RG_ERROR_LOAD_NOT4CNT_IMAGE,        // 10
    RG_ERROR_MATERIAL_MISUSE,           // 11
    RG_ERROR_RGMATRIX_SIZE0,            // 12
    RG_ERROR_LOAD_TEXTURE,              // 13
    RG_ERROR_PLANET_NOT_FOUND,          // 14
    RG_ERROR_BLOCK_TYPE_INCORRECT,      // 15
    RG_ERROR_FIND_TEXTURE,              // 16
};
```

### s_delete_errors

```cpp
enum s_delete_errors {
    SD_NO_ERR = 0,         // Success
    SD_NO_RG_TYPE,         // Pointer not from RG allocator
    SD_PTR_IS_NULLPTR,     // Null pointer
    SD_DEALOC_ERROR        // System deallocation failed
};
```

### DATA_OUT

Memory block header stored before every RG-allocated pointer:

```cpp
struct DATA_OUT {
    size_t size = 0;            // User data size in bytes
    char magnum[2] = {'R', 'G'};  // Magic number for validation
};
```

---

## 6. kernel.h

Sets `RG_HERE_FILE_NAME` to `"kernel/kernel"`. This is the largest file (~1247 lines).

### 6.1 Forward Declarations and Global Variables

```cpp
namespace Rinegine::Kernel {

    extern std::vector<std::string>  AMainArguments;
    extern std::vector<std::wstring> WMainArguments;

    template<class K, class V> struct MapData;   // Forward declaration

    template<class T> class Matrix;              // Forward declaration
    template<class T> class Array;               // Forward declaration

    extern std::string  AMainFolder;
    extern std::wstring WMainFolder;
    extern rg_string    MainFolder;
    extern uint8_t      RG_D_W_L;
```

### 6.2 Entry Point Declarations

```cpp
    int rg_main();   // User-defined entry point (declared here)

    int InterPoint(int argc, char** argv, int (*user_main)() = rg_main);
    int InterPoint(int argc, wchar_t** argv, int (*user_main)() = rg_main);

    void init();     // [todo]
```

### 6.3 Lock Namespace (Memory Management Declarations)

```cpp
    namespace Lock {
        struct LogVars;
        extern LogVars _vars;

        void*  s_new(const size_t&);                  // Allocate with tracking
        void*  s_fast_new(const size_t&);             // Fast allocate (no tracking)
        uint   s_delete(void*);                       // Free with validation
        void   s_fast_delete(void*);                  // Fast free
        bool   s_rawmemtest(const char*);             // Check magic at raw address
        int    s_memtest(const void*);                // Full pointer validation
        size_t s_get_size(const void*);               // Get block size in bytes
        size_t s_get_typesize(const void*);           // Get element type size
        void   addl(Log::Types, std::string, bool, std::string, int);
        void   addl(Log::Types, std::wstring, bool, std::wstring, int);

        template<class T> struct CountPointers;        // [declared, not defined]
    }
```

### 6.4 String Conversion

```cpp
    std::wstring to_stringw(const std::string&);
    std::wstring to_stringw(const std::wstring&);
    std::string  to_stringa(const std::string&);
    std::string  to_stringa(const std::wstring&);

    rg_string to_string(const std::string&);   // [outdate]
    rg_string to_string(const std::wstring&);  // [outdate]
```

### 6.5 POINT2D

```cpp
    template<class T>
    struct POINT2D {
        T x = T(), y = T();

        POINT2D();
        POINT2D(T x_, T y_);

        POINT2D  operator+(POINT2D p);
        POINT2D  operator-(POINT2D p);
        POINT2D& operator+=(POINT2D p);
        POINT2D& operator-=(POINT2D p);

        bool operator==(POINT2D p);   // x==p.x && y==p.y
        bool operator>=(POINT2D p);   // x>=p.x && y>=p.y
        bool operator<=(POINT2D p);
        bool operator>(POINT2D p);
        bool operator<(POINT2D p);

        T& operator[](uint i);        // i=0→x, i=1→y  via (&x)[i%2]
    };
```

### 6.6 POINT3D, COLOR3D, COLOR4D (Declared Only)

```cpp
    template<class T> struct POINT3D { T x, y, z; /* operators declared, not defined */ };
    template<class T> struct COLOR3D { T r, g, b; /* operators declared, not defined */ };
    template<class T> struct COLOR4D { T r, g, b, a; /* ==, != declared */ };
```

Marked `[outdate soon]` — use `vec3`, `vec4` instead.

### 6.7 Keyboard Input

```cpp
    int KeyIs(int key, bool hold);
    int KeyIsPress(int key, bool hold);
    int TestKeyIs(int key, bool hold);
```

### 6.8 SysTime

```cpp
    class SysTime {
        struct SysTimeVar;
        static SysTimeVar _vars;
    public:
        static void update();

        // Wide string versions
        static std::wstring YearW();
        static std::wstring MonthW();
        static std::wstring DayOfWeekW();
        static std::wstring DayW();
        static std::wstring HourW();
        static std::wstring MinuteW();
        static std::wstring SecondW();
        static std::wstring MillisecondsW();

        // ANSI string versions
        static std::string YearA();
        static std::string MonthA();
        static std::string DayOfWeekA();
        static std::string DayA();
        static std::string HourA();
        static std::string MinuteA();
        static std::string SecondA();
        static std::string MillisecondsA();

        // [outdate] — use A/W versions
        static rg_string Year();
        static rg_string Month();
        static rg_string DayOfWeek();
        static rg_string Day();
        static rg_string Hour();
        static rg_string Minute();
        static rg_string Second();
        static rg_string Milliseconds();
    };
```

### 6.9 Console Color

```cpp
    void SetColorConsole(WORD);
    void SetTrueColorConsole(COLOR3D<uint8_t>,
                             CONSOLE_COLOR = CONSOLE_COLOR::C_TEXT);

#ifdef __WIN32
    inline void SetColorTCMD(WORD col);   // Uses SetConsoleTextAttribute
#endif
```

### 6.10 String Utilities

```cpp
    bool isSubstringAt(const char&, const std::string&);
    bool isSubstringAt(const wchar_t&, const std::wstring&);
    bool isSubstringAt(const std::string&, const std::string&);
    bool isSubstringAt(const std::string&, const std::wstring&);  // [not implemented]

    void Open(std::string path);    // Open file, URL, or launch program
    void Open(std::wstring path);

    std::string  tolowstr(std::string);         // Lowercase (Latin only)
    std::wstring tolowwstr(std::wstring);       // Lowercase wide [redo, exp]
```

### 6.11 Number Formatting

```cpp
    char*  itoa(int value, int base = 10, char* buffer = nullptr);
    std::string  itos(size_t value, size_t base = 10);
    std::wstring itows(long long int value, long long int base = 10);
    std::wstring itows(size_t value, size_t base = 10);
```

### 6.12 Directory Operations

```cpp
    bool isDirectory(std::string path);
    bool isDirectory(std::wstring path);
    bool CreateFolder(std::string path);
    bool CreateFolder(std::wstring path);
```

### 6.13 Debug Class

```cpp
    class Debug {
        struct DebugVars;
        static DebugVars _vars;
    public:
        Debug();
        Debug(rg_string path);
        ~Debug();

        static void init();
        static void init(rg_string path);
        static void open_log_after_error(bool);
        static void open_shell(bool);        // Same as above
        static rg_string log_path();
        static void update();
        static void stop() [[noreturn]];
        static void no_close();

        static void add(rg_string msg, Log::Types level = DEBUG,
                        bool print = true, rg_string file = "NULL", int line = -1);

        template<class S1, class S2>
        static void add(S1 msg, Log::Types level, bool print, S2 file, int line);

        static void addl(Log::Types level, rg_string msg = RG_L"empty",
                         bool print = true,
                         rg_string file = rg_to_string(RG_HERE_FILE_NAME),
                         int line = -1);

        template<class S1, class S2>
        static void addl(Log::Types level, S1 msg, bool print, S2 file, int line);
    };
```

### 6.14 GetLastErrorString

```cpp
    rg_string GetLastErrorString(DWORD error_code);
```

### 6.15 Template Allocation Functions

```cpp
    // s_new — allocation with initialization
    template<class T> T* s_new(size_t count);
    template<class T> T* s_new(size_t count, T&& value);
    template<class T> T* s_new(size_t count, const T& value);
    template<class T, class Gen>
    std::enable_if_t<std::is_invocable_r_v<T, Gen>, T*>
        s_new(size_t count, Gen&& gen);

    // s_fast_new — allocation without zeroing
    template<class T> T* s_fast_new(size_t count);
    template<class T> T* s_fast_new(size_t count, T&& value);
    template<class T> T* s_fast_new(size_t count, const T& value);
    template<class T, class Gen>
    std::enable_if_t<std::is_invocable_r_v<T, Gen>, T*>
        s_fast_new(size_t count, Gen&& gen);

    size_t s_get_typesize(void*);
```

### 6.16 s_print

```cpp
    char s_print(to_rrvalue(char*));
    char s_print(to_rrvalue(wchar_t*));
    char s_print(to_rrvalue(std::string*));
    char s_print(to_rrvalue(std::wstring*));
    char s_print(std::string*);
    char s_print(std::wstring*);

    template<class T>
    char s_print(T* in);   // Prints all elements comma-separated
```

### 6.17 s_fill / s_fill_func

```cpp
    template<class ForwardIt, class Generator>
    void s_fill_func(ForwardIt first, ForwardIt last, Generator g);

    template<class ForwardIt, class T>
    void s_fill(ForwardIt first, ForwardIt last, T value);

    template<class T, class Gen>
    void s_fill_func(T* arr, int size, Gen g);

    template<class T, class Gen>
    void s_fill(T* arr, int size, Gen value);
```

### 6.18 s_getraw

```cpp
    char* s_getraw(void* in);   // Get raw pointer including header
```

### 6.19 Template s_delete / s_fast_delete

```cpp
    template<class T> void s_delete(T*& in);         // Class types: call dtors; primitives: free
    template<class T> void s_fast_delete(T*& in);    // Same for class; fast for primitives
```

Both use SFINAE to distinguish class vs non-class types.

### 6.20 s_move

```cpp
    template<class T> decltype(auto) s_move(T& obj);  // (T&&)obj
```

### 6.21 s_resize

```cpp
    template<class T> void s_resize(T*& in, int new_size);
```

If `new_size <= 0`: calls `s_delete`. If `in == nullptr`: calls `s_new`. Otherwise creates new array, move-transfers elements, deletes old.

### 6.22 Raw_Pointer

```cpp
    struct Raw_Pointer {
        void* ptr = nullptr;
        size_t typesize = 0;
        size_t arrsize = 0;

        bool is_init() const;
        void* get() const;

        Raw_Pointer();
        Raw_Pointer(void* in);
        Raw_Pointer(const Raw_Pointer&) = default;
        Raw_Pointer& operator=(const Raw_Pointer&) = default;
        Raw_Pointer(Raw_Pointer&&) = default;
        Raw_Pointer& operator=(Raw_Pointer&&) = default;

        void init();
        void init(void* in);

        Raw_Pointer& operator=(void* in);
        void* operator->();
        void clear();
        operator void*() const;
        ~Raw_Pointer();
    };
```

### 6.23 Pointer<T>

```cpp
    template<class T>
    class Pointer {
        Raw_Pointer _ptr;
    public:
        bool is_init() const;
        T* get() const;

        Pointer();
        Pointer(const T& in);
        Pointer(Pointer&& in) noexcept;
        Pointer(const Pointer& in);
        Pointer(T* in);

        void init();
        void init(T& in);
        void init(const T& in);
        void init(T in);
        void init(T* in);

        Pointer& operator=(const T& in);
        Pointer& operator=(Pointer&& in) noexcept;
        Pointer& operator=(const Pointer& in);
        Pointer& operator=(T* in);

        T* operator->();
        void clear();
        operator T*() const;
    };
```

### 6.24 RawArray

```cpp
    class RawArray {
        template<class T> friend class Array;
        DATA_OUT* ptr = nullptr;
        void* get() const;   // (void*)(ptr + 1)
    public:
        RawArray() = default;
        RawArray(size_t size_bytes);
        RawArray(const RawArray&);
        RawArray& operator=(const RawArray&);

        void resize(size_t size_bytes);
        size_t size() const;
        void clear();
        ~RawArray();
    };
```

### 6.25 Array<T>

```cpp
    template<class T>
    class Array : protected RawArray {
    public:
        Array() = default;
        Array(Array&&) = default;
        Array(const Array& in);            // Deep copy
        Array(size_t count);
        Array(size_t count, const T& value);
        Array(T&& value);                  // Single element, move
        Array(const T& value);             // Single element, copy

        T& operator[](long i) const;       // Bounds check; negative wraps from end
        T* back() const;                   // Pointer to last element
        T* begin() const;                  // Iterator begin
        T* end() const;                    // Iterator end
        T* data();

        void resize(size_t count);
        void push_back(const T& in);
        size_t size() const;               // Returns ptr->size / sizeof(T)
        void clear();
        ~Array();
    };
```

**Note:** `push_back` uses `std::move` on a `const T&` — this results in a copy, not a move.

### 6.26 Matrix<T>

```cpp
    template<class T>
    class Matrix {
        struct MatrixVars;
        MatrixVars _vars;
    public:
        Matrix();
        Matrix(uint rows, uint cols);
        Matrix(uint rows, uint cols, T value);

        void init(Array<T>);
        void init(std::initializer_list<std::initializer_list<T>>);
        void init(uint rows, uint cols);
        void init(uint rows, uint cols, T* data);
        void init(uint rows, uint cols, T value);
        void init(Matrix<T>);

        void operator=(std::initializer_list<std::initializer_list<T>>);
        void operator=(Array<T>);
        void operator=(Matrix<T>);

        void resize(uint total);
        void resize(uint rows, uint cols);
        void resize(POINT2D<uint> dims);

        void fill(Matrix<T>);
        void fill(uint rows, uint cols, T* data);
        void fill(Array<T>);
        void fill(std::initializer_list<std::initializer_list<T>>);
        void fill(T value);
        void fill(uint rows, uint cols, T value);

        void randomBoolFill(double min, double max);
        void randomBoolAddFill(double min, double max);
        void randomAddFill(double min, double max);
        void random_fill(double density);
        void noise_fill(int intensity);
        void noise_dbool_fill(int intensity);
        void fill_range_random(T min, T max);

        void scale(uint factor);
        void smoothScale(int factor);

        Matrix<T>& transpose();
        void update_transpose();
        T& get_t(const uint& row, const uint& col) const;

        T* operator[](const uint& row) const;
        T& operator()(const uint& row, const uint& col) const;
        T& operator()(POINT2D<uint> pos) const;
        T& operator()(POINT2D<int> pos) const;
        T& operator[](POINT2D<uint> pos) const;
        T& operator[](POINT2D<int> pos) const;

        T& get(const uint& row, const uint& col) const;
        T& getyx(uint y, uint x) const;
        T& get(POINT2D<uint> pos) const;
        T& get(POINT2D<int> pos) const;

        void print() const;
        std::string print_d() const;
        rg_ostrem& print(rg_ostrem& out) const;

        operator T*();
        T* get() const;
        T* data() const;
        T* get_mat() const;
        operator Array<T>&() const;
        operator Array<T>() const;
        operator bool();
        operator uint() const;

        uint size(uint dim) const;
        POINT2D<uint> size() const;

        bool empty() const;

        void clear();
        ~Matrix();

        void operator*=(const T* data);
        void operator*=(std::initializer_list<std::initializer_list<T>>);
        void operator*=(const Matrix<T>&);

        template<class T2> Matrix<T> operator*(const T2& scalar) const;
        template<class T2> Matrix<T> operator%(Matrix<T2>&) const;
        Matrix<T> operator*(const Matrix<T>&);
        Matrix<T> operator*(const Array<T>&) const;

        void operator+=(const Matrix<T>&);
        void operator-=(const Matrix<T>&);
        Matrix<T> operator+(const Matrix<T>&);
        Matrix<T> operator-(const Matrix<T>&);

        template<class TT> void place(POINT2D<int> offset, Matrix<TT>& src);
    };

    template<class T, class T2>
    T SpecialMatMulti(Matrix<T>&, Matrix<T2>&, int, int);

    template<class T, class T2>
    bool CountMatMinus(Matrix<T>&, Matrix<T2>&, int, int);  // [todo] Remove
```

### 6.27 RG_Matrix3D<T>

```cpp
    template<class T>
    class RG_Matrix3D {
        struct Matrix3DVars;
        Matrix3DVars _vars;
    public:
        RG_Matrix3D();
        RG_Matrix3D(Array<T>);
        RG_Matrix3D(RG_Matrix3D<T>);
        RG_Matrix3D(std::initializer_list<std::initializer_list<T>>);
        RG_Matrix3D(uint x, uint y, uint z);
        RG_Matrix3D(uint x, uint y, uint z, T* data);
        RG_Matrix3D(uint x, uint y, uint z, T value);

        void init(Array<T>);
        void init(std::initializer_list<std::initializer_list<T>>);
        void init(uint x, uint y, uint z);
        void init(uint x, uint y, uint z, T* data);
        void init(uint x, uint y, uint z, T value);
        void init(RG_Matrix3D<T>);

        void operator=(std::initializer_list<std::initializer_list<T>>);
        void operator=(Array<T>);
        void operator=(RG_Matrix3D<T>);

        void resize(uint total);
        void resize(uint x, uint y, uint z);
        void resize(POINT3D<uint> dims);
        void resize(POINT3D<int> dims);

        void fill(RG_Matrix3D<T>);
        void fill(uint x, uint y, uint z, T* data);
        void fill(Array<T>);
        void fill(std::initializer_list<
                  std::initializer_list<std::initializer_list<T>>>);
        void fill(T value);
        void fill(uint x, uint y, uint z, T value);

        void randomBoolFill(double, double);
        void randomBoolAddFill(double, double);
        void randomAddFill(double, double);
        void random_fill(double);
        void noise_fill(int);
        void noise_dbool_fill(int);
        void fill_range_random(T min, T max);

        void scale(uint factor);

        T& get(const uint& x, const uint& y, const uint& z) const;
        T& getzyx(uint z, uint y, uint x) const;
        T& get(POINT3D<uint> pos) const;
        T& get(POINT3D<int> pos) const;

        void print() const;

        operator T*();
        T* get() const;
        T* get_mat() const;
        operator Array<T>&() const;
        operator Array<T>() const;
        operator bool();
        operator uint() const;

        uint size(uint dim) const;
        POINT3D<uint> size() const;

        bool empty() const;

        void clear();
        ~RG_Matrix3D();

        template<class T2> RG_Matrix3D<T> operator*(const T2&) const;
        template<class T2> RG_Matrix3D<T> operator%(RG_Matrix3D<T2>&) const;
        void operator+=(const RG_Matrix3D<T>&);
        void operator-=(const RG_Matrix3D<T>&);

        template<class TT> void place(POINT3D<int> offset, RG_Matrix3D<TT>& src);
    };
```

### 6.28 Random Number Generation

```cpp
    uint64_t wstring_to_seed(const std::wstring& str);

    class RG_CRand {
    public:
        RG_CRand();
        RG_CRand(uint64_t seed);
        void init(uint64_t seed);
        bool is_init();
        uint64_t rand();
    };

    int set_seed();
    uint64_t RG_Rand();
    uint64_t Rand();
    double RandRange(double min, double max);
```

### 6.29 RG_List

```cpp
    template<class T>
    class RG_List {
    public:
        operator Array<T>&();
        int size();
        RG_List(std::initializer_list<T>);
        T operator[](int i);
    };
```

### 6.30 RG_ENCODE

```cpp
    struct RG_ENCODE_TYPE;
    struct RG_ENCODE_VALUE;

    class RG_ENCODE {
    public:
        static bool is_init();
        static wchar_t get_size(std::string);
        static int get_id(std::string);
        static RG_ENCODE_VALUE get(std::string);
    };
```

### 6.31 File Operations

```cpp
#ifdef RG_WIN
    std::wstring utf8_to_utf16(const std::string& str);
    std::string  utf16_to_utf8(const std::wstring& wstr);
#endif

    std::string  AFileLoad(std::string path);
    std::wstring WFileLoad(std::string path);
    std::wstring WFileLoad(std::wstring path);

    template<class String>
    rg_string FileLoad(String path);
    // With RG_UTF:    returns WFileLoad(rg_to_stringa(path))
    // Without RG_UTF: returns AFileLoad(rg_to_stringa(path))

    bool RG_IsFile(std::string path);
    std::string GetTypePath(std::string path);
```

### 6.32 FileFinder (Windows Only)

```cpp
#ifdef RG_WINos
    class FileFinder {
        HANDLE hFindFile;
        WIN32_FIND_DATA findFileData;
        bool _init = false, _eof = false;
    public:
        bool eof();
        WIN32_FIND_DATA* init(const rg_string& path);
        WIN32_FIND_DATA* next();
        void close();
        ~FileFinder();
    };

    class FileFinderA {
        HANDLE hFindFile;
        WIN32_FIND_DATAA findFileData;
        bool _init = false, _eof = false;
    public:
        bool eof();
        WIN32_FIND_DATAA* init(const std::string& path);
        WIN32_FIND_DATAA* next();
        void close();
        ~FileFinderA();
    };

    class FileFinderW {
        HANDLE hFindFile;
        WIN32_FIND_DATAW findFileData;
        bool _init = false, _eof = false;
    public:
        bool eof();
        WIN32_FIND_DATAW* init(const std::wstring& path);
        WIN32_FIND_DATAW* next();
        void close();
        ~FileFinderW();
    };
#endif
```

### 6.33 Program Execution

```cpp
    int RG_CMD(std::string command, bool wait = true);

    struct ConfigRunProgram {
        std::string path = "err";
        bool assinhrone = true;     // Asynchronous mode
        bool InItFol = false;       // Run from its own folder
        bool otherCMD = false;      // Additional command mode
    };

    int RunProgram(ConfigRunProgram conf);   // Win and Linux versions
```

### 6.34 Main Folder Detection

```cpp
    std::string  RG_AGetMainFolder();
    std::wstring RG_WGetMainFolder();

#ifdef RG_UTF
    std::wstring RG_GetMainFolder();
#else
    std::string  RG_GetMainFolder();
#endif
```

### 6.35 Vector Types

**vec2:**

```cpp
    template<class T>
    struct vec2 {
        void operator=(vec2<T> in);
        T& operator[](int i);
        vec2 operator*(const vec2& in);
        vec2 operator*(const POINT2D<T>& in);
    };
```

**vec3:**

```cpp
    template<class T>
    struct vec3 {
        void operator=(vec3<T> in);
        void operator=(vec2<T> in);
        vec3<T>& operator=(std::initializer_list<T> list);
        vec3<T> operator*(const vec3<T>& in);
        vec3<T> operator*(const T& in);
        vec3<T> operator+(const vec3<T>& in);
        vec3<T> operator+(const T& in);
        vec3<T> operator-(const vec3<T>& in);
        vec3<T> operator-(const T& in);
        void operator+=(const vec3<T>& in);
        T& operator[](int i) const;
    };
```

**vec4:**

```cpp
    template<class T>
    struct vec4 {
        template<class T2> void operator=(Matrix<T2> in);
        template<class T2> void operator=(Array<T2> in);
        void operator=(vec4<T> in);
        void operator=(vec3<T> in);
        void operator=(vec2<T> in);
        T& operator[](int i) const;
        template<class T2> vec4<T> operator*(const Matrix<T2>& in);
    };
```

### 6.36 Version (Duplicate in kernel.h)

```cpp
    void RG_GetVersion(int& major, int& minor, int& patch, int& wip);
    void RG_GetVersion(int& major, int& minor, int& patch);
```

---

## 7. other_define.h

### TryCatch

```cpp
namespace Rinegine {
    int TryCatch(std::function<void()> func);
}
```

### TryCatch Macro Wrapper

```cpp
#define RG_CATCH_ERROR  return Rinegine::TryCatch([&]() {
#define RG_ERROR_LOG    });
```

Usage:
```cpp
RG_CATCH_ERROR
    // code that may throw
RG_ERROR_LOG
```

### MainArguments Alias

```cpp
#ifndef RinegineLib
namespace Rinegine {
#ifdef RG_UTF
    std::vector<std::wstring>& MainArguments = Kernel::WMainArguments;
#else
    std::vector<std::string>& MainArguments = Kernel::AMainArguments;
#endif
}
#endif
```

---

## 8. interPoint.h

Generates the platform-specific entry point when `RinegineLib` is **not** defined:

```cpp
#ifndef RinegineLib
int rg_main();   // Declare user entry point

#ifdef RG_UTF
int wmain(int argc, wchar_t* argv[]) {
    return Rinegine::Kernel::InterPoint(argc, argv, ::rg_main);
}
#else
int main(int argc, char* argv[]) {
    return Rinegine::Kernel::InterPoint(argc, argv, ::rg_main);
}
#endif
#endif
```

When `RinegineLib` **is** defined (during library compilation), no `main()`/`wmain()` is generated.
