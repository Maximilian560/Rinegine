#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "wip/allocator"
/*
namespace Rinegine {
  static bool notseeitmsgmore = 0;

  namespace Lock {

    inline static std::atomic_ullong MemUsed = 0;
    // magic nums
    static int Magic_Num = 8 + (sizeof(size_t));
  };
  void* WIP::Lock::s_new(const size_t& size, const size_t& typesize) { // todo                     ||
    // only for linux yet, sorry||
    // unoptimazed yet
    if (!notseeitmsgmore) {
      //RG_LOG_LOCK_INFO("At the moment s_new is not ready and it is better to use "
        "standard alternatives");
      notseeitmsgmore = 1;
    }
    if (size == 0)
      return nullptr;

    int page_size = getpagesize();

    size_t rsize = ((size * typesize + Rinegine::Lock::Magic_Num) + page_size - 1) / page_size * page_size;

    void* raw_newmem = mmap(nullptr, rsize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (raw_newmem == MAP_FAILED) {
      for (int i = 1; i <= 30 && !raw_newmem; i++) {
        raw_newmem = mmap(nullptr, rsize, PROT_READ | PROT_WRITE,
          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (raw_newmem == MAP_FAILED)
          //RG_LOG_LOCK_LOCK_ERROR("Memory allocate error, retry: " + std::to_string(i) + "/" + std::to_string(30));
      }
      if (raw_newmem == MAP_FAILED)
        //RG_LOG_LOCK_LOCK_CRITICAL("MEMORY ALLOCATE ERROR");
    }
    if (sizeof(size_t) != 8) { // todo replace to engine init
      RG_LOG_LOCK_CRITICAL("Your architecture unsupported yet");
    }

    size_t& ptrtypesize = *((size_t*)raw_newmem);
    char* ptrmnum = (char*)raw_newmem;
    size_t& ptr_arrsize = *(size_t*)(((char*)raw_newmem) + 8);

    ptrtypesize = typesize;
    ptrmnum[0] = 'R';
    ptrmnum[1] = 'G';
    ptr_arrsize = size;
    void* out = (void*)(((char*)raw_newmem) + Rinegine::Lock::Magic_Num);
    Rinegine::Lock::MemUsed += rsize;

    //RG_LOG_LOCK_LOCK_MEM("Mem aloc: " + std::to_string(rsize) +
      "b, type: " + std::to_string(typesize));
#ifdef RG_MEM_LIMIT
    if (Rinegine::Lock::MemUsed >= RG_MEM_LIMIT)
      //RG_LOG_LOCK_LOCK_CRITICAL("Memory limit exceeded");
#endif
    return out;
  }

  bool WIP::Lock::s_rawmemtest(const char* in) {
    if (in[0] == 'R' && in[1] == 'G')
      return true;
    return false;
  }

  bool WIP::Lock::s_memtest(const void* in) {
    if (in == nullptr)
      return false;
    char* rawmem = (((char*)(in)) - Rinegine::Lock::Magic_Num);
    if (rawmem[1] == 'G' && rawmem[0] == 'R')
      return true;

    return false;
  }

  size_t WIP::Lock::s_get_size(const void* in) {
    if (!s_memtest(in))
      //RG_LOG_LOCK_LOCK_CRITICAL("s_get_size: array is not rg type");
    return (((size_t*)(in)) - 1)[0];
  }

  char WIP::Lock::s_print(to_rrvalue(char*) in) {
    int temp_size = (int)s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << in[i];
      if (i == temp_size - 1)
        rg_cout << std::endl;
    }
    return '\0';
  }

  char WIP::Lock::s_print(to_rrvalue(wchar_t*) in) {
    int temp_size = (int)s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      std::wcout << in[i]; // TODO
      if (i == temp_size - 1)
        rg_cout << std::endl;
    }
    return '\0';
  }

  char WIP::Lock::s_print(to_rrvalue(std::string*) in) {
    int temp_size = (int)s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << "\"";
      rg_cout << rg_to_string(in[i]);
      rg_cout << "\"\n";
    }
    return '\0';
  }
  char WIP::Lock::s_print(to_rrvalue(std::wstring*) in) {
    int temp_size = (int)s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << rg_to_string(in[i]) << ", ";
    }
    return '\0';
  }

  char WIP::Lock::s_print(std::string* in) {
    int temp_size = (int)s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << "\"";
      rg_cout << rg_to_string(in[i]);
      rg_cout << "\"\n";
    }
    return '\0';
  }
  char WIP::Lock::s_print(std::wstring* in) {
    int temp_size = (int)s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << rg_to_string(in[i]) << ", ";
    }
    return '\0';
  }

  char* WIP::Lock::s_getraw(const void* in) {
    return (char*)((size_t*)(in)-1) - (2 + sizeof(size_t));
  }

  template <typename T> decltype(auto) s_move(T& obj) { return (T&&)obj; }

  uint WIP::Lock::s_delete(const void* in) {
    if (!Rinegine::WIP::Lock::s_memtest(in))
      return SD_NO_RG_TYPE;
    if (in == nullptr)
      return SD_PTR_IS_NULLPTR;
    int page_size = getpagesize();

    const size_t size = Rinegine::WIP::Lock::s_get_size(in);
    const size_t typesize = Rinegine::WIP::Lock::s_get_typesize(in);

    size_t rsize =
      ((size * typesize + Rinegine::Lock::Magic_Num) + page_size - 1) /
      page_size * page_size;

    // free(Rinegine::WIP::Lock::s_getraw(in));
    if (munmap((void*)((char*)in - Rinegine::Lock::Magic_Num), rsize) == -1) {
      //RG_LOG_LOCK_ERROR("s_delete deallocate error");
      return SD_DEALOC_ERROR;
    }
    //RG_LOG_LOCK_LOCK_MEM("Mem clean: " + std::to_string(rsize) +
      "b, type: " + std::to_string(typesize));
    Rinegine::Lock::MemUsed -= rsize;
    return SD_NO_ERR;
    //
  }
  void* WIP::Lock::s_fast_new(const size_t& size, const size_t& typesize) {
    char* newmem = (char*)malloc(size * typesize + sizeof(size_t) + sizeof(size_t) + sizeof(char) * 2);
    if (!newmem) {
      //RG_LOG_LOCK_LOCK_ERROR("Fast alloc failed, try standard alloc");
      void* out = WIP::Lock::s_new(size, typesize);
      return out;
    }

    newmem[0] = 'R';
    newmem[1] = 'G';
    size_t* stypesize = (size_t*)(newmem + 2);
    stypesize[0] = (size_t)typesize;
    size_t* ssize = (size_t*)(stypesize + 1);
    ssize[0] = size;
    void* out = (void*)(ssize + 1);
    Rinegine::Lock::MemUsed += size * typesize + sizeof(size_t) +
      sizeof(size_t) + sizeof(char) * 2;
    return out;
  }

  void WIP::Lock::s_fast_delete(const void* in) {
    if (!Rinegine::WIP::Lock::s_memtest(in))
      return;
    const size_t& size = Rinegine::WIP::Lock::s_get_size(in);
    const size_t& typesize = Rinegine::WIP::Lock::s_get_typesize(in);
    Rinegine::Lock::MemUsed -=
      size * typesize + sizeof(size_t) + sizeof(char) * 2;
    free(Rinegine::WIP::Lock::s_getraw(in));
    in = nullptr;
  }

  size_t WIP::Lock::s_get_typesize(const void* in) {
    if (!s_memtest(in)) {
      //RG_LOG_LOCK_LOCK_CRITICAL("s_get_typesize: array is not RG type");
    }
    return *((size_t*)((size_t*)(in)-1) - 1);
  }
}
*/




