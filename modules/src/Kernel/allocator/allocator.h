#pragma once

namespace Rinegine {
  inline static std::atomic_ullong MemUsed = 0;
  // struct DATA_OUT{
  //   size_t size = 0;
  //   size_t typesize = 0;
  //   char magnum[2] = "RG";
  // };
  //*ALLOC
  void* Kernel::Lock::s_new(const size_t& size) { // [STUB]
    if (size <= 0) return nullptr;
    MemUsed += size + sizeof(DATA_OUT);
    RG_LOG_LOCK_MEM("Alloc: '" + std::to_string(size) + "' bytes");
    DATA_OUT* out = (DATA_OUT*)malloc(size + sizeof(DATA_OUT));
    memset((long*)out, 0, sizeof(DATA_OUT));
    out->magnum[0] = 'R';
    out->magnum[1] = 'G';
    out->size = size;
    return (void*)(out + 1);
  }
  inline DATA_OUT* s_raw_new(const size_t& size) { // [STUB]
    if (size <= 0) return nullptr;
    MemUsed += size + sizeof(DATA_OUT);
    RG_LOG_LOCK_MEM("Alloc: '" + std::to_string(size) + "' bytes");
    DATA_OUT* out = (DATA_OUT*)calloc(size + sizeof(DATA_OUT),1);
    // DATA_OUT* out = (DATA_OUT*)malloc(size + sizeof(DATA_OUT));
    memset((long*)out, 0, sizeof(DATA_OUT));
    out->magnum[0] = 'R';
    out->magnum[1] = 'G';
    out->size = size;
    return out;
  }
  void* Kernel::Lock::s_fast_new(const size_t& size) {
    MemUsed += size + sizeof(DATA_OUT);
    DATA_OUT* out = (DATA_OUT*)malloc(size + sizeof(DATA_OUT));
    out->magnum[0] = 'R';
    out->magnum[1] = 'G';
    out->size = size;
    return (void*)(out + 1);
  }
  //*GETSIZE
  size_t Kernel::Lock::s_get_size(const void* in) {
    return (((DATA_OUT*)in) - 1)->size;
  }
  //*MEMTEST
  int Kernel::Lock::s_memtest(const void* in) {
    if (in == nullptr) return -1;
    in = ((DATA_OUT*)in) - 1;
    return ((DATA_OUT*)in)->magnum[0] == 'R' && ((DATA_OUT*)in)->magnum[1] == 'G';
  }
  //*DELETE
  uint Kernel::Lock::s_delete(void* in) {
    switch (s_memtest(in)) {
    case -1: RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is nullptr");return 0;break;
    case 0: RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type (0x" + Rinegine::Kernel::itos((long long)in, 16) + ")");return 0;break;
    default: break;
    }
    // if (!s_memtest(in)) { RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");return 0; }
    static size_t size = s_get_size(in);
    MemUsed -= size;
    RG_LOG_LOCK_MEM("Dealloc: '" + std::to_string(size) + "' bytes");
    free(((DATA_OUT*)in) - 1);
    return 0;
    // MemUsed -= ;
    // free
  }
  inline uint s_raw_delete(DATA_OUT* in) {
    // switch (s_memtest(in)) {
    // case -1: RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is nullptr");return 0;break;
    // case 0: RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type (0x" + Rinegine::Kernel::itos((long)in, 16) + ")");return 0;break;
    // default: break;
    // }
    // if (!s_memtest(in)) { RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");return 0; }
    // static size_t size = s_get_size(in);
    if(in!=nullptr){
      MemUsed -= in->size;
      RG_LOG_LOCK_MEM("Dealloc: '" + std::to_string(in->size) + "' bytes");
      free(in);
    }
    return 0;
    // MemUsed -= ;
    // free
  }
  void Kernel::Lock::s_fast_delete(void* in) {
    // if (!s_memtest(in)) { RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");return; }
    switch (s_memtest(in)) {
    case -1: RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is nullptr");return;break;
    case 0: RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type (0x" + Rinegine::Kernel::itos((long long)in, 16) + ")");return;break;
    default: break;
    }
    static size_t size = s_get_size(in);
    MemUsed -= size;
    free(((DATA_OUT*)in) - 1);
    return;
  }
  //*RESIZE
  inline void s_raw_resize(DATA_OUT*& inout, const size_t& size) { // [STUB]
    if (size <= 0) { s_raw_delete(inout);return; }
    else {
      RG_LOG_LOCK_MEM("Realloc: '"+std::to_string(inout->size)+"' -> '" + std::to_string(size) + "' bytes");
      inout = (DATA_OUT*)realloc(inout, size + sizeof(DATA_OUT));
      if (!inout) {
        RG_LOG_LOCK_CRITICAL("Memory Reallocation is failed");
      }
      MemUsed += (long)size - (long)inout->size;
      inout->size = size;
    }
    // return out;
  }
}
