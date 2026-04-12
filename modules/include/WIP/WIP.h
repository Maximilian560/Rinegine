#pragma once

namespace Rinegine {
  // const size_t Lock::page_size = getpagesize();

  // namespace Lock {
  //   inline std::atomic_ullong MemUsed = 0;
  //   int Magisc_Num = 8 + (sizeof(size_t));//todo, i guese it shuld be removed
  // }
  namespace WIP {
    //MAP
    class RawMap {
      template <class key, class value>
      friend class Map;
      Kernel::RawArray keys;
      Kernel::RawArray values;
      size_t count = 0;
    public:
      RawMap() = default;
      RawMap(size_t size) : count(0) { init(size); }
      void init(size_t size) {
        resize(size);
      }
      void resize(size_t size) {
        keys.resize(size);
        values.resize(size);
      }
      ~RawMap() = default;
    };

    namespace Lock {
      // const size_t page_size;
      void* s_new(const size_t&, const size_t & = 1); // [done,stub]
      void* s_fast_new(const size_t& size, const size_t& typesize = 1); // [done,stub]
      uint s_delete(const void*);                      // [done,stub]
      void s_fast_delete(const void*);                 // [done,stub]
      // void s_depage(void* addr, size_t count); 
      bool s_rawmemtest(const char*);
      // template <class type> bool s_memtest(type *);
      bool s_memtest(const void*);

      size_t s_get_size(const void*);
      size_t s_get_typesize(const void*);

      char* s_getraw(const void*);
      char s_print(std::wstring*);
      char s_print(std::string*);
      char s_print(to_rrvalue(std::wstring*));
      char s_print(to_rrvalue(std::string*));
      char s_print(to_rrvalue(wchar_t*));
      char s_print(to_rrvalue(char*));

    };
    //! ALLOCATOR EXPERIMENTAL/WIP
    // class Allocator {
    //   inline uintptr_t g_page_mask = 0;
    //   struct _map {
    //     u_char magnum[3]; // R,G,SIZE
    //     struct mem {
    //       mem* next = nullptr;
    //       bool init = false;
    //     } _mem;
    //   };
    //   inline _map* _main_map = nullptr;

    // public:
    //   inline bool rg_map_test(void* in) {
    //     const unsigned char* p =
    //       (const unsigned char*)((uintptr_t)in & g_page_mask);
    //     return p[0] == 'R' && p[1] == 'G';
    //   }
    //   void init();
    //   void push(size_t in = 1);

    //   // _map *s_map(size_t count = 1);
    //   // void *s_new(size_t count, size_t type_size);

    //   void print_map();
    //   //!
    //   void s_free(void* in);
    //   // void *get_free() {}

    //   Allocator() {}
    // };

    //!
    void* s_new(size_t count, size_t type_size);
    template <class type>
    type* s_new(size_t count, type&&) { //[todo]
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

    template <typename type = void>
    class Allocator {
      static thread_local ThreadLocalPool TLPVar;
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
        return (type*)(pool.pool = Kernel::s_new(n, type()));
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


    //***TOKENIZE MODULE***//
    // class Tokenizer {

    // };
  };
}