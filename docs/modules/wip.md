# WIP Module

The WIP (Work In Progress) module contains experimental features not yet ready for the main Kernel module. This includes a custom memory allocator with thread-local pooling, a raw map structure, and printing utilities.

## Inclusion Chain

```
modules/include/WIP/set.h → include.h → WIP.h
modules/src/WIP/set.h → include.h → allocator/allocator.h
```

---

## 1. include.h (public)

```cpp
#pragma once
#include <limits>
```

---

## 2. WIP.h

### 2.1 RawMap

A low-level key-value store using `RawArray` for both keys and values.

```cpp
namespace Rinegine::WIP {
    class RawMap {
        template<class Key, class Value>
        friend class Map;

        Kernel::RawArray keys;
        Kernel::RawArray values;
        size_t count = 0;

    public:
        RawMap() = default;
        RawMap(size_t size);

        void init(size_t size);
        void resize(size_t size);
        ~RawMap() = default;
    };
}
```

The `Map<Key, Value>` template class (not yet implemented) will use this as its backend.

### 2.2 WIP::Lock — Memory Management Declarations

```cpp
namespace Rinegine::WIP::Lock {
    void*  s_new(const size_t& size, const size_t& typesize = 1);
    void*  s_fast_new(const size_t& size, const size_t& typesize = 1);
    uint   s_delete(const void* ptr);
    void   s_fast_delete(const void* ptr);
    bool   s_rawmemtest(const char* ptr);
    bool   s_memtest(const void* ptr);
    size_t s_get_size(const void* ptr);
    size_t s_get_typesize(const void* ptr);
    char*  s_getraw(const void* ptr);

    char s_print(std::wstring*);
    char s_print(std::string*);
    char s_print(to_rrvalue(std::wstring*));
    char s_print(to_rrvalue(std::string*));
    char s_print(to_rrvalue(wchar_t*));
    char s_print(to_rrvalue(char*));
}
```

### 2.3 Free s_new Function

```cpp
namespace Rinegine::WIP {
    void* s_new(size_t count, size_t type_size);

    template<class T>
    T* s_new(size_t count, T&& value);  // Delegates to Kernel::Lock::s_new
}
```

### 2.4 ThreadLocalPool

```cpp
namespace Rinegine::WIP {
    struct ThreadLocalPool {
        void* pool;
        size_t count;

        struct Node {
            Node* next = nullptr;
            bool init = false;
        };
    };
}
```

### 2.5 Allocator<T> — STL-Compatible Custom Allocator

```cpp
namespace Rinegine::WIP {
    template<typename T = void>
    class Allocator {
        static thread_local ThreadLocalPool TLPVar;

        struct _map {
            uintptr_t size;
            u_char magnum[3];  // 'R', 'G', SIZE_BYTE
            struct mem {
                mem* next = nullptr;
                bool init = false;
            } _mem;
        };

        inline static uintptr_t s_map_size = 0;
        inline static _map* _main_map = nullptr;

        void push(size_t count = 1);

    public:
        using value_type = T;

        Allocator() = default;

        template<class T2>
        constexpr Allocator(const Allocator<T2>&) noexcept {}

        T* allocate(std::size_t n);
        void deallocate(T* p, std::size_t) noexcept;
    };
}
```

#### allocate()

Checks for overflow against `std::numeric_limits<size_t>::max()`. Uses a thread-local pool, falls back to `Kernel::s_new`. Throws `std::bad_alloc` on overflow.

#### deallocate()

Calls `s_delete(p)`.

#### Usage with STL containers

```cpp
#include <Rinegine/WIP>

std::vector<int, Rinegine::WIP::Allocator<int>> vec;
vec.push_back(42);  // Allocated via RG memory system
```

---

## 3. include.h (src/internal)

Pulls in a comprehensive set of standard library and OS headers:

**C++ Standard:**
`<cmath>`, `<filesystem>`, `<format>`, `<fstream>`, `<iostream>`, `<malloc.h>`, `<mutex>`, `<string>`, `<thread>`, `<cstdlib>`, `<cxxabi.h>`, `<typeinfo>`, `<functional>`, `<atomic>`, `<type_traits>`, `<cerrno>`, `<cstdio>`, `<cstring>`

**Windows:**
`<windows.h>`, `<psapi.h>`, `<direct.h>`, `<fcntl.h>`, `<io.h>` (defines `getcwd` as `_getcwd`)

**Linux:**
`<chrono>`, `<ctime>`, `<errno.h>`, `<iconv.h>`, `<linux/limits.h>`, `<stdexcept>`, `<sys/stat.h>`, `<sys/mman.h>`, `<unistd.h>`

