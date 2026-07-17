#pragma once

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/allocator"


namespace Rinegine {
  typedef unsigned char BYTE;
  typedef BYTE byte;
  namespace Kernel {

    namespace low_level { //[done?]
      //[get system page size]
      inline std::size_t get_page_size() noexcept {//[done]
#if defined(__linux__) || defined(__ANDROID__)
        long ps = sysconf(_SC_PAGESIZE);
        return (ps > 0) ? static_cast<std::size_t>(ps) : 4096;
#elif defined(_WIN32)
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        return static_cast<std::size_t>(si.dwPageSize);
#endif
      }
      //[align some num by some alignment]
      inline constexpr  std::size_t align_to_page(std::size_t size, std::size_t alignment) noexcept {//[done]
        return (size + alignment - 1) & ~(alignment - 1);
      }
      //[useless yet]
      inline constexpr  std::size_t clz64(std::size_t x) noexcept {//[done]
#if defined(__GNUC__) || defined(__clang__)
        return static_cast<std::size_t>(__builtin_clzll(x));
#elif defined(_MSC_VER)
        unsigned long idx;
        _BitScanReverse64(&idx, x);
        return 63 - idx;
#endif
      }


      extern const size_t CACHE_LINE_SIZE;


      constexpr std::size_t align_to_cache_line(std::size_t n) noexcept {
        return (n + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE - 1);
      }
      constexpr bool is_cache_aligned(std::size_t n) noexcept {
        return (n & (CACHE_LINE_SIZE - 1)) == 0;
      }

      constexpr std::size_t align_to(std::size_t n, size_t align) noexcept {
        return (n + align - 1) & ~(align - 1);
      }
      template<typename T>
      constexpr std::size_t align_to(std::size_t n) noexcept {
        return (n + alignof(T) - 1) & ~(alignof(T) - 1);
      }
      template<typename T>
      constexpr T* align_ptr_to_cache_line(T* ptr) noexcept {
        return reinterpret_cast<T*>(
          align_to_cache_line(reinterpret_cast<std::size_t>(ptr))
          );
      }

      template<typename T>
      constexpr T* align_ptr_to(T* ptr, size_t align) noexcept {
        return reinterpret_cast<T*>(
          align_to(reinterpret_cast<std::size_t>(ptr), align)
          );
      }
      template<class T2, typename T>
      constexpr T* align_ptr_to(T* ptr) noexcept {
        return reinterpret_cast<T*>(
          align_to<T2>(reinterpret_cast<std::size_t>(ptr))
          );
      }
    }

    //[mem flags]
    enum class MEM_FLAG :uint32_t {//[todo more]
      //[MAIN AND SYSTEM]
      INIT = 1 << 0,
      IS_USED = 1 << 1,
      LOCKED = 1 << 2,
      READ_ONLY = 1 << 3,
      // EXECUTABLE =,
      //[CUSTOM AND SUPPORT]
      IS_POOL = 1 << 16,
      IS_FREE_LIST = 1 << 17,
      NO_TAIL = 1 << 18,
      CUSTOM_POOL = 1 << 19,
      // IS_MAIN_POOL = 1 << 17,

    };
    //[operators for correct work flags]
    constexpr MEM_FLAG operator|(MEM_FLAG a, MEM_FLAG b) {//[done]
      return static_cast<MEM_FLAG>(
        static_cast<std::underlying_type_t<MEM_FLAG>>(a) |
        static_cast<std::underlying_type_t<MEM_FLAG>>(b)
        );
    }

    constexpr MEM_FLAG operator&(MEM_FLAG a, MEM_FLAG b) {//[done]
      return static_cast<MEM_FLAG>(
        static_cast<std::underlying_type_t<MEM_FLAG>>(a) &
        static_cast<std::underlying_type_t<MEM_FLAG>>(b)
        );
    }

    constexpr MEM_FLAG operator~(MEM_FLAG a) {//[done]
      return static_cast<MEM_FLAG>(
        ~static_cast<std::underlying_type_t<MEM_FLAG>>(a)
        );
    }

