#pragma once

namespace Rinegine {
static bool notseeitmsgmore = 0;

namespace Lock {

inline static std::atomic_ullong MemUsed = 0;

static size_t page_size = getpagesize();
// magic nums
static int Magic_Num = 8 + (sizeof(size_t));
}

// Allocator
// Kernel::Allocator::;
//! Allocator
/////
// LOW LEVEL ALLOC
void *Kernel::s_page(size_t count, void *addr, int prot, int flags, int fd,
                     off_t offset) {
  if (count == 0) {
    return MAP_FAILED;
  }
  size_t rsize = count * Rinegine::Lock::page_size;
  void *raw_mem = mmap(addr, rsize, prot, flags, fd, offset);
  if (raw_mem != MAP_FAILED) {
    RG_LOG_LOCK_MEM("Mem page alloc: " + std::to_string(rsize) + "b | 0x" +
                    Rinegine::Kernel::itos((size_t)raw_mem, 16));
    Rinegine::Lock::MemUsed += rsize;
  } else {
    // int err = errno;
    RG_LOG_LOCK_ERROR("Mem page alloc: " + std::to_string(rsize) +
                      "b has failed: " + strerror(errno));
  }
  // errno;
  return raw_mem;
}
void Kernel::s_depage(void *addr, size_t count) {
  size_t rsize = count * Rinegine::Lock::page_size;
  if (munmap(addr, rsize)) {
    int err = errno;
    RG_LOG_LOCK_ERROR("Mem page dealloc: " + std::to_string(rsize) +
                      "b has failed: " + strerror(err)+ " | 0x" +
                    Rinegine::Kernel::itos((size_t)addr, 16));
    if (err == EINVAL)
      RG_LOG_LOCK_INFO("I guess you are trying to delete unallocated memory");

  } else {

    RG_LOG_LOCK_MEM("Mem page dealloc: " + std::to_string(rsize) + "b | 0x" +
                    Rinegine::Kernel::itos((size_t)addr, 16));
    Rinegine::Lock::MemUsed -= rsize;
  }
}

/////
void *
Kernel::Lock::s_new(const size_t &size,
                    const size_t &typesize) { // todo                     ||
                                              // only for linux yet, sorry||
                                              // unoptimazed yet
  if (!notseeitmsgmore) {
    RG_LOG_INFO("At the moment s_new is not ready and it is better to use "
                "standard alternatives");
    notseeitmsgmore = 1;
  }
  if (size == 0)
    return nullptr;

  size_t rsize = ((size * typesize + Rinegine::Lock::Magic_Num) +
                  Rinegine::Lock::page_size - 1) /
                 Rinegine::Lock::page_size * Rinegine::Lock::page_size;

  void *raw_newmem = mmap(nullptr, rsize, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (raw_newmem == MAP_FAILED) {
    for (int i = 1; i <= 30 && !raw_newmem; i++) {
      raw_newmem = mmap(nullptr, rsize, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
      if (raw_newmem == MAP_FAILED)
        RG_LOG_LOCK_ERROR("Memory allocate error, retry: " + std::to_string(i) +
                          "/" + std::to_string(30));
    }
    if (raw_newmem == MAP_FAILED)
      RG_LOG_LOCK_CRITICAL("MEMORY ALLOCATE ERROR");
  }
  if (sizeof(unsigned long long) != 8) { // todo replace to engine init
    RG_LOG_CRITICAL("Your architecture unsupported yet");
  }

  unsigned long long &ptrtypesize = *((unsigned long long *)raw_newmem);
  char *ptrmnum = (char *)raw_newmem;
  size_t &ptr_arrsize = *(size_t *)(((char *)raw_newmem) + 8);

  ptrtypesize = typesize;
  ptrmnum[0] = 'R';
  ptrmnum[1] = 'G';
  ptr_arrsize = size;
  void *out = (void *)((char *)(raw_newmem) + Rinegine::Lock::Magic_Num);
  Rinegine::Lock::MemUsed += rsize;

  RG_LOG_LOCK_MEM("Mem aloc: " + std::to_string(rsize) +
                  "b, type: " + std::to_string(typesize));
#ifdef RG_MEM_LIMIT
  if (Rinegine::Lock::MemUsed >= RG_MEM_LIMIT)
    RG_LOG_LOCK_CRITICAL("Memory limit exceeded");
#endif
  return out;
}

bool Kernel::s_rawmemtest(char *in) {
  if (in[0] == 'R' && in[1] == 'G')
    return true;
  return false;
}

bool Kernel::s_memtest(const void *in) {
  if (in == nullptr)
    return false;
  char *rawmem = (((char *)(in)) - Rinegine::Lock::Magic_Num);
  if (rawmem[1] == 'G' && rawmem[0] == 'R')
    return true;

  return false;
}

const unsigned long long &Kernel::s_get_size(const void *in) {
  if (!s_memtest(in))
    RG_LOG_LOCK_CRITICAL("s_get_size: array is not rg type");
  return (((unsigned long long *)(in)) - 1)[0];
}

char Kernel::s_print(to_rrvalue(char *) in) {
  int temp_size = (int)s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << in[i];
    if (i == temp_size - 1)
      rg_cout << std::endl;
  }
  return '\0';
}

char Kernel::s_print(to_rrvalue(wchar_t *) in) {
  int temp_size = (int)s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    std::wcout << in[i]; // TODO
    if (i == temp_size - 1)
      rg_cout << std::endl;
  }
  return '\0';
}

char Kernel::s_print(to_rrvalue(std::string *) in) {
  int temp_size = (int)s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << "\"";
    rg_cout << rg_to_string(in[i]);
    rg_cout << "\"\n";
  }
  return '\0';
}
char Kernel::s_print(to_rrvalue(std::wstring *) in) {
  int temp_size = (int)s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << rg_to_string(in[i]) << ", ";
  }
  return '\0';
}