Also defines: `#define RG_HERE_FILE_NAME "kernel/include"`

---

## 4. allocator/allocator.h — Implementations

### 4.1 Static Globals

```cpp
namespace Rinegine {
    static bool notseeitmsgmore = false;

    namespace Lock {
        inline static std::atomic_ullong MemUsed = 0;  // Total allocated bytes
        static int Magic_Num = 8 + sizeof(size_t);      // Header overhead
    }
}
```

### 4.2 s_new (mmap-based)

```cpp
void* WIP::Lock::s_new(const size_t& size, const size_t& typesize);
```

- Uses `mmap` with `PROT_READ | PROT_WRITE`, `MAP_PRIVATE | MAP_ANONYMOUS`
- Page-aligned: `rsize = ((size * typesize + Magic_Num) + page_size - 1) / page_size * page_size`
- Retries up to 30 times on failure
- Memory layout:
  ```
  [0..7]     typesize (size_t)
  [8..15]    size (size_t)
  [16]       'R'
  [17]       'G'
  [Magic_Num..]  user data (returned pointer)
  ```
- Updates `MemUsed` atomic counter
- Checks `RG_MEM_LIMIT` if defined (triggers critical log if exceeded)
- Linux-only (has a TODO note for Windows support)
- Logs a one-time warning: "At the moment s_new is not ready and it is better to use standard alternatives"

### 4.3 s_rawmemtest

```cpp
bool WIP::Lock::s_rawmemtest(const char* ptr);
```

Checks if `ptr[0] == 'R' && ptr[1] == 'G'`.

### 4.4 s_memtest

```cpp
bool WIP::Lock::s_memtest(const void* ptr);
```

Returns `false` if null. Subtracts `Magic_Num` from the pointer, checks for "RG" magic.

### 4.5 s_get_size

```cpp
size_t WIP::Lock::s_get_size(const void* ptr);
```

Triggers critical log if validation fails. Returns `(((size_t*)(ptr)) - 1)[0]` — reads the `size_t` slot immediately before the user pointer.

### 4.6 s_print Overloads

```cpp
char s_print(to_rrvalue(char*));           // Print each char
char s_print(to_rrvalue(wchar_t*));        // Print each wchar_t via std::wcout
char s_print(to_rrvalue(std::string*));    // Print quoted strings
char s_print(to_rrvalue(std::wstring*));   // Print via rg_to_string
char s_print(std::string*);                // Same as rvalue version
char s_print(std::wstring*);               // Same as rvalue version
```

### 4.7 s_getraw

```cpp
char* WIP::Lock::s_getraw(const void* ptr);
```

Returns the raw start of the allocation (including header): `(char*)((size_t*)(ptr)-1) - (2 + sizeof(size_t))`.

### 4.8 s_move

```cpp
template<typename T>
decltype(auto) s_move(T& obj) { return (T&&)obj; }
```

### 4.9 s_delete

```cpp
uint WIP::Lock::s_delete(const void* ptr);
```

1. Validates with `s_memtest()` — returns `SD_NO_RG_TYPE` on failure
2. Returns `SD_PTR_IS_NULLPTR` if null
3. Calculates page-aligned size
4. Calls `munmap`
5. Decrements `MemUsed`
6. Returns `SD_NO_ERR` or `SD_DEALOC_ERROR`

### 4.10 s_fast_new (malloc-based)

```cpp
void* WIP::Lock::s_fast_new(const size_t& size, const size_t& typesize);
```

- Uses `malloc` instead of `mmap` (faster, not page-aligned)
- Memory layout:
  ```
  [0]       'R'
  [1]       'G'
  [2..9]    typesize (size_t)
  [10..17]  size (size_t)
  [18..]    user data (returned pointer)
  ```
- Falls back to `s_new` if malloc fails
- Updates `MemUsed`

### 4.11 s_fast_delete

```cpp
void WIP::Lock::s_fast_delete(const void* ptr);
```

1. Validates with `s_memtest()`
2. Reads size and typesize
3. Decrements `MemUsed`
4. Calls `free(s_getraw(ptr))`

### 4.12 s_get_typesize

```cpp
size_t WIP::Lock::s_get_typesize(const void* ptr);
```

Triggers critical log if validation fails. Returns `*((size_t*)((size_t*)(ptr)-1) - 1)` — reads the `size_t` slot two positions before the user pointer.

---

## Status

All features in this module are **experimental**. The allocator is functional but incomplete (Linux-only for `s_new`, with a warning). The map system has no `Map<Key,Value>` implementation. APIs may change without notice.
