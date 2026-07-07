#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "wip/allocator"


namespace Rinegine {
  typedef unsigned char BYTE;
  typedef unsigned char byte;
  namespace WIP {

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


      constexpr std::size_t CACHE_LINE_SIZE =
#if defined(__cpp_lib_hardware_interference_size) && __cpp_lib_hardware_interference_size >= 201603L
        std::hardware_destructive_interference_size;
#elif defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
        64;
#elif defined(__aarch64__)
        64;
#elif defined(__arm__)
        32;
#else
        64;
#endif
      // Assume, it makes sense, but I don't see it...
      static_assert((CACHE_LINE_SIZE& (CACHE_LINE_SIZE - 1)) == 0,
        "CACHE_LINE_SIZE must be a power of 2");

      constexpr std::size_t align_to_cache_line(std::size_t n) noexcept {
        return (n + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE - 1);
      }
      constexpr bool is_cache_aligned(std::size_t n) noexcept {
        return (n & (CACHE_LINE_SIZE - 1)) == 0;
      }
      template<typename T>
      constexpr T* align_ptr_to_cache_line(T* ptr) noexcept {
        return reinterpret_cast<T*>(
          align_to_cache_line(reinterpret_cast<std::size_t>(ptr))
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

    // struct MEM_DATA {
    //   void* data;
    // };
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
    // struct MEM_CELL_HEAD {
    //   uint32_t magic;
    //   uint32_t flags;
    //   size_t size;
    //   uint32_t pool_id;
    //   uint32_t id;
    // }
    // struct MEM_POOL_HEAD {
    //   uint32_t magic;
    //   uint32_t flags;
    //   size_t size;
    //   uint32_t pool_id;
    //   uint32_t id;
    // }
    //[tail mem structure]
    // struct MEM_TAIL {//[done i think]
    //   size_t magic1;
    //   size_t magic2;
    // };
    //[todo cell mem structure]
    struct MEM_CELL {//[done or maybe it useless code idk]
      inline MEM_HEAD* get_head() {
        return ((MEM_HEAD*)this) - 1;
      }
      constexpr MEM_HEAD* get_head() const {
        return ((MEM_HEAD*)(this)) - 1;
      }
      // inline MEM_TAIL* get_tail() {
      //   return (MEM_TAIL*)(((char*)this) + (((MEM_HEAD*)this)->size - sizeof(MEM_TAIL)));
      // }
    };
    // constexpr size_t MEM_TAIL_SIZE = sizeof(MEM_TAIL);
    // constexpr size_t MEM_HEAD_SIZE = sizeof(MEM_HEAD);
    // constexpr size_t MEM_HEADnTAIL_SIZE = (sizeof(MEM_HEAD)+sizeof(MEM_TAIL));
    // constexpr size_t MEM_CELL_SIZE = (sizeof(MEM_CELL)); ////not need yet
    //[sys mem id for id all of mem head]
    static thread_local uint32_t SYS_MEM_ID = 0;
    static thread_local uint32_t SYS_POOL_ID = 0;
    //[const by sys page size]
    inline const size_t SYS_PAGE_SIZE = low_level::get_page_size();
    inline const size_t BASE_ALLOC_PAGE_COUNT = 1024 * 4096;
    size_t ALLOC_PAGE_COUNT = BASE_ALLOC_PAGE_COUNT;
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
        // RG_LOG_LOCK_DEBUG("ptr of pool: "+std::to_string((long long)ptr)+", ptr of tail: "+std::format("{x}",(long long)(MEM_TAIL*)((char*)ptr) + align - sizeof(MEM_TAIL))+", size of tail: "+std::to_string(sizeof(MEM_TAIL)));
        // RG_LOG_LOCK_DEBUG("ptr of pool: "+std::to_string((long long)ptr)+", ptr of tail: "+std::format("{x}",(long long)(MEM_TAIL*)((char*)ptr) + align - sizeof(MEM_TAIL))+", size of tail: "+std::to_string(sizeof(MEM_TAIL)));

        RG_LOG_LOCK_DEBUG(std::format("ptr of pool: {:#x}", (long long)ptr));
        // MEM_TAIL* tail = (MEM_TAIL*)(((char*)ptr) + (align - sizeof(MEM_TAIL)));
        // tail->magic1 = RG_MAG_NUM;
        // tail->magic2 = RG_MAG_NUM;
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
    //[mem pool for storage mem cells and other mem pools]
    // struct MEM_POOL {
    //   MEM_HEAD* pool = nullptr;
    //   void init() {
    //     if (pool)return;
    //     RG_LOG_LOCK_DEBUG("Create new pool");
    //     pool = SYS_GET_MEM(SYS_PAGE_SIZE);
    //     pool->pool_id = SYS_POOL_ID++;
    //   }
    //   void destruct() {
    //     RG_LOG_LOCK_DEBUG("Delete pool");
    //     SYS_DEL_MEM(pool);
    //   }
    // };
    inline bool MEM_CELL_TEST(const void* ptr) {
      if (ptr) [[likely]] {

        MEM_HEAD* head = (((MEM_HEAD*)ptr) - 1);
        // MEM_TAIL* tail = (MEM_TAIL*)(((char*)ptr) + head->size);
        if (head->magic == RG_MAG_NUM) {
          // if ((tail->magic1 == tail->magic2) && (tail->magic1 == RG_MAG_NUM)) {
          return 0;
          // }
          // else {
            //   RG_LOG_LOCK_ERROR(std::format("Memory id {:d} from pool id {:d} is corrupted!", head->id, head->pool_id));
            // }
          RG_LOG_LOCK_ERROR("MEM_CELL_TEST Error: ptr is not rg type");
        }
      }
      return 1;
    }

    inline bool MEM_RAW_CELL_TEST(const MEM_HEAD* head) {
      // MEM_TAIL* tail = (MEM_TAIL*)(((char*)(head + 1)) + head->size);
      // if (head->magic == RG_MAG_NUM) {
      if (head) [[likely]] {

        if (head->magic == RG_MAG_NUM) {
          return 0;
          // }
          // else {
          RG_LOG_LOCK_ERROR(std::format("Memory id {:d} from pool id {:d} is corrupted!", head->id, head->pool_id));
          // }
        }
        RG_LOG_LOCK_ERROR("MEM_RAW_CELL_TEST Error: ptr is not rg type");
      }
      RG_LOG_LOCK_ERROR("MEM_RAW_CELL_TEST Error: ptr is not ptr (nullptr)");
      return 1;
    }

    inline size_t MEM_CELL_SIZE(const void* ptr) {
      return (((MEM_HEAD*)ptr) - 1)->size;
    }
    /*[TODO] IDEAS
      Hot pools and cold pools
      Hot to no long life objects, cold for long life objects
      Free list for index free cell in full pool
      */
      //  #pragma GCC ivdep
      //  #pragma clang loop vectorize(enable) assume_safety
      // RESTRICT __restrict__ __restrict restrict before vars
      /*
      void add_fast(int* __restrict a, int* __restrict b, int* __restrict c) {
          for (int i = 0; i < 1024; ++i) {
            c[i] = a[i] + b[i];
          }
        }
      */
      // flag for debug -Rpass=loop-vectorize


      //[TODO]
    class Allocator {
      struct PoolCache {
        MEM_HEAD* near_free;
        size_t used_mem;
      };
      // size_t 
      struct cell_data : public MEM_HEAD {
        void* ptr;
      };
      inline static MEM_HEAD* pool = nullptr;
      //next init cell and now active pool
      inline static BYTE* next_init = nullptr;
      inline static BYTE* now_active_pool = nullptr;

      //next active pool
      inline static BYTE* next_active_pool = nullptr;

      //array of free and active cells
      inline static cell_data* list_free_cell = nullptr;
      inline static cell_data* list_active_cell = nullptr;

      //array of active pool cache
      inline static BYTE* now_active_pool_cache = nullptr;
      inline static BYTE* next_active_pool_cache = nullptr;



      // inline static MEM_HEAD* pool = nullptr;
      // inline static MEM_HEAD* next_init = nullptr;
      // inline static MEM_HEAD* now_pool = nullptr;
      // inline static PoolCache* now_pool_cache = nullptr;
      // inline static MEM_HEAD* next_pool = nullptr;
      // inline static PoolCache* next_pool_cache = nullptr;
      // inline static thread_local uint32_t pool_size[510]; [TODO] in plans

      void* to_index = nullptr;
      // std::thread indexer = []()({
      //   bool indexer_work = 1;
      //   const MEM_HEAD & *to_index_this = to_index;
      //   while (indexer_work) {
      //     while (to_index_this == nullptr) {
      //       /*[TODO]*/ return;
      //       sleep(20);
      //     }
      //   }
      //   });

      void switch_buffer() {//[TODO]
        if (!to_index) {
          to_index = now_active_pool;
        }
        if (!next_active_pool) {
          RG_LOG_CRITICAL("switch_buffer error: next pool isn't ready");
        }
        now_active_pool = next_active_pool;
        now_active_pool_cache = next_active_pool_cache;
        next_active_init = (MEM_HEAD*)(now_active_pool_cache + 1);
        next_active_pool = nullptr;
      }
    public:
      //[constructor]
      Allocator() {
        RG_LOG_LOCK_DEBUG("Create new Allocator");
        //   in->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED)
        // }
          //[constructor]
        if (pool)return;
        RG_LOG_LOCK_DEBUG("Create new pool");
        pool = SYS_GET_MEM(SYS_PAGE_SIZE);
        pool->pool_id = SYS_POOL_ID++;
        MEM_HEAD** pool_array = (MEM_HEAD**)(pool + 1);
        Rinegine::Kernel::Flags::set(pool->flags, MEM_FLAG::LOCKED);
        // now_pool = (pool = );
        /*======================*/
        //[if pool isn't init, should it init -> then mem get page from size]
        pool_array[0] = SYS_GET_MEM(SYS_PAGE_SIZE * ALLOC_PAGE_COUNT * (1));
        pool_array[0]->pool_id = SYS_POOL_ID++;
        //[new pool it temp for return from this func. Should returned a point to some cell from pool]
        now_pool = pool_array[0];
        now_pool_cache = (PoolCache*)(now_pool + 1);
        //[HEAD of cell]
        // PoolCache* cache = 
        next_init = (MEM_HEAD*)(now_pool_cache + 1);
        now_pool_cache->used_mem = sizeof(MEM_HEAD) + sizeof(PoolCache);
        RG_LOG_LOCK_DEBUG(std::string("Check correct sys allocation: size = ") + std::to_string(now_pool->size) + "; mag is " + ((now_pool->magic == RG_MAG_NUM) ? "correct" : "incorrect"));
        //[fill mem vars]
        // head_out->size = bytes;
        // head_out->magic = RG_MAG_NUM;
        // head_out->flags = static_cast<uint32_t>(MEM_FLAG::INIT);
        // // head_out->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED);
        // head_out->id = SYS_MEM_ID++;
        // head_out->pool_id = (uint32_t)i;

        // MEM_TAIL* tail = (MEM_TAIL*)(((char*)(head_out + 1)) + bytes);
        // tail->magic1 = RG_MAG_NUM;
        // tail->magic2 = RG_MAG_NUM;


        // cache->near_free = (MEM_HEAD*)(((char*)(head_out + 1)) + bytes + sizeof(MEM_TAIL));
        // MEM_HEAD* next_cell = (MEM_HEAD*)(tail + 1);
        // if (cache->near_free > next_cell)cache->near_free = next_cell;

        // cache->near_free = (MEM_HEAD*)(tail + 1);
        // rg_cout << (long long)((((char*)(head_out + 1)) + bytes + sizeof(MEM_TAIL)) - (long long)head_out) << std::endl;
        // rg_cout << (sizeof(MEM_HEAD) * 2 + sizeof(MEM_TAIL) * 2 + bytes);
        //[POOL_MEM_HEAD|POOL_CACHE|MEM_HEAD|data|TAIL|POOL_TAIL]
        // cache->used_mem = bytes + sizeof(MEM_TAIL) * 2 + sizeof(MEM_HEAD) * 2 + sizeof(PoolCache);
        // return head_out + 1;
        /*======================*/
        RG_LOG_LOCK_DEBUG(std::string("Pool is ") + std::string((pool->magic == RG_MAG_NUM) ? "init" : "doesn't init"));
        if (Rinegine::Kernel::Flags::has(pool->flags, MEM_FLAG::LOCKED)) {
          RG_LOG_LOCK_WARN(std::format("Pool {:d} mem id {:d} already locked", pool->pool_id, pool->id));
        }
        else {
          Rinegine::Kernel::Flags::set(pool->flags, MEM_FLAG::LOCKED);
          RG_LOG_LOCK_MEM(std::format("Pool {:d} mem id {:d} now is locked", pool->pool_id, pool->id));
        }
      }
      // void reallocate(void* ptr, size_t nsize) {
        // MEM_HEAD* head = (((MEM_HEAD*)ptr) - 1);

        // if (MEM_RAW_CELL_TEST(head)) {
        //   RG_LOG_LOCK_CRITICAL("Allocator error: reallocate get corrupted memory");
        // }
        // void* new_cell = allocate(nsize);
        // memcpy(new_cell, ptr, head->size);
        // MEM_HEAD* new_cell_head = (((MEM_HEAD*)new_cell) - 1);
        // new_cell_head->flags = head->flags;
        // raw_deallocate(head);
      // }
      inline void* get_pool_base(void* cell_ptr) {
        // ~(PAGE_SIZE - 1) create the mask 0x...FFFFF000
        return (void*)((uintptr_t)cell_ptr & ~(SYS_PAGE_SIZE - 1));
      }
      //[allocate]
      void* allocate(size_t bytes) {
        if (bytes == 0)return nullptr;
        size_t align_byte = low_level::align_to_cache_line(bytes);
        // RG_LOG_LOCK_ERROR(std::format("used is: {:d}, need is {:d} + {:d}; size is: {:d};; free: {:d}; next_init is: {:#x}", now_pool_cache->used_mem, align_byte, sizeof(MEM_HEAD), now_pool->size, now_pool->size - now_pool_cache->used_mem, (long long)next_init));
        if (align_byte + sizeof(MEM_HEAD) > now_pool->size - now_pool_cache->used_mem) [[unlikely]] {
          if (next_pool) {
            if (align_byte + sizeof(MEM_HEAD) <= next_pool->size - next_pool_cache->used_mem) {
              switch_buffer();
            }
            else {
              RG_LOG_LOCK_CRITICAL("Временная ошибка, позже заменю на смену буфера");

            }
          }
          else {
            RG_LOG_LOCK_CRITICAL("Временная ошибка, позже заменю на смену буфера");
          }
        }

        void* out = next_init;
        next_init = ((char*)next_init) + align_byte;
        return out;
        // void* out = (next_init + 1);
        // next_init->size = align_byte;
        // next_init->id = SYS_MEM_ID++;
        // next_init->pool_id = now_pool->pool_id;
        // next_init->magic = RG_MAG_NUM;
        // next_init->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED | MEM_FLAG::INIT);
        // next_init = ((MEM_HEAD*)(((char*)(next_init + 1)) + align_byte));
        // now_pool_cache->used_mem += align_byte + sizeof(MEM_HEAD);
      }
      void deallocate(BYTE* in) {
        if (!MEM_CELL_TEST(in)) [[likely]] {
          BYTE* head = in;
          Rinegine::Kernel::Flags::clear(head->flags, MEM_FLAG::IS_USED);
        }
        else {
          RG_LOG_LOCK_ERROR(std::format("deallocate: in ptr isn't RG type"));
        }
      }

      void clear() {
        if (pool == nullptr) {
          RG_LOG_LOCK_MEM("pool already free");
          return;
        }
        if (pool->magic == RG_MAG_NUM) {
          // size_t count = ((pool->size - sizeof(MEM_HEAD)) / sizeof(MEM_HEAD*) - sizeof(MEM_TAIL));
          size_t count = (pool->size - sizeof(MEM_HEAD) /*- sizeof(MEM_TAIL)*/) / sizeof(MEM_HEAD*);
          MEM_HEAD** pool_array = (MEM_HEAD**)(pool + 1);
          for (size_t i = 0; i < count;i++) {
            if (pool_array[i]) {//* delete pool doesn't pool class (if class will be changed it may do some corrupt and UB)
              SYS_DEL_MEM(pool_array[i]);
            }
          }
        }
        else {
          RG_LOG_LOCK_CRITICAL("How and for what??");
        }
        RG_LOG_LOCK_DEBUG("Some allocator has clearing successfullyl!");
      }
      ~Allocator() {
        clear();
      }
    };


    Allocator GlobalAllocator;

    //[Allocator tests]
    void Allocator_tests() {
      RG_LOG_LOCK_INFO("Start Allocator tests");
      RG_LOG_LOCK_INFO("Try init Allocator");

      Allocator& test = GlobalAllocator;
      RG_LOG_LOCK_INFO("Done");
      RG_LOG_LOCK_INFO("Try init 20 bytes");
      char* temp = (char*)test.allocate(20);
      RG_LOG_LOCK_INFO("Check size and mag num");
      RG_LOG_LOCK_INFO(std::format("Size: {:d} mag num is {:s}", (((MEM_HEAD*)temp) - 1)->size, (((((MEM_HEAD*)temp) - 1)->magic == RG_MAG_NUM) ? "correct" : "incorrect")));
      RG_LOG_LOCK_INFO("Try fill it");
      for (int i = 0;i < 20;i++) {
        temp[i] = (char)i;
      }
      RG_LOG_LOCK_INFO("Next");
      RG_LOG_LOCK_INFO("Next");
      RG_LOG_LOCK_INFO("Try init 40 bytes");
      char* temp2 = (char*)test.allocate(40);
      RG_LOG_LOCK_INFO("Check size and mag num");
      RG_LOG_LOCK_INFO(std::format("Size: {:d} mag num is {:s}", (((MEM_HEAD*)temp2) - 1)->size, (((((MEM_HEAD*)temp2) - 1)->magic == RG_MAG_NUM) ? "correct" : "incorrect")));
      RG_LOG_LOCK_INFO("Try fill it");
      for (int i = 0;i < 40;i++) {
        temp2[i] = (char)i;
      }
      // RG_LOG_LOCK_INFO
      RG_LOG_LOCK_INFO(std::string("Size: ") + std::to_string((((MEM_HEAD*)temp) - 1)->size) + ", mag num is " + (((((MEM_HEAD*)temp) - 1)->magic == RG_MAG_NUM) ? "correct" : "incorrect"));
      RG_LOG_LOCK_INFO("Next");
      RG_LOG_LOCK_INFO("Try deallocate 40 bytes");
      test.deallocate(temp2);
      RG_LOG_LOCK_INFO("Next");
      RG_LOG_LOCK_INFO("Try reinit 40 bytes");
      temp2 = (char*)test.allocate(40);
      RG_LOG_LOCK_INFO("Check size and mag num");
      RG_LOG_LOCK_INFO(std::format("Size: {:d} mag num is {:s}", (((MEM_HEAD*)temp2) - 1)->size, (((((MEM_HEAD*)temp2) - 1)->magic == RG_MAG_NUM) ? "correct" : "incorrect")));
      RG_LOG_LOCK_INFO("Try read and init it");
      for (int i = 0;i < 40;i++) {
        rg_cout << (int)temp2[i] << ",";
        temp2[i] = (char)i;
      }
      RG_LOG_LOCK_INFO("All test done");
    };
  }
}
/*================*/
//POOL
//[HEAD][POOLsARRAY][May tail idk]
//POOL from array of pools
//[DATA]
//POOL of cell head
//[HEAD][DATA][may tail idk]
//POOL of free ceil indentical like cell head pool
/*================*/