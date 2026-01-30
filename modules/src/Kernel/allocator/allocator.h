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
    // char* out = (char*)malloc(size * typesize + 2 + sizeof(size_t) * 2);
    // RG_LOG_LOCK_DEBUG("mem debug:");
    // RG_LOG_LOCK_DEBUG("DATA_OUT size is:" + std::to_string(sizeof(DATA_OUT)));
    // DATA_OUT* out = (DATA_OUT*)malloc(size + sizeof(DATA_OUT));
    DATA_OUT* out = (DATA_OUT*)calloc(size + sizeof(DATA_OUT), 1);
    out->magnum[0] = 'R';
    out->magnum[1] = 'G';
    out->size = size;
    // RG_LOG_LOCK_DEBUG("out vars magnum is:" + std::to_string((int)out->magnum[0]) + " " + std::to_string((int)out->magnum[1]));
    // RG_LOG_LOCK_DEBUG("out vars size is:" + std::to_string((int)out->size));
    return (void*)(out + 1);
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
  bool Kernel::Lock::s_memtest(const void* in) {
    // return ((char*)in)[0] == 'R' && ((char*)in)[1] == 'G';
    // RG_LOG_LOCK_DEBUG("memtest debug");
    // RG_LOG_LOCK_DEBUG("in magnum is");
    in = ((DATA_OUT*)in) - 1;
    // RG_LOG_LOCK_DEBUG(std::to_string((int)(((DATA_OUT*)in))->magnum[0]) + " " + std::to_string((int)(((DATA_OUT*)in))->magnum[1]));
    // RG_LOG_LOCK_DEBUG(((char)(((DATA_OUT*)in))->magnum[0]) + " || " + ((char)(((DATA_OUT*)in))->magnum[1]));

    // RG_LOG_LOCK_DEBUG(((char)(((DATA_OUT*)in)-1)->magnum[0]) + " || " + ((char)(((DATA_OUT*)in)-1)->magnum[1]));
    // return (((DATA_OUT*)in)-1)->magnum[0] == 'R' && (((DATA_OUT*)in)-1)->magnum[1] == 'G';
    // return ((DATA_OUT*)(((char*)in) - sizeof(DATA_OUT))->magnum[0] == 'R' && ((DATA_OUT*)(((char*)in) - sizeof(DATA_OUT))->magnum[1] == 'G'));
    return ((DATA_OUT*)in)->magnum[0] == 'R' && ((DATA_OUT*)in)->magnum[1] == 'G';
  }
  //*DELETE
  uint Kernel::Lock::s_delete(void* in) {
    if (!s_memtest(in)) { RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");return 0; }
    static size_t size = s_get_size(in);
    MemUsed -= size;
    RG_LOG_LOCK_MEM("Dealloc: '" + std::to_string(size) + "' bytes");
    free(((DATA_OUT*)in) - 1);
    return 0;
    // MemUsed -= ;
    // free
  }
  void Kernel::Lock::s_fast_delete(void* in) {
    if (!s_memtest(in)) { RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");return; }
    static size_t size = s_get_size(in);
    MemUsed -= size;
    free(((DATA_OUT*)in) - 1);
    return;
  }
}