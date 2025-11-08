#pragma once

namespace Rinegine {
static bool notseeitmsgmore = 0;

const size_t Kernel::Lock::page_size = getpagesize();
namespace Lock {

inline static std::atomic_ullong MemUsed = 0;

// magic nums
static int Magic_Num = 8 + (sizeof(size_t));
} // namespace Lock

//** Allocator
void Kernel::Allocator::init() {
  if (_main_map == nullptr) {
    // std::cout << "init" << std::endl;
    RG_LOG_LOCK_MEM("Allocator init");
    _main_map = s_map(1);
    g_page_mask = ~(uintptr_t)(Rinegine::Kernel::Lock::page_size - 1);
  }
}
void Kernel::Allocator::push(size_t in) {
  // std::cout << "push" << std::endl;
  RG_LOG_LOCK_MEM("Push " + std::to_string(in) + " page(s)");
  Kernel::Allocator::_map *addr = s_map(in);

  if (addr != nullptr) {
    Kernel::Allocator::_map *mmin = rg_min(addr, _main_map);
    Kernel::Allocator::_map *mmax = rg_max(addr, _main_map);
    if (size_t(mmax) - size_t(mmin) == Rinegine::Kernel::Lock::page_size * in) {
      // std::cout << "prev: " << (int)mmax->magnum[2] << std::endl;
      mmin->_mem.next = &mmax->_mem;
      mmin->magnum[2] += mmax->magnum[2];
      mmax->magnum[0] = 0;
      mmax->magnum[1] = 0;
      mmax->magnum[2] = 0;

      _main_map = mmin;
      if (_main_map->magnum[2] == UINT8_MAX) {
        RG_LOG_LOCK_CRITICAL("Strange, but the size of the page pool has "
                             "become too large, the number of pages is " +
                             std::to_string(size_t(_main_map->magnum[2])));
      }
    } else {
      RG_LOG_LOCK_MEM("Error! Failed to add page to shared heap!");
      RG_LOG_LOCK_DEBUG("size_t(mmax) - size_t(mmin) = " +
                        std::to_string(size_t(mmax) - size_t(mmin)));
      print_map();
      RG_LOG_LOCK_CRITICAL("Mem error, see previous log");
    }
  }
}
Kernel::Allocator::_map *Kernel::Allocator::s_map(size_t count) {
  /**/
  void *addr = _main_map;
  int prot = PROT_READ | PROT_WRITE;
  int flags = MAP_PRIVATE | MAP_ANONYMOUS;
  int fd = -1;
  off_t offset = 0;
  /**/
  if (count == 0) {
    return (Kernel::Allocator::_map *)MAP_FAILED;
  }
  size_t rsize = count * Rinegine::Kernel::Lock::page_size;

  Kernel::Allocator::_map *out =
      (Kernel::Allocator::_map *)mmap(addr, rsize, prot, flags, fd, offset);
  // std::cout << "Map address: " << out << std::endl;
  if (out == (MAP_FAILED) || out == nullptr || out == NULL) {
    RG_LOG_LOCK_MEM(
        "Allocator error; s_map error;"); // +
                                          // rg_string(strerror(errno)));//todo
                                          // fix
    RG_LOG_LOCK_CRITICAL(
        "s_map error, perhaps there is not enough space, see previous log");
  } else {
    ((char *)out)[0] = 'R';
    ((char *)out)[1] = 'G';
    ((char *)out)[2] = 1;
  }
  return out;
}
void *Kernel::Allocator::s_new(size_t count, size_t type_size) {
  // If there is potentially not enough space in the heap
  if ((count * type_size + sizeof(Kernel::Allocator::_map::mem) * 1) >
      // actual size > pagesize * count merged pages - header //todo remove
      Rinegine::Kernel::Lock::page_size * _main_map->magnum[2] - sizeof(_map)) {
    RG_LOG_LOCK_MEM("map less then new array size, push new page...");
    RG_LOG_LOCK_MEM("size array + head: " +
                    std::to_string(count * type_size +
                                   sizeof(Kernel::Allocator::_map::mem) * 1));
    RG_LOG_LOCK_MEM("size page: " +
                    std::to_string(Rinegine::Kernel::Lock::page_size));
    RG_LOG_LOCK_MEM("count page in map: " +
                    std::to_string(_main_map->magnum[2]));
    RG_LOG_LOCK_MEM("Available space for allocation (if heap is empty): " +
                    std::to_string(Rinegine::Kernel::Lock::page_size *
                                       _main_map->magnum[2] -
                                   sizeof(Rinegine::Kernel::Allocator::_map)));
    push((count * type_size + sizeof(Kernel::Allocator::_map::mem) * 1) /
         (Rinegine::Kernel::Lock::page_size -
          sizeof(Rinegine::Kernel::Allocator::_map)));
    // RG_LOG_LOCK_CRITICAL(
    // "Turn RG_D_W_L = 4; This hasn't yet been implemented");
  }
  Kernel::Allocator::_map::mem *out = &_main_map->_mem;
  while (true) {
    if (out->init == false) {
      if (((out->next) &&
           (size_t(out->next) - size_t(out)) <
               (count * type_size + sizeof(Kernel::Allocator::_map::mem)))) {

        Kernel::Allocator::_map::mem *next = out->next;
        Kernel::Allocator::_map::mem *next2 = out;
        while (next != nullptr && next->init == false) {
          // std::cout << "Cell " << size_t(next2) << " and " << size_t(next)
          // << " merged" << std::endl;
          next2 = next;
          next = next->next;
        }
        out->next = next2->next;
        if (((out->next) &&
             (size_t(out->next) - size_t(out)) <
                 (count * type_size + sizeof(Kernel::Allocator::_map::mem)))) {
          out = out->next;
          continue;
        }
        break;
      }
      break;
    } else {
      if (out->next == nullptr)
        RG_LOG_LOCK_CRITICAL("ITS IS IMPOSIBLE!!!");
      out = out->next;
    }
  }
  if (out->init && out->next == nullptr) {
    RG_LOG_LOCK_ERROR("The cell is initialized but the next cell has not "
                      "been created, deleting this cell");
  }

  if (out->next) {
    if ((char *)out + sizeof(Kernel::Allocator::_map::mem) + count * type_size +
            sizeof(Kernel::Allocator::_map::mem) <=
        (char *)out->next) {
      Kernel::Allocator::_map::mem *temp =
          (Kernel::Allocator::_map::mem *)(((char *)out) + (count * type_size) +
                                           sizeof(
                                               Kernel::Allocator::_map::mem));
      temp->next = out->next;
      temp->init = 0;
      out->next = temp;
    }
  } else {

    RG_LOG_LOCK_MEM("Not enough space, create new cell:");
    size_t temp =
        (size_t(_main_map) + Kernel::Lock::page_size * _main_map->magnum[2]) -
        (size_t(out) + sizeof(Kernel::Allocator::_map::mem));
    // }

    size_t temp2 =
        (count * type_size + sizeof(Kernel::Allocator::_map::mem) * 2);
    RG_LOG_LOCK_MEM("temp (left): " + std::to_string(temp));
    RG_LOG_LOCK_MEM("temp2 (need): " + std::to_string(temp2));
    if (temp > temp2) {

      out->next =
          (Kernel::Allocator::_map::mem *)(((char *)out) + (count * type_size) +
                                           sizeof(
                                               Kernel::Allocator::_map::mem));
      RG_LOG_LOCK_MEM("New cell: 0x" +
                      Rinegine::Kernel::itos(size_t(out->next), 16));
      RG_LOG_LOCK_MEM("Free space left: " +
                      std::to_string(size_t(_main_map) - size_t(out->next) +
                                     Rinegine::Kernel::Lock::page_size));
      RG_LOG_LOCK_MEM("Need space: " +
                      std::to_string((count * type_size +
                                      sizeof(Kernel::Allocator::_map::mem))));
    } else {
      RG_LOG_LOCK_MEM("No free space in old page, create new page...");
      push();
      // print_map();
      return s_new(count, type_size);
    }
  }
  out->init = true;
  // print_map();
  return (out + 1);
}
void Kernel::Allocator::s_free(void *in) {
  Kernel::Allocator::_map::mem *temp = ((Kernel::Allocator::_map::mem *)in - 1);
  if (temp->init == 1) {
    temp->init = false;
  }
  elif (temp->init == 0) {
    RG_LOG_LOCK_MEM("Memory is corrupted or has already been cleared");
    RG_LOG_LOCK_ERROR("Invalid mem in s_delete");
  }
  else {
    RG_LOG_LOCK_MEM(
        "Damaged memory or memory not from the engine was received");
    RG_LOG_LOCK_CRITICAL("Invalid mem in s_delete");
  }
}
void Kernel::Allocator::print_map() {
  if (_main_map == nullptr)
    return;
  RG_LOG_LOCK_DEBUG("Debug info about map");
  std::cout << std::dec << "Size map: "
            << _main_map->magnum[2] * Rinegine::Kernel::Lock::page_size
            << std::endl;
  std::cout << "Heap:\n";
  Kernel::Allocator::_map::mem *temp = &_main_map->_mem;
  int i = 0;
  while (temp != nullptr) {
    std::cout << "account cell:: " << i << std::endl;
    std::cout << "init: " << temp->init << std::endl;
    std::cout << "size: " << size_t(temp->next) - size_t(temp) << std::endl;
    std::cout << "address: " << std::dec << size_t(temp) << std::dec
              << std::endl;
    std::cout << "next: " << std::dec << size_t(temp->next) << std::dec
              << std::endl;
    temp = temp->next;
    i++;
  }
}
//! Allocator
/////
// LOW LEVEL ALLOC
void *Kernel::Lock::s_page(size_t count, void *addr, int prot, int flags,
                           int fd, off_t offset) {
  if (count == 0) {
    return MAP_FAILED;
  }
  size_t rsize = count * Rinegine::Kernel::Lock::page_size;
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
  size_t rsize = count * Rinegine::Kernel::Lock::page_size;
  if (munmap(addr, rsize)) {
    int err = errno;
    RG_LOG_LOCK_ERROR("Mem page dealloc: " + std::to_string(rsize) +
                      "b has failed: " + strerror(err) + " | 0x" +
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
                  Rinegine::Kernel::Lock::page_size - 1) /
                 Rinegine::Kernel::Lock::page_size *
                 Rinegine::Kernel::Lock::page_size;

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
} // namespace Rinegine