//[===============================================]//
#pragma once

// === CODE === //
//low level func namespace
namespace Rinegine {
  namespace WIP {

    namespace low_level {//[done?]
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
    //[head mem structure]
    struct MEM_HEAD {//[done i think]
      uint32_t magic;
      uint32_t flags;
      size_t size;
      uint32_t pool_id;
      uint32_t id;
    };
    //[tail mem structure]
    struct MEM_TAIL {//[done i think]
      uint32_t magic1;
      uint32_t magic2;
    };
    //[todo cell mem structure]
    struct MEM_CELL {//[done or maybe it useless code idk]
      inline MEM_HEAD* get_head() {
        return ((MEM_HEAD*)this) - 1;
      }
      constexpr MEM_HEAD* get_head() const {
        return ((MEM_HEAD*)(this)) - 1;
      }
      inline MEM_TAIL* get_tail() {
        return (MEM_TAIL*)(((char*)this) + (((MEM_HEAD*)this)->size - sizeof(MEM_TAIL)));
      }
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
    inline const size_t BASE_ALLOC_PAGE_COUNT = 512;
    size_t ALLOC_PAGE_COUNT = BASE_ALLOC_PAGE_COUNT;
    //[get system mem, return system page with ready mem head]
    inline MEM_HEAD* SYS_GET_MEM(size_t bytes) {//[done it all]
      size_t align = low_level::align_to_page(bytes, SYS_PAGE_SIZE);
#ifdef RG_WIN
      MEM_HEAD* ptr = (MEM_HEAD*)VirtualAlloc(nullptr, align, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#elif defined(RG_LINUX)
      MEM_HEAD* ptr = (MEM_HEAD*)mmap(nullptr, align, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#else
      MEM_HEAD* ptr = nullptr;
#endif
      if (ptr == nullptr) {
        RG_LOG_LOCK_CRITICAL("Allocator: fault alloc new page");
      }
      else {
        // //RG_LOG_LOCK_DEBUG("ptr of pool: "+std::to_string((long long)ptr)+", ptr of tail: "+std::format("{x}",(long long)(MEM_TAIL*)((char*)ptr) + align - sizeof(MEM_TAIL))+", size of tail: "+std::to_string(sizeof(MEM_TAIL)));
        //RG_LOG_LOCK_DEBUG(std::format("ptr of pool: {:#x}, ptr of tail: {:#x}, size of tail: {:d}", (long long)ptr, (long long)(MEM_TAIL*)(((char*)ptr) + align - sizeof(MEM_TAIL)), sizeof(MEM_TAIL)));
        MEM_TAIL* tail = (MEM_TAIL*)(((char*)ptr) + (align - sizeof(MEM_TAIL)));
        tail->magic1 = RG_MAG_NUM;
        tail->magic2 = RG_MAG_NUM;
        // //RG_LOG_LOCK_MEM(std::string("ID ") + std::to_string(SYS_MEM_ID) + "; " + std::to_string(align) + " bytes of memory allocated (" + std::to_string(bytes) + " bytes were requested)");
        //RG_LOG_LOCK_MEM(std::format("ID {:d}| {:d} bytes of memory allocated ({:d} bytes were requested)", SYS_MEM_ID, align, bytes));
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
          // //RG_LOG_LOCK_MEM(std::string("ID: ") + std::to_string(in->id) + "; try deallocate");
          //RG_LOG_LOCK_MEM(std::format("ID: {:d}| try deallocate", in->id));
          if (Rinegine::Kernel::Flags::has(in->flags, MEM_FLAG::IS_USED)) [[likely]] {
            if (!Rinegine::Kernel::Flags::has(in->flags, MEM_FLAG::LOCKED)) [[likely]] {
              MEM_TAIL* tail = (MEM_TAIL*)(((char*)in) + ((in->size) - sizeof(MEM_TAIL)));
              if (tail->magic1 != tail->magic2 || tail->magic2 != RG_MAG_NUM) [[unlikely]] {
                RG_LOG_LOCK_CRITICAL("The memory tail for identifier " + std::to_string(in->id) + " is corrupted, but the cell will still be cleared and the program will continue to work. In case of any crash, it is necessary to track the movement of memory under identifier " + std::to_string(in->id) + ".");
              }
              // //RG_LOG_LOCK_MEM(std::to_string(in->size) + " bytes of memory deallocated");
              //RG_LOG_LOCK_MEM(std::format("ID: {:d}| {:d} bytes of memory deallocated", in->id, in->size));
              //RG_LOG_LOCK_DEBUG(std::format("ptr of pool: {:#x}, ptr of tail: {:#x}, size of tail: {:d}", (long long)in, (long long)(MEM_TAIL*)(((char*)in) + in->size - sizeof(MEM_TAIL)), sizeof(MEM_TAIL)));
              in->flags = 0;
              in->magic = 0;
              in->size = 0;
#ifdef RG_WIN
              VirtualFree(in, 0, MEM_RELEASE);
#elif defined(RG_LINUX)
              // //RG_LOG_LOCK_WARN("Mem has not been cleared for debug!");
              munmap(in, in->size);
#else
              //RG_LOG_LOCK_ERROR("SYS_DEL_MEM: For what?");
#endif
              in = nullptr;
            }
            else {
              // //RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " is locked");
              //RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} is locked", ((long long)in)));
            }
          }
          else {
            // //RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " isn't allocated");
            //RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} isn't allocated", ((long long)in)));
          }
        }
        else {
          // //RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " isn't allocated or isn't Rinegine type");
          //RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} isn't allocated or isn't Rinegine type", ((long long)in)));
        }
      }
      else {
        // //RG_LOG_LOCK_ERROR("SYS_DEL_MEM: mem " + std::to_string((long long)in) + " is nullptr");
        //RG_LOG_LOCK_ERROR(std::format("SYS_DEL_MEM: mem {:#x} is nullptr", ((long long)in)));
      }
    }
    //[mem pool for storage mem cells and other mem pools]
    struct MEM_POOL {
      MEM_HEAD* pool = nullptr;
      void init() {
        if (pool)return;
        //RG_LOG_LOCK_DEBUG("Create new pool");
        pool = SYS_GET_MEM(SYS_PAGE_SIZE);
        pool->pool_id = SYS_POOL_ID++;
      }
      void destruct() {
        //RG_LOG_LOCK_DEBUG("Delete pool");
        SYS_DEL_MEM(pool);
      }
    };

    /* [TODO] in plans
    struct MEM_POOL_SIZE{
      enum struct FLAGS{

      };
      uint32_t size;
      uint32_t flags;

    };*/
    inline bool MEM_CELL_TEST(void* ptr) {
      MEM_HEAD* head = (((MEM_HEAD*)ptr) - 1);
      MEM_TAIL* tail = (MEM_TAIL*)(((char*)ptr) + head->size);
      if (head->magic == RG_MAG_NUM) {
        if ((tail->magic1 == tail->magic2) && (tail->magic1 == RG_MAG_NUM)) {
          return 0;
        }
        else {
          //RG_LOG_LOCK_ERROR(std::format("Memory id {:d} from pool id {:d} is corrupted!", head->id, head->pool_id));
        }
        //RG_LOG_LOCK_ERROR("MEM_CELL_TEST Error: ptr is not rg type");
      }
      return 1;
    }
    inline size_t MEM_CELL_SIZE(void* ptr) {
      return (((MEM_HEAD*)ptr) - 1)->size;
    }
    //[Allocator class, for allocate/deallocate mem cells]
    class Allocator {

      // MEM_HEA data;
      inline static thread_local MEM_POOL pool;
      // inline static thread_local uint32_t pool_size[510]; [TODO] in plans
      struct PoolCache {
        MEM_HEAD* near_free;
        size_t used_mem;
        // size_t 
      };
      // void prepare_cell(MEM_HEAD* in, size_t size) {
      //   in->size = size;
      //   in->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED);
      //   in->id = SYS_MEM_ID++;
      //   in->magic = RG_MAG_NUM;
      // }
    public:
      //[constructor]
      Allocator() {
        //RG_LOG_LOCK_DEBUG("Create new Allocator");
        pool.init();
        //RG_LOG_LOCK_DEBUG(std::string("Pool is ") + std::string((pool.pool->magic == RG_MAG_NUM) ? "init" : "doesn't init"));
        if (Rinegine::Kernel::Flags::has(pool.pool->flags, MEM_FLAG::LOCKED)) {
          //RG_LOG_LOCK_WARN(std::format("Pool {:d} mem id {:d} already locked", pool.pool->pool_id, pool.pool->id));
        }
        else {
          Rinegine::Kernel::Flags::set(pool.pool->flags, MEM_FLAG::LOCKED);
          //RG_LOG_LOCK_MEM(std::format("Pool {:d} mem id {:d} now is locked", pool.pool->pool_id, pool.pool->id));
        }
      }
      void reallocate(void* ptr, size_t nsize) {
        if (MEM_CELL_TEST(ptr)) {
          RG_LOG_LOCK_CRITICAL("Allocator error: reallocate get corrupted memory");
        }
        void* new_cell = allocate(nsize);
        memcpy(new_cell, ptr, MEM_CELL_SIZE(ptr));
        deallocate(ptr);
      }
      inline void* get_pool_base(void* cell_ptr) {
        // ~(PAGE_SIZE - 1) создаёт маску 0x...FFFFF000
        return (void*)((uintptr_t)cell_ptr & ~(SYS_PAGE_SIZE - 1));
      }
      //[allocate]
      void* allocate(size_t bytes) {
        //[get pool array for easer get pools from main pool]
        //[HEAD|*pool_array*|TAIL]
        // MEM_HEAD* pool_array_new = (pool.pool+1);
        MEM_HEAD** pool_array = (MEM_HEAD**)(pool.pool + 1);
        //RG_LOG_LOCK_DEBUG(std::format("pool_array: {:#x}", (long long)(pool_array)));
        //[free or not (pool)]
        bool valid_pool = false;
        //[out var, may be unuseles]
        // void* out = nullptr;
        // while (!valid_pool) {
         //[calc count pool in main pool (pool of pools)]
        // size_t count_pools_from_main_pool = ((pool.pool->size - sizeof(MEM_HEAD)) / sizeof(MEM_HEAD*) - sizeof(MEM_TAIL));
        size_t count_pools_from_main_pool = (pool.pool->size - sizeof(MEM_HEAD) - sizeof(MEM_TAIL)) / sizeof(MEM_HEAD*);
        //RG_LOG_LOCK_DEBUG(std::string("run allocate try, pool array count is ") + std::to_string(count_pools_from_main_pool));
        //[check every pool in main pool]
        for (size_t i = 0; i < count_pools_from_main_pool && !valid_pool;i++) {
          //[now pool, tested pool]
          MEM_HEAD* now_pool = pool_array[i];
          //[if it is nullptr then this isn't init, should init]
          if (now_pool != nullptr) {
            //[if it magic number is correct, to next, else error]
            if (now_pool->magic == RG_MAG_NUM) [[likely]] {
              //[if pool has flag "is pool"]
              if (Rinegine::Kernel::Flags::has(now_pool->flags, MEM_FLAG::IS_POOL)) [[likely]] {
                //[if pool hasn't flag "read only" (very unlikely that it has have it)]
                if (!Rinegine::Kernel::Flags::has(now_pool->flags, MEM_FLAG::READ_ONLY)) [[likely]] {
                  //[get pool cache]
                  PoolCache* cache = (PoolCache*)(now_pool + 1);
                  //[if pool used mem more then count for alloc plus other structure slop]
                  //RG_LOG_LOCK_DEBUG(std::format("Pool id {:d}, mem id {:d}, size {:d}, used mem {:d}, try alloc {:d}, check of free {:d}", now_pool->pool_id, now_pool->id, now_pool->size, cache->used_mem, bytes, bytes + sizeof(PoolCache) + sizeof(MEM_HEAD) + sizeof(MEM_TAIL)));
                  //RG_LOG_LOCK_DEBUG(std::format("size of mem head {:d}, size of mem tail {:d}, size of pool cache {:d}", sizeof(MEM_HEAD), sizeof(MEM_TAIL), sizeof(PoolCache)));
                  //[if free size not enough]

                  /*
                  if (cache->near_free->size < (bytes + sizeof(MEM_HEAD) + sizeof(MEM_TAIL))) {
                    //RG_LOG_LOCK_DEBUG("Tested cell debug: cache near free: {:#x}, size {:d}, m_h {:d}, m_t {:d}, next mem {:#x}", cache->near_free, cache->near_free->size, sizeof(MEM_HEAD), sizeof(MEM_TAIL), (((char*)cache->near_free) + cache->near_free->size + sizeof(MEM_HEAD) + sizeof(MEM_TAIL)));
                    head_out = (MEM_HEAD*)(((char*)cache->near_free) + cache->near_free->size + sizeof(MEM_HEAD) + sizeof(MEM_TAIL));
                    while (head_out->size < (bytes + sizeof(MEM_HEAD) + sizeof(MEM_TAIL))) {
                      if (Rinegine::Kernel::Flags::has(cache->near_free->flags, MEM_FLAG::INIT))
                        //RG_LOG_LOCK_DEBUG("Tested cell debug: now free: {:#x}, size {:d}, m_h {:d}, m_t {:d}, next mem {:#x}", head_out, head_out->size, sizeof(MEM_HEAD), sizeof(MEM_TAIL), (((char*)head_out) + head_out->size + sizeof(MEM_HEAD) + sizeof(MEM_TAIL)));
                      head_out = (MEM_HEAD*)(((char*)head_out) + head_out->size + sizeof(MEM_HEAD) + sizeof(MEM_TAIL));

                    }
                  }*/
                  if ((now_pool->size - cache->used_mem) < (bytes + sizeof(PoolCache) + sizeof(MEM_HEAD) * 2 + sizeof(MEM_TAIL) * 2)) {//todo there may be error (size mem_head * 2 and mem_tail * 2)
                    continue;
                  }
                  else {
                    MEM_HEAD* head_out = cache->near_free;
                    if (Rinegine::Kernel::Flags::has(head_out->flags, MEM_FLAG::INIT)) {
                      while (head_out->size < (bytes /*+ sizeof(MEM_HEAD) + sizeof(MEM_TAIL)*/)) {//todo there may be a bug
                        //RG_LOG_LOCK_DEBUG(std::format("Tested cell debug: now free: {:#x}, size {:d}, m_h {:d}, m_t {:d}, next mem {:#x}", (long long)head_out, head_out->size, sizeof(MEM_HEAD), sizeof(MEM_TAIL), (long long)(((char*)head_out) + head_out->size + sizeof(MEM_HEAD) + sizeof(MEM_TAIL))));
                        head_out = (MEM_HEAD*)(((char*)head_out) + head_out->size + sizeof(MEM_HEAD) + sizeof(MEM_TAIL));
                        if (MEM_CELL_TEST(head_out)) {
                          RG_LOG_LOCK_CRITICAL("Whath the logs");
                        }
                        if (!Rinegine::Kernel::Flags::has(head_out->flags, MEM_FLAG::INIT)) break;
                      }
                    }
                    if (Rinegine::Kernel::Flags::has(head_out->flags, MEM_FLAG::INIT)) {
                      Rinegine::Kernel::Flags::set(head_out->flags, MEM_FLAG::IS_USED);
                      return head_out + 1;
                    }
                    else {
                      //RG_LOG_LOCK_DEBUG(std::format("Check correct sys allocation: size = {:d}; mag is {:s}", now_pool->size, (now_pool->magic == RG_MAG_NUM) ? "correct" : "incorrect"));
                      //[fill mem vars]
                      head_out->size = bytes;
                      head_out->magic = RG_MAG_NUM;
                      head_out->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED | MEM_FLAG::CUSTOM_POOL | MEM_FLAG::INIT);
                      head_out->id = SYS_MEM_ID++;
                      head_out->pool_id = (uint32_t)i;

                      MEM_TAIL* tail = (MEM_TAIL*)(((char*)(head_out + 1)) + bytes);
                      tail->magic1 = RG_MAG_NUM;
                      tail->magic2 = RG_MAG_NUM;

                      MEM_HEAD* next_cell = (MEM_HEAD*)(tail + 1);
                      if (cache->near_free > next_cell)cache->near_free = next_cell;
                      // cache->near_free = (MEM_HEAD*)(tail + 1);
                      cache->used_mem += bytes + sizeof(MEM_TAIL) + sizeof(MEM_HEAD);
                      return head_out + 1;
                    }
                    //[TODO] If the size in near_free is suitable, use it, otherwise look for the nearest free one
                  }
                }
                else {
                  RG_LOG_LOCK_CRITICAL("pool is read only");
                }
              }
              else {
                RG_LOG_LOCK_CRITICAL("pool is not pool lol (idk how do you do that...) late will be added fixex the pool (i think)");
              }
            }
            else {
              RG_LOG_LOCK_CRITICAL("magic num is break... this is placeholder, late will be added fixes the pool (i think)");
            }
          }
          else { // {if now_pool == nullptr}
            //[if pool isn't init, should it init -> then mem get page from size]
            pool_array[i] = SYS_GET_MEM(std::max(bytes + sizeof(MEM_HEAD) * 2 + sizeof(MEM_TAIL) * 2 + sizeof(PoolCache), SYS_PAGE_SIZE * ALLOC_PAGE_COUNT * (i + 1)));
            pool_array[i]->pool_id = SYS_POOL_ID++;
            //[new pool it temp for return from this func. Should returned a point to some cell from pool]
            now_pool = pool_array[i];
            //[HEAD of cell]
            PoolCache* cache = (PoolCache*)(now_pool + 1);
            MEM_HEAD* head_out = (MEM_HEAD*)(cache + 1);
            //RG_LOG_LOCK_DEBUG(std::string("Check correct sys allocation: size = ") + std::to_string(now_pool->size) + "; mag is " + ((now_pool->magic == RG_MAG_NUM) ? "correct" : "incorrect"));
            //[fill mem vars]
            head_out->size = bytes;
            head_out->magic = RG_MAG_NUM;
            head_out->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED | MEM_FLAG::CUSTOM_POOL | MEM_FLAG::INIT);
            // head_out->flags = static_cast<uint32_t>(MEM_FLAG::IS_USED);
            head_out->id = SYS_MEM_ID++;
            head_out->pool_id = (uint32_t)i;

            MEM_TAIL* tail = (MEM_TAIL*)(((char*)(head_out + 1)) + bytes);
            tail->magic1 = RG_MAG_NUM;
            tail->magic2 = RG_MAG_NUM;


            // cache->near_free = (MEM_HEAD*)(((char*)(head_out + 1)) + bytes + sizeof(MEM_TAIL));
            // MEM_HEAD* next_cell = (MEM_HEAD*)(tail + 1);
            // if (cache->near_free > next_cell)cache->near_free = next_cell;

            cache->near_free = (MEM_HEAD*)(tail + 1);
            // rg_cout << (long long)((((char*)(head_out + 1)) + bytes + sizeof(MEM_TAIL)) - (long long)head_out) << std::endl;
            // rg_cout << (sizeof(MEM_HEAD) * 2 + sizeof(MEM_TAIL) * 2 + bytes);
            //[POOL_MEM_HEAD|POOL_CACHE|MEM_HEAD|data|TAIL|POOL_TAIL]
            cache->used_mem = bytes + sizeof(MEM_TAIL) * 2 + sizeof(MEM_HEAD) * 2 + sizeof(PoolCache);
            return head_out + 1;
          }
          RG_LOG_LOCK_CRITICAL("Allocator::allocate(size_t): You've stumbled upon a case that's not ready yet.");
          return nullptr;
        }
        //[target,point,and other -> return correct cell also if first cell already exist]
        return nullptr;//[todo]
      }
      void deallocate(void* in) {
        if (MEM_CELL_TEST(in)) {
          //RG_LOG_LOCK_ERROR(std::format("deallocate: in ptr isn't RG type"));
          return;
        }
        MEM_HEAD* head = ((MEM_HEAD*)in) - 1;
        if (!Rinegine::Kernel::Flags::has(head->flags, MEM_FLAG::IS_USED)) {
          //RG_LOG_LOCK_WARN(std::format("deallocate: mem {:d} already dealocated", head->id));
          return;
        }
        if (!Rinegine::Kernel::Flags::has(head->flags, MEM_FLAG::CUSTOM_POOL)) {
          //RG_LOG_LOCK_WARN("deallocate: No optimization was applied because the MEM_FLAG::CUSTOM_POOL flag was disabled.");
        }
        else {
          MEM_HEAD** pool_array = (MEM_HEAD**)(pool.pool + 1);
          PoolCache* cache = (PoolCache*)(pool_array[head->pool_id] + 1);
          if (cache->near_free > head)cache->near_free = head;
          cache->used_mem -= head->size + sizeof(MEM_TAIL) + sizeof(MEM_HEAD);
        }
        Rinegine::Kernel::Flags::clear(head->flags, MEM_FLAG::IS_USED);
        //RG_LOG_LOCK_MEM(std::format("Mem {:d} has been deallocated", head->id));
      }
      // void test() {
      //   //RG_LOG_LOCK_DEBUG("pool == " + std::to_string((long long)pool.pool));
      // }
      void clear() {
        if (pool.pool == nullptr) {
          //RG_LOG_LOCK_MEM("pool already free");
          return;
        }
        if (pool.pool->magic == RG_MAG_NUM) {
          // size_t count = ((pool.pool->size - sizeof(MEM_HEAD)) / sizeof(MEM_HEAD*) - sizeof(MEM_TAIL));
          size_t count = (pool.pool->size - sizeof(MEM_HEAD) - sizeof(MEM_TAIL)) / sizeof(MEM_HEAD*);
          MEM_HEAD** pool_array = (MEM_HEAD**)(pool.pool + 1);
          for (size_t i = 0; i < count;i++) {
            if (pool_array[i]) {//* delete pool doesn't pool class (if class will be changed it may do some corrupt and UB)
              SYS_DEL_MEM(pool_array[i]);
            }
          }
        }
        else {
          RG_LOG_LOCK_CRITICAL("How and for what??");
        }
        //RG_LOG_LOCK_DEBUG("Some allocator has clearing successfullyl!");
      }
      ~Allocator() {
        clear();
        Rinegine::Kernel::Flags::clear(pool.pool->flags, MEM_FLAG::LOCKED);
        pool.destruct();
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
      // //RG_LOG_LOCK_INFO("Next");
      RG_LOG_LOCK_INFO("Next");
      RG_LOG_LOCK_INFO("Try init 40 bytes");
      char* temp2 = (char*)test.allocate(40);
      RG_LOG_LOCK_INFO("Check size and mag num");
      RG_LOG_LOCK_INFO(std::format("Size: {:d} mag num is {:s}", (((MEM_HEAD*)temp2) - 1)->size, (((((MEM_HEAD*)temp2) - 1)->magic == RG_MAG_NUM) ? "correct" : "incorrect")));
      RG_LOG_LOCK_INFO("Try fill it");
      for (int i = 0;i < 40;i++) {
        temp2[i] = (char)i;
      }
      // //RG_LOG_LOCK_INFO
      // //RG_LOG_LOCK_INFO(std::string("Size: ") + std::to_string((((MEM_HEAD*)temp) - 1)->size) + ", mag num is " + (((((MEM_HEAD*)temp) - 1)->magic == RG_MAG_NUM) ? "correct" : "incorrect"));
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


    //[VISUAL ALLOCATOR]
    //*|  MAIN POOL                   | //[DONE]//
    //*|  [HEAD|Pools pointers|TAIL]  | //[DONE]//
    //*|  Other pools                 | //[DONE]//
    //*|  [HEAD|CACHE|mem cells|TAIL] | //[DONE]//
    //*|  Mem cells                   | //[DONE]//
    //*|  [HEAD|data|TAIL]            | //[DONE]//

    //[TODO NOTE]
    //[+1] Do mem head
    //[+2] Do func to get mem pages
    //[+3] Do manage mem cells
    //[+4] Do global mem manager
    //[ ~] 
    //[ ~] 
    //[ ~]

    //[TODO TARGET]
    //[  ] Allocator should return correct mem cell and free this when it need
    //[+1] Manage mem (allocate and deallocate, seek and clean and other todo)
    //[=2] Should be faster, more faster, the fasterest ever any other allocators
    //[ ~] 


  }
}