char Kernel::s_print(std::string *in) {
  int temp_size = (int)s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << "\"";
    rg_cout << rg_to_string(in[i]);
    rg_cout << "\"\n";
  }
  return '\0';
}
char Kernel::s_print(std::wstring *in) {
  int temp_size = (int)s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << rg_to_string(in[i]) << ", ";
  }
  return '\0';
}

char *Kernel::s_getraw(void *in) {
  return (char *)((unsigned long long *)(in)-1) - (2 + sizeof(unsigned int));
}

template <typename T> decltype(auto) s_move(T &obj) { return (T &&)obj; }

uint Kernel::Lock::s_delete(void *in, unsigned int typesize) {
  if (!Rinegine::Kernel::s_memtest(in))
    return SD_NO_RG_TYPE;
  if (in == nullptr)
    return SD_PTR_IS_NULLPTR;
  int page_size = getpagesize();

  const size_t size = Rinegine::Kernel::s_get_size(in);

  size_t rsize =
      ((size * typesize + Rinegine::Lock::Magic_Num) + page_size - 1) /
      page_size * page_size;

  // free(Rinegine::Kernel::s_getraw(in));
  if (munmap((void *)((char *)in - Rinegine::Lock::Magic_Num), rsize) == -1) {
    RG_LOG_ERROR("s_delete deallocate error");
    return SD_DEALOC_ERROR;
  }
  RG_LOG_LOCK_MEM("Mem clean: " + std::to_string(rsize) +
                  "b, type: " + std::to_string(typesize));
  Rinegine::Lock::MemUsed -= rsize;
  return SD_NO_ERR;
  //
}
void *Kernel::Lock::s_fast_new(const unsigned long long &size,
                               const unsigned long long &typesize) {
  char *newmem = (char *)malloc(size * typesize + sizeof(unsigned long long) +
                                sizeof(unsigned int) + sizeof(char) * 2);
  if (!newmem) {
    RG_LOG_LOCK_ERROR("Fast alloc failed, try standard alloc");
    void *out = Kernel::Lock::s_new(size, typesize);
    return out;
  }

  newmem[0] = 'R';
  newmem[1] = 'G';
  unsigned int *stypesize = (unsigned int *)(newmem + 2);
  stypesize[0] = (unsigned int)typesize;
  unsigned long long *ssize = (unsigned long long *)(stypesize + 1);
  ssize[0] = size;
  void *out = (void *)(ssize + 1);
  Rinegine::Lock::MemUsed += size * typesize + sizeof(unsigned long long) +
                             sizeof(unsigned int) + sizeof(char) * 2;
  return out;
}

void Kernel::Lock::s_fast_delete(void *in, unsigned int typesize) {
  if (!Rinegine::Kernel::s_memtest(in))
    return;
  const unsigned long long &size = Rinegine::Kernel::s_get_size(in);
  Rinegine::Lock::MemUsed -=
      size * typesize + sizeof(unsigned long long) + sizeof(char) * 2;
  free(Rinegine::Kernel::s_getraw(in));
  in = nullptr;
}

unsigned int Kernel::s_get_typesize(void *in) {
  if (!s_memtest(in)) {
    RG_LOG_LOCK_CRITICAL("s_get_typesize: array is not RG type");
  }
  return *((unsigned int *)((unsigned long long *)(in)-1) - 1);
}
}
