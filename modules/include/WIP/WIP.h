#pragma once

namespace Rinegine {
  // const size_t Lock::page_size = getpagesize();

  // namespace Lock {
  //   inline static std::atomic_ullong MemUsed = 0;
  //   static int Magisc_Num = 8 + (sizeof(size_t));//todo, i guese it shuld be removed
  // }
  class WIP {
  public:
    class Lock {
    public:
      static const size_t page_size;
      static void* s_new(const size_t&, const size_t & = 1); // [done,stub]
      static void* s_fast_new(const size_t& size, const size_t& typesize = 1); // [done,stub]
      static uint s_delete(const void*);                      // [done,stub]
      static void s_fast_delete(const void*);                 // [done,stub]
      // static void s_depage(void* addr, size_t count); 
      static bool s_rawmemtest(const char*);
      // template <class type> static bool s_memtest(type *);
      static bool s_memtest(const void*);

      static size_t s_get_size(const void*);
      static size_t s_get_typesize(const void*);

      static char* s_getraw(const void*);
      static char s_print(std::wstring*);
      static char s_print(std::string*);
      static char s_print(to_rrvalue(std::wstring*));
      static char s_print(to_rrvalue(std::string*));
      static char s_print(to_rrvalue(wchar_t*));
      static char s_print(to_rrvalue(char*));

    };
    //! ALLOCATOR EXPERIMENTAL/WIP
    // class Allocator {
    //   inline static uintptr_t g_page_mask = 0;
    //   struct _map {
    //     u_char magnum[3]; // R,G,SIZE
    //     struct mem {
    //       mem* next = nullptr;
    //       bool init = false;
    //     } _mem;
    //   };
    //   inline static _map* _main_map = nullptr;

    // public:
    //   static inline bool rg_map_test(void* in) {
    //     const unsigned char* p =
    //       (const unsigned char*)((uintptr_t)in & g_page_mask);
    //     return p[0] == 'R' && p[1] == 'G';
    //   }
    //   static void init();
    //   static void push(size_t in = 1);

    //   // static _map *s_map(size_t count = 1);
    //   // static void *s_new(size_t count, size_t type_size);

    //   static void print_map();
    //   //!
    //   static void s_free(void* in);
    //   // static void *get_free() {}

    //   Allocator() {}
    // };

    //!
    static void* s_new(size_t count, size_t type_size);
    template <class type>
    static type* s_new(size_t count, type&&) { //[todo]
      return (type*)Kernel::Lock::s_new(count * sizeof(type));
      // for(int i = 0; i < count; i++) new (type*) i;
    }
    struct ThreadLocalPool {
      void* pool;
      size_t count;
      struct Node {
        Node* next = nullptr;
        bool init = false;
      };
    };
    inline static thread_local ThreadLocalPool TLPVar;

    template <typename type = void>
    class Allocator {
      inline static uintptr_t s_map_size = 0;
      struct _map {
        uintptr_t size;
        u_char magnum[3]; // R,G,SIZE
        struct mem {
          mem* next = nullptr;
          bool init = false;
        } _mem;
      };
      inline static _map* _main_map = nullptr;
      void push(size_t in = 1);
    public:
      using value_type = type;
      Allocator() = default;
      template <class type2>
      constexpr Allocator(const Allocator<type2>&) noexcept {}

      type* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(type)) {
          RG_LOG_ERROR("std::bad_alloc, allocate size overflow");
          throw std::bad_alloc();
        }
        thread_local ThreadLocalPool pool;
        return static_cast<type*>(pool.pool = s_new(n, type()));
      }

      void deallocate(type* p, std::size_t) noexcept {
        s_delete(p);
      }

    };
    // #define Allocator Allocator<>
        // template <typename type, typename type2>
        // constexpr bool operator==(const Allocator<type>&, const Allocator<type2>&) noexcept {
        //   return true;
        // }

        // template <typename type, typename type2>
        // constexpr bool operator!=(const Allocator<type>&, const Allocator<type2>&) noexcept {
        //   return false;
        // }
        // template <typename T> struct Allocator {
        //   using value_type = T;

        //   Allocator() = default;
        //   template <class U> constexpr Allocator(const Allocator<U> &) noexcept {}

        //   T *allocate(std::size_t n) {
        //     if (n == 0)
        //       return nullptr;
        //     void *ptr = Kernel::s_fast_new<T>(static_cast<unsigned int>(n));
        //     if (!ptr)
        //       throw std::bad_alloc{};
        //     return static_cast<T *>(ptr);
        //   }

        //   void deallocate(T *ptr, std::size_t n) noexcept {
        //     if (ptr) {
        //       Kernel::Lock::s_fast_delete(ptr, sizeof(T));
        //     }
        //   }

        //   bool operator==(const Allocator &) const { return true; }
        //   bool operator!=(const Allocator &) const { return false; }
        // }; //! EXPERIMENTAL
  };
}