    // Для += и -= (set/clear):
    inline MEM_FLAG& operator|=(MEM_FLAG& a, MEM_FLAG b) {//[done]
      a = a | b;
      return a;
    }

    inline MEM_FLAG& operator&=(MEM_FLAG& a, MEM_FLAG b) {//[done]
      a = a & b;
      return a;
    }

    //[mag num for check mem]
    constexpr uint32_t RG_MAG_NUM = ('R' << 0) | ('G' << 8) | ('M' << 16) | ('G' << 24);//[done]
    // //[head mem structure]
    struct MEM_HEAD {//[done i think]
      uint32_t magic;
      uint32_t flags;
      size_t size;
      size_t pool_id;
      size_t id;
    };
    //[sys mem id for id all of mem head]
    static thread_local uint32_t SYS_MEM_ID = 0;
    //[const by sys page size]
    inline const size_t SYS_PAGE_SIZE = low_level::get_page_size();
    constexpr size_t MAX_ALLOC_PAGE_SIZE = 1024 * 1024 * 1024;
    extern const std::size_t CACHE_LINE_SIZE;
    inline constexpr size_t BASE_ALLOC_PAGE_COUNT = 4096;
    inline size_t ALLOC_PAGE_COUNT = BASE_ALLOC_PAGE_COUNT;
    // extern size_t ALLOC_PAGE_COUNT;
    //[get system mem, return system page with ready mem head]
    inline MEM_HEAD* SYS_GET_MEM(size_t bytes) {//[done it all]

      size_t align = low_level::align_to_page(bytes, SYS_PAGE_SIZE);
#ifdef RG_SYS_WINDOWS
      MEM_HEAD* ptr = (MEM_HEAD*)VirtualAlloc(nullptr, align, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#elif defined(RG_SYS_LINUX)
      MEM_HEAD* ptr = (MEM_HEAD*)mmap(nullptr, align, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#else
      MEM_HEAD* ptr = nullptr;
#endif
      if (ptr == nullptr) {
        RG_LOG_LOCK_CRITICAL("Allocator: fault alloc new page");
      }
      else {
        RG_LOG_LOCK_DEBUG(std::format("ptr of pool: {:#x}", (long long)ptr));
        RG_LOG_LOCK_MEM(std::string("ID ") + std::to_string(SYS_MEM_ID) + "; " + std::to_string(align) + " bytes of memory allocated (" + std::to_string(bytes) + " bytes were requested)");
        RG_LOG_LOCK_MEM(std::format("ID {:d}| {:d} bytes of memory allocated ({:d} bytes were requested)", SYS_MEM_ID, align, bytes));
        ptr->size = align;
        ptr->magic = RG_MAG_NUM;
        ptr->id = SYS_MEM_ID++;
        ptr->pool_id = 0;
        ptr->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED | MEM_FLAG::IS_POOL);//[todo | i think it should changing in time some time on time or on always (sor)]
      }
      return ptr;
    }

    inline BYTE* SYS_GET_RAW_MEM(size_t bytes) {//[done it all]
      if (bytes == 0) [[unlikely]] return nullptr;
      size_t align = low_level::align_to_page(bytes, SYS_PAGE_SIZE);
#ifdef RG_SYS_WINDOWS
      BYTE* ptr = (BYTE*)VirtualAlloc(nullptr, align, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#elif defined(RG_SYS_LINUX)
      BYTE* ptr = (BYTE*)mmap(nullptr, align, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#else
      BYTE* ptr = nullptr;
#endif
      if (ptr == nullptr || ptr == MAP_FAILED) {
        RG_LOG_LOCK_CRITICAL("Allocator: fault alloc new page");
      }
      RG_LOG_LOCK_MEM(std::format("ID {:d}| {:d} bytes of memory allocated ({:d} bytes were requested)", SYS_MEM_ID, align, bytes));
      return ptr;
    }

    //[deallocate sys mem pages with mem head]
    inline void SYS_DEL_MEM(MEM_HEAD*& in) {//[done]
      if (in != nullptr) {
        if (in->magic == RG_MAG_NUM) [[likely]] {
          RG_LOG_LOCK_MEM(std::string("ID: ") + std::to_string(in->id) + "; try deallocate");
          RG_LOG_LOCK_MEM(std::format("ID: {:d}| try deallocate", in->id));
          if (Rinegine::Kernel::Flags::has(in->flags, MEM_FLAG::IS_USED)) [[likely]] {
            if (!Rinegine::Kernel::Flags::has(in->flags, MEM_FLAG::LOCKED)) [[likely]] {
              RG_LOG_LOCK_MEM(std::format("ID: {:d}| {:d} bytes of memory deallocated", in->id, in->size));
              RG_LOG_LOCK_DEBUG(std::format("ptr of pool: {:#x}", (long long)in));
              in->flags = 0;
              in->magic = 0;
              in->size = 0;
#ifdef RG_SYS_WINDOWS
              VirtualFree(in, 0, MEM_RELEASE);
#elif defined(RG_SYS_LINUX)
              munmap(in, in->size);
#else
              RG_LOG_LOCK_ERROR("SYS_DEL_MEM: For what?");
#endif
              in = nullptr;
            }
            else {
              // RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " is locked");
              RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} is locked", ((long long)in)));
            }
          }
          else {
            // RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " isn't allocated");
            RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} isn't allocated", ((long long)in)));
          }
        }
        else {
          // RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " isn't allocated or isn't Rinegine type");
          RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} isn't allocated or isn't Rinegine type", ((long long)in)));
        }
      }
      else {
        // RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " is nullptr");
        RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} is nullptr", ((long long)in)));
      }
    }

