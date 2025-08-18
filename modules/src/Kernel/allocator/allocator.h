#pragma once

namespace Rinegine {

namespace Lock {

template <class type> struct CountPointers {
  inline static int count = 0;
  inline static int size = 0;
  inline static type *max_pointer = nullptr;
  inline static type *min_pointer = nullptr;
};
inline static unsigned long long int MemUsed = 0;
}
void *Kernel::Lock::s_new(int size, unsigned int typesize) {
  if (size == 0)
    return nullptr;

  // if (!std::is_default_constructible<type>::value) {
  //   RG_LOG_LOCK_CRITICAL("Type must be default constructible");
  // }

  char *newmem = nullptr;
  for (int i = 1; i <= 30 && !newmem; i++) {
    newmem = (char *)malloc(size * typesize + sizeof(uint) + sizeof(char) * 2);
    if (newmem == nullptr)
      RG_LOG_LOCK_ERROR("Memory allocate error, retry: " + std::to_string(i) +
                        "/" + std::to_string(30));
  }
  if (newmem == nullptr)
    RG_LOG_LOCK_CRITICAL("MEMORY ALLOCATE ERROR");

  newmem[0] = 'R';
  newmem[1] = 'G';

  uint *ssize = (uint *)(newmem + 2);
  ssize[0] = size;

  void *out = (void *)(ssize + 1);
  // for (int i = 0; i < size; i++) {
  //   new (out + i) type(); // Placement new
  // }
  /*
    Rinegine::Lock::CountPointers<type>::count++;
    Rinegine::Lock::CountPointers<type>::size += size;

      if (Rinegine::Lock::CountPointers<type>::max_pointer == nullptr)
      Rinegine::Lock::CountPointers<type>::max_pointer = out;
    else
      Rinegine::Lock::CountPointers<type>::max_pointer =
          rg_max(Rinegine::Lock::CountPointers<type>::max_pointer, out);

      if (Rinegine::Lock::CountPointers<type>::min_pointer == nullptr)
      Rinegine::Lock::CountPointers<type>::min_pointer = out;
    else
      Rinegine::Lock::CountPointers<type>::min_pointer =
          rg_min(Rinegine::Lock::CountPointers<type>::min_pointer, out);
  */
  Rinegine::Lock::MemUsed += size * typesize + sizeof(uint) + sizeof(char) * 2;

  RG_LOG_LOCK_MEM(
      "Mem aloc: " +
      std::to_string(size * typesize + sizeof(uint) + sizeof(char) * 2) +
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
  char *rawmem = (char *)((uint *)(in)-1) - 2;
  if (rawmem[1] == 'G' && rawmem[0] == 'R')
    return true;
  return false;
}

const uint RG_NULL_SIZE = 0;
const uint &Kernel::s_get_size(const void *in) {
  if (s_memtest(in))
    return (((uint *)(in)) - 1)[0];
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

char *Kernel::s_getraw(void *in) { return ((char *)((uint *)(in)-1) - 2); }


template <typename T> decltype(auto) s_move(T &obj) { return (T &&)obj; }

void Kernel::Lock::s_delete(void *in, unsigned int typesize) {
  if (in == nullptr)
    return;
  if (Rinegine::Kernel::s_memtest(in)) {
    const uint &size = Rinegine::Kernel::s_get_size(in);

    RG_LOG_LOCK_MEM("Mem clean: " +
                    std::to_string(Rinegine::Kernel::s_get_size(in) * typesize +
                                   sizeof(uint) + sizeof(char) * 2) +
                    "b, type: " + std::to_string(typesize));

    Rinegine::Lock::MemUsed -=
        size * typesize + sizeof(uint) + sizeof(char) * 2;

    uint *clearsize = ((uint *)(in)) - 1;
    *clearsize = 0;
    free(Rinegine::Kernel::s_getraw(in));
    in = nullptr;
  } else {
    RG_LOG_LOCK_WARNING("Memory Deallocation is failed, array is not RG type");
    free(in);
    in = nullptr;
  }
}
template <class type> void Kernel::s_resize(type *&p, to_rvalue(int) newsize) {
  if (newsize > 0) {
    if (p != nullptr) {
      if (!s_memtest(p)) {
        RG_LOG_LOCK_ERROR("Memory Resize is failed, array is not RG type");
        return;
      };
      int size = s_get_size(p);
      if (size != newsize) {
        type *out = s_new<type>(newsize);
        for (int i = 0; i < rg_min(size, newsize); i++) {
          out[i] = std::move(p[i]);
        }
        s_delete<type>(p);
        p = out;
        return;
      } else
        return;
    } else {
      p = s_new<type>(newsize);

      return;
    }
  } else {
    s_delete(p);
    return;
  }
}
template <class type> void Kernel::s_renew(type *&p, to_rvalue(int) newsize) {
  if (newsize > 0) {
    if (p != nullptr) {
      if (!s_memtest(p)) {
        RG_LOG_LOCK_ERROR("Memory Renew is failed, array is not RG type");
        return;
      };
      int size = s_get_size(p);
      if (size != newsize) {
        s_delete<type>(p);
        p = s_new<type>(newsize);
      }
    } else {
      p = s_new<type>(newsize);
    }
  } else {
    s_delete(p);
    return;
  }
}

template <class type>
int Kernel::s_erase(
    type *&p, int arrsize, int pos,
    int size) { // p - начала массива, arrsize - размер массива, pos - начала
                // удаления, size - количество элементов для удаления
  RG_LOG_LOCK_WARNING("function s_erase(type*& p, int arrsize, int pos, int "
                      "size) is deprecated. Please refer to the documentation");
  if (size == 0)
    return arrsize;
  int eracesize = size;
  int eracepos = pos;
  if (pos + size > arrsize) {
    RG_LOG_LOCK_ERROR("s_erase, size+pos is greater than the size of the "
                      "passed array, erase pos = '" +
                      std::to_string(pos) + "', erase size = '" +
                      std::to_string(size) + "', array size = '" +
                      std::to_string(arrsize) + "'");
  }
  if (pos > arrsize) {
    RG_LOG_LOCK_CRITICAL("s_erase, pos is greater than the size of the passed "
                         "array, erase pos = '" +
                         std::to_string(pos) + "',array size = '" +
                         std::to_string(arrsize) + "'");
  }
  if (arrsize <= 0)
    RG_LOG_LOCK_CRITICAL(
        "s_erase, array size less than or equal to 0, array size = " +
        std::to_string(arrsize) + "'");
  if (pos < 0)
    eracepos = arrsize + pos;
  if (size < 0) {
    if (size + pos <= 0)
      RG_LOG_LOCK_CRITICAL(
          "I'm tired of writing errors, but here it's supposedly position + "
          "cleanup size is less than zero, understand it as you want. And i "
          "want to sleep.\n");
  }
  if (pos + size > arrsize)
    eracesize = arrsize - pos;
  if (arrsize - size <= 0) {
    RG_LOG_LOCK_DEBUG("s_erase, array size less than or equal to 0");
    s_delete(p);
    return 0;
  }
  type *a = s_new<type>(arrsize - size); // new type[arrsize-size];
  for (int i = 0; i < arrsize - eracesize; i++) {
    if (i >= pos) {
      a[i] = p[i + eracesize];
    } else {
      a[i] = p[i];
    }
  }
  s_delete(p);
  p = a;
  return arrsize - eracesize;
}

template <class type>
int Kernel::s_erase_new(
    type *&p, int pos,
    int size) { // p - начала массива, arrsize - размер массива, pos - начала
                // удаления, size - количество элементов для удаления
  RG_LOG_LOCK_WARNING("function s_erase(type*& p, int arrsize, int pos, int "
                      "size) is deprecated. Please refer to the documentation");
  if (!s_memtest(p)) {
    RG_LOG_LOCK_ERROR("s_erase, array is not of type RG, 'size' 0 returned");
    return 0;
  }
  uint arrsize = s_get_size(p);
  if (size == 0)
    return arrsize;
  int eracesize = size;
  int eracepos = pos;
  if (pos + size > arrsize) {
    RG_LOG_LOCK_ERROR("s_erase, size+pos is greater than the size of the "
                      "passed array, erase pos = '" +
                      std::to_string(pos) + "', erase size = '" +
                      std::to_string(size) + "', array size = '" +
                      std::to_string(arrsize) + "'");
  }
  if (pos > arrsize) {
    RG_LOG_LOCK_CRITICAL("s_erase, pos is greater than the size of the passed "
                         "array, erase pos = '" +
                         std::to_string(pos) + "',array size = '" +
                         std::to_string(arrsize) + "'");
  }
  if (arrsize <= 0)
    RG_LOG_LOCK_CRITICAL(
        "s_erase, array size less than or equal to 0, array size = " +
        std::to_string(arrsize) + "'");
  if (pos < 0)
    eracepos = arrsize + pos;
  if (size < 0) {
    if (size + pos <= 0)
      RG_LOG_LOCK_CRITICAL(
          "I'm tired of writing errors, but here it's supposedly position + "
          "cleanup size is less than zero, understand it as you want. And i "
          "want to sleep.\n");
  }
  if (pos + size > arrsize)
    eracesize = arrsize - pos;
  if (arrsize - size <= 0) {
    RG_LOG_LOCK_DEBUG("s_erase, array size less than or equal to 0");
    s_delete(p);
    return 0;
  }
  type *a = s_new<type>(arrsize - size); // new type[arrsize-size];
  for (int i = 0; i < arrsize - eracesize; i++) {
    if (i >= pos) {
      a[i] = p[i + eracesize];
    } else {
      a[i] = p[i];
    }
  }
  s_delete(p);
  p = a;
  return arrsize - eracesize;
}

//////ALLOCATE MAIN END

template <class type> int Kernel::Get_Count_Pointers() {
  return Lock::CountPointers<type>::count;
}

template <class type> Kernel::Array<type *> Kernel::Get_All_Pointers() {
  Kernel::Array<type *> out(Lock::CountPointers<type>::count);
  long long contin = Lock::CountPointers<type>::min_pointer;
  for (int i = 0; i < Lock::CountPointers<type>::count; i++) {
    for (long long j = contin; j < Lock::CountPointers<type>::max_pointer;
         j++) {
      if (s_memtest((type *)j)) {
        contin = j + 1;
        out[i] = (type *)j;
        break;
      }
    }
  }
  return out;
}
}