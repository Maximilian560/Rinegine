#pragma once

namespace Rinegine {

namespace Lock {

// template <class type> struct CountPointers {
//   inline static int count = 0;
//   inline static int size = 0;
//   inline static type *max_pointer = nullptr;
//   inline static type *min_pointer = nullptr;
// };
// inline static unsigned long long int MemUsed = 0;
inline static std::atomic_ullong MemUsed = 0;
}
void *Kernel::Lock::s_new(const unsigned long long& size, const unsigned long long& typesize) {
  if (size == 0)
    return nullptr;
  char *newmem =
      (char *)malloc(size * typesize + sizeof(unsigned long long) + sizeof(char) * 2);
  if (!newmem) {
    for (int i = 1; i <= 30 && !newmem; i++) {
      newmem =
          (char *)malloc(size * typesize + sizeof(unsigned long long) + sizeof(char) * 2);
      if (newmem == nullptr)
        RG_LOG_LOCK_ERROR("Memory allocate error, retry: " + std::to_string(i) +
                          "/" + std::to_string(30));
    }
    if (newmem == nullptr)
      RG_LOG_LOCK_CRITICAL("MEMORY ALLOCATE ERROR");
  }
  newmem[0] = 'R';
  newmem[1] = 'G';
  unsigned long long *ssize = (unsigned long long *)(newmem + 2);
  ssize[0] = size;
  void *out = (void *)(ssize + 1);
  Rinegine::Lock::MemUsed += size * typesize + sizeof(unsigned long long) + sizeof(char) * 2;
  RG_LOG_LOCK_MEM(
      "Mem aloc: " +
      std::to_string(size * typesize + sizeof(unsigned long long) + sizeof(char) * 2) +
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
  char *rawmem = (char *)((unsigned long long *)(in)-1) - 2;
  if (rawmem[1] == 'G' && rawmem[0] == 'R')
    return true;
  return false;
}

const unsigned long long RG_NULL_SIZE = 0;
const unsigned long long &Kernel::s_get_size(const void *in) {
  if (s_memtest(in))
    return (((unsigned long long *)(in)) - 1)[0];
  return RG_NULL_SIZE;
}

char Kernel::s_print(to_rrvalue(char *) in) {
  int temp_size = s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << in[i];
    if (i == temp_size - 1)
      rg_cout << std::endl;
  }
  return '\0';
}

char Kernel::s_print(to_rrvalue(wchar_t *) in) {
  int temp_size = s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    std::wcout << in[i]; // TODO
    if (i == temp_size - 1)
      rg_cout << std::endl;
  }
  return '\0';
}

char Kernel::s_print(to_rrvalue(std::string *) in) {
  int temp_size = s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << "\"";
    rg_cout << rg_to_string(in[i]);
    rg_cout << "\"\n";
  }
  return '\0';
}
char Kernel::s_print(to_rrvalue(std::wstring *) in) {
  int temp_size = s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << rg_to_string(in[i]) << ", ";
  }
  return '\0';
}

char Kernel::s_print(std::string *in) {
  int temp_size = s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << "\"";
    rg_cout << rg_to_string(in[i]);
    rg_cout << "\"\n";
  }
  return '\0';
}
char Kernel::s_print(std::wstring *in) {
  int temp_size = Kernel::s_get_size(in);
  for (int i = 0; i < temp_size; i++) {
    rg_cout << rg_to_string(in[i]) << ", ";
  }
  return '\0';
}

char *Kernel::s_getraw(void *in) { return ((char *)((unsigned long long *)(in)-1) - 2); }

template <typename T> decltype(auto) s_move(T &obj) { return (T &&)obj; }

void Kernel::Lock::s_delete(void *in, unsigned int typesize) {
  if (in == nullptr)
    return;
  if (Rinegine::Kernel::s_memtest(in)) {
    const unsigned long long &size = Rinegine::Kernel::s_get_size(in);

    RG_LOG_LOCK_MEM("Mem clean: " +
                    std::to_string(Rinegine::Kernel::s_get_size(in) * typesize +
                                   sizeof(unsigned long long) + sizeof(char) * 2) +
                    "b, type: " + std::to_string(typesize));

    Rinegine::Lock::MemUsed -=
        size * typesize + sizeof(unsigned long long) + sizeof(char) * 2;

    // unsigned long long *clearsize = ((unsigned long long *)(in)) - 1;
    // *clearsize = 0;
    free(Rinegine::Kernel::s_getraw(in));
    in = nullptr;
  } else {
    RG_LOG_LOCK_WARNING("Memory Deallocation is failed, array is not RG type");
    free(in);
    in = nullptr;
  }
}
void *Kernel::Lock::s_fast_new(const unsigned long long &size,
                               const unsigned long long &typesize) {
  char *newmem =
      (char *)malloc(size * typesize + sizeof(unsigned long long) + sizeof(char) * 2);
  if (!newmem) {
    RG_LOG_LOCK_ERROR("Fast alloc failed, try standard alloc");
    void *out = Kernel::Lock::s_new(size, typesize);
    return out;
  }

  newmem[0] = 'R';
  newmem[1] = 'G';
  unsigned long long *ssize = (unsigned long long *)(newmem + 2);
  ssize[0] = size;
  void *out = (void *)(ssize + 1);
  Rinegine::Lock::MemUsed += size * typesize + sizeof(unsigned long long) + sizeof(char) * 2;
  return out;
}

void Kernel::Lock::s_fast_delete(void *in, unsigned int typesize) {
  if (!Rinegine::Kernel::s_memtest(in))
    return;
  const unsigned long long &size = Rinegine::Kernel::s_get_size(in);
  Rinegine::Lock::MemUsed -= size * typesize + sizeof(unsigned long long) + sizeof(char) * 2;
  free(Rinegine::Kernel::s_getraw(in));
  in = nullptr;
}
}