    inline void SYS_DEL_RAW_MEM(BYTE*& in, size_t size
#ifndef RG_SYS_WINDOWS
      = 0
#endif
    ) noexcept {//[done]
      if (in) {
#ifdef RG_SYS_WINDOWS
        VirtualFree(in, 0, MEM_RELEASE);
#elif defined(RG_SYS_LINUX)
        munmap(in, size);
#else
        RG_LOG_LOCK_ERROR("SYS_DEL_MEM: For what?");
#endif
        RG_LOG_LOCK_MEM("Some raw mem is deallocated");
        in = nullptr;
      }
    }
    //[mem pool for storage mem cells and other mem pools]
    inline bool MEM_CELL_TEST(const void* ptr) {
      if (ptr) [[likely]] {

        MEM_HEAD* head = (((MEM_HEAD*)ptr) - 1);
        if (head->magic == RG_MAG_NUM) {
          return 0;
          RG_LOG_LOCK_ERROR("MEM_CELL_TEST Error: ptr is not rg type");
        }
      }
      return 1;
    }

    inline bool MEM_RAW_CELL_TEST(const MEM_HEAD* head) {
      if (head) [[likely]] {

        if (head->magic == RG_MAG_NUM) {
          return 0;
          RG_LOG_LOCK_ERROR(std::format("Memory id {:d} from pool id {:d} is corrupted!", head->id, head->pool_id));
        }
        RG_LOG_LOCK_ERROR("MEM_RAW_CELL_TEST Error: ptr is not rg type");
      }
      RG_LOG_LOCK_ERROR("MEM_RAW_CELL_TEST Error: ptr is not ptr (nullptr)");
      return 1;
    }

    inline size_t MEM_CELL_SIZE(const void* ptr) {
      return (((MEM_HEAD*)ptr) - 1)->size;
    }

    class Allocator {
      struct ChainNode;
      static BYTE* pool;
      static BYTE* next;
      static size_t size_of_allocate;
      static size_t allocator_count;
    public:
      using value_type = BYTE;
      template <typename U>
      struct rebind {
        using other = Allocator;
      };
      bool operator==(const Allocator&) const noexcept = default;
      Allocator();
      void init();
      BYTE* allocate(size_t in);
      void deallocate(void* ptr, size_t n = 0);
      ~Allocator();
    };

    inline Allocator GlobalAllocator; //[TODO]
  }
}
