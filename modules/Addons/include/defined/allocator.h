#pragma once

template<class type>
class RG_Array;
namespace RG {
  namespace Lock {

    template <class type>
    struct CountPointers {
      inline static int count = 0;
      inline static int size = 0;
      inline static type* max_pointer = nullptr;
      inline static type* min_pointer = nullptr;
    };
    unsigned long long int MemUsed = 0;
    //     template<class type>
    //     inline type* s_new(to_rvalue(int) size) {
    //       if (size == 0)return nullptr;
    //       char* newmem = (char*)malloc(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2);
    //       if (newmem == nullptr)RG_Debug::addl(RG_LOG_CRITICAL, "MEMORY ALLOCATE ERROR");
    //       newmem[0] = 'R';
    //       newmem[1] = 'G';
    //       uint* ssize = (uint*)(newmem + 2);
    //       ssize[0] = size;
    //       type* out = ((type*)(ssize + 1));
    //       for (int i = 0; i < size; i++) {
    //         new (out + i) type();  // Placement new
    //       }
    //       Lock::CountPointers<type>::count++;
    //       Lock::CountPointers<type>::size += size;
    //       if (Lock::CountPointers<type>::max_pointer == nullptr)CountPointers<type>::max_pointer = out;else
    //         Lock::CountPointers<type>::max_pointer = rg_max(Lock::CountPointers<type>::max_pointer, out);
    //       if (Lock::CountPointers<type>::min_pointer == nullptr)CountPointers<type>::min_pointer = out;else
    //         Lock::CountPointers<type>::min_pointer = rg_min(Lock::CountPointers<type>::min_pointer, out);
    //       //RG_Debug::addl(RG_LOG_MEM,"Some type size is '"+to_string(sizeof(type))+"' has already taken up '"+to_string(Lock::CountPointers<type>::size*sizeof(type))+"' bytes");
    //       Lock::MemUsed += size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;
    //       /*#ifdef RG_MEMLOG
    //       RG_Debug::addl(RG_LOG_MEM,"Memory occupied by the program: '"+to_string(Lock::MemUsed)+"' bytes or '"+to_string(Lock::MemUsed/1024./1024.)+" MB'");
    //       #else
    //       RG_Debug::addl(RG_LOG_MEM,"Memory occupied by the program: '"+to_string(Lock::MemUsed)+"' bytes or '"+to_string(Lock::MemUsed/1024./1024.)+" MB'",false);
    //       #endif*/

    //       RG_Debug::addl(RG_LOG_MEM, "Memory allocate: '" + to_string(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) + "' bytes or '" + to_string((size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) / 1024. / 1024.) + " MB'");

    // #ifdef RG_MEM_LIMIT
    //       if (Lock::MemUsed >= RG_MEM_LIMIT)RG_Debug::addl(RG_LOG_CRITICAL, "Memory limit exceeded");
    // #endif
    //       return out;
    //     }




  }//Lock
  //////ALLOCATE MAIN


  template<class type>
  inline type* s_new(int size) {
    if (size == 0) return nullptr;

    static_assert(std::is_default_constructible<type>::value, "Type must be default constructible");
    char* newmem = nullptr;
    for (int i = 1; i <= 30 && !newmem; i++) {
      newmem = (char*)malloc(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2);
      if (newmem == nullptr) RG_Debug::addl(RG_LOG_ERROR, "Memory allocate error, retry: "+to_string(i)+"/"+to_string(30));
    }
    if (newmem == nullptr) RG_Debug::addl(RG_LOG_CRITICAL, "MEMORY ALLOCATE ERROR");

    newmem[0] = 'R';
    newmem[1] = 'G';

    uint* ssize = (uint*)(newmem + 2);
    ssize[0] = size;

    type* out = (type*)(ssize + 1);
    for (int i = 0; i < size; i++) {
      new (out + i) type(); // Placement new
    }

    Lock::CountPointers<type>::count++;
    Lock::CountPointers<type>::size += size;

    if (Lock::CountPointers<type>::max_pointer == nullptr) Lock::CountPointers<type>::max_pointer = out;
    else Lock::CountPointers<type>::max_pointer = rg_max(Lock::CountPointers<type>::max_pointer, out);

    if (Lock::CountPointers<type>::min_pointer == nullptr) Lock::CountPointers<type>::min_pointer = out;
    else Lock::CountPointers<type>::min_pointer = rg_min(Lock::CountPointers<type>::min_pointer, out);

    Lock::MemUsed += size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;

    RG_Debug::addl(RG_LOG_MEM, "Memory allocate: '" +
      std::to_string(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) +
      "' bytes or '" +
      std::to_string((size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) / 1024. / 1024.) +
      " MB'");

#ifdef RG_MEM_LIMIT
    if (Lock::MemUsed >= RG_MEM_LIMIT) RG_Debug::addl(RG_LOG_CRITICAL, "Memory limit exceeded");
#endif

    return out;
  }

  /*template<class type>
  inline type* s_new(to_rvalue(int) size, type in) {
    type* out = s_new<type>(size);
    for (int i = 0; i < size; i++) {
      out[i] = in;
    }
    return out;
  }*/
  // inline type* s_new(int size, type&& in) {
  template<class type>
  inline type* s_new(int size, type&& in) {
    if (size == 0) return nullptr;
    static_assert(std::is_constructible<type, type&&>::value, "Type must be constructible with the given argument");

    char* newmem = (char*)malloc(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2);
    if (newmem == nullptr) RG_Debug::addl(RG_LOG_CRITICAL, "MEMORY ALLOCATE ERROR");

    newmem[0] = 'R';
    newmem[1] = 'G';
    uint* ssize = (uint*)(newmem + 2);
    ssize[0] = size;

    type* out = (type*)(ssize + 1);
    for (int i = 0; i < size; i++) {
      new (out + i) type(std::forward<type>(in)); // Placement new с учётом перемещений
      // out[i]=in;
    }

    Lock::CountPointers<type>::count++;
    Lock::CountPointers<type>::size += size;
    if (Lock::CountPointers<type>::max_pointer == nullptr) Lock::CountPointers<type>::max_pointer = out;
    else Lock::CountPointers<type>::max_pointer = rg_max(Lock::CountPointers<type>::max_pointer, out);

    if (Lock::CountPointers<type>::min_pointer == nullptr) Lock::CountPointers<type>::min_pointer = out;
    else Lock::CountPointers<type>::min_pointer = rg_min(Lock::CountPointers<type>::min_pointer, out);

    Lock::MemUsed += size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;

    RG_Debug::addl(RG_LOG_MEM, "Memory allocate: '" +
      std::to_string(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) +
      "' bytes or '" +
      std::to_string((size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) / 1024. / 1024.) +
      " MB'");

#ifdef RG_MEM_LIMIT
    if (Lock::MemUsed >= RG_MEM_LIMIT) RG_Debug::addl(RG_LOG_CRITICAL, "Memory limit exceeded");
#endif

    return out;
  }

  template<class type>
  inline type* s_new(int size, const type& in) {
    if (size == 0) return nullptr;
    static_assert(std::is_constructible<type, type&&>::value, "Type must be constructible with the given argument");

    char* newmem = (char*)malloc(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2);
    if (newmem == nullptr) RG_Debug::addl(RG_LOG_CRITICAL, "MEMORY ALLOCATE ERROR");

    newmem[0] = 'R';
    newmem[1] = 'G';
    uint* ssize = (uint*)(newmem + 2);
    ssize[0] = size;

    type* out = (type*)(ssize + 1);
    for (int i = 0; i < size; i++) {
      // new (out + i) type(std::move<type>(in)); // Placement new с учётом перемещений
      out[i] = in;
    }

    Lock::CountPointers<type>::count++;
    Lock::CountPointers<type>::size += size;
    if (Lock::CountPointers<type>::max_pointer == nullptr) Lock::CountPointers<type>::max_pointer = out;
    else Lock::CountPointers<type>::max_pointer = rg_max(Lock::CountPointers<type>::max_pointer, out);

    if (Lock::CountPointers<type>::min_pointer == nullptr) Lock::CountPointers<type>::min_pointer = out;
    else Lock::CountPointers<type>::min_pointer = rg_min(Lock::CountPointers<type>::min_pointer, out);

    Lock::MemUsed += size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;

    RG_Debug::addl(RG_LOG_MEM, "Memory allocate: '" +
      std::to_string(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) +
      "' bytes or '" +
      std::to_string((size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) / 1024. / 1024.) +
      " MB'");

#ifdef RG_MEM_LIMIT
    if (Lock::MemUsed >= RG_MEM_LIMIT) RG_Debug::addl(RG_LOG_CRITICAL, "Memory limit exceeded");
#endif

    return out;
  }



  //template<class type>
  inline bool s_rawmemtest(char* in) {
    if (in[0] == 'R' && in[1] == 'G')return true;
    return false;
  }

  template<class type>
  inline bool s_memtest(type* in) {
    if (in == nullptr)return false;
    char* rawmem = (char*)((uint*)(in)-1) - 2;
    if (rawmem[1] == 'G' && rawmem[0] == 'R')return true;
    return false;
  }


  const uint RG_NULL_SIZE = 0;
  template<class type>
  inline const uint& s_get_size(const type* in) {
    if (s_memtest(in))return(((uint*)(in)) - 1)[0];
    return RG_NULL_SIZE;
  }


  template<class type>
  inline char s_print(type* const& in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << in[i];
      if (i == temp_size - 1)rg_cout << endl; else rg_cout << ',' << ' ';
    }
    return '\0';
  }
  // template<class type>
  // inline char s_print(to_rrvalue(type*) in){
  //   int temp_size = s_get_size(in);
  //   for(int i = 0; i < temp_size;i++){
  //     rg_cout << in[i];
  //     if(i == temp_size - 1)rg_cout << endl;else rg_cout << ',' << ' ';
  //   }
  //   return '\0';
  // }



  inline char s_print(to_rrvalue(char*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << in[i];
      if (i == temp_size - 1)rg_cout << endl;
    }
    return '\0';
  }

  inline char s_print(to_rrvalue(wchar_t*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      wcout << in[i];
      if (i == temp_size - 1)wcout << endl;
    }
    return '\0';
  }

  inline char s_print(to_rrvalue(string*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      rg_cout << "\"";
#ifdef RG_UTF
      wcout << utf8_decode(in[i]);
#else 
      cout << in[i];
#endif
      rg_cout << "\"\n";
      //if (i == temp_size - 1)rg_cout << endl;else rg_cout << ',' << ' ';
    }
    return '\0';
  }
  inline char s_print(to_rrvalue(wstring*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      // rg_cout << "L\"";
      wcout << in[i] << ", ";
      // rg_cout << "\"\n";
      //if (i == temp_size - 1)rg_cout << endl;else rg_cout << ',' << ' ';
    }
    return '\0';
  }



  /*inline char s_print(to_rvalue(char*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size;i++) {
      rg_cout << in[i];
      if (i == temp_size - 1)rg_cout << endl;;
    }
    return '\0';
  }
  inline char s_print(to_rvalue(wchar_t*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size;i++) {
      wcout << in[i];
      if (i == temp_size - 1)wcout << endl;
    }
    return '\0';
  }

  inline char s_print(to_rvalue(string*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size;i++) {
  #ifdef RG_UTF
          wcout << utf8_decode(in[i]);
  #else
          cout << in[i];
  #endif
          if (i == temp_size - 1)rg_cout << endl;else rg_cout << ',' << ' ';
        }
        return '\0';
      }*/

      /*inline char s_print(to_rvalue(wstring*) in) {
        int temp_size = s_get_size(in);
        for (int i = 0; i < temp_size;i++) {
          wcout << in[i];
          if (i == temp_size - 1)rg_cout << endl;else rg_cout << ',' << ' ';
        }
        return '\0';
      }*/
      /*inline void s_print(to_rvalue(wstring*) in) {
        int temp_size = s_get_size(in);
        for (int i = 0; i < temp_size;i++) {
          wcout << in[i];
          if (i == temp_size - 1)rg_cout << endl;else rg_cout << ',' << ' ';
        }
      }*/

  template<class ForwardIt, class Generator>
  constexpr
    inline  void s_fill_func(ForwardIt first, ForwardIt last, Generator g) {
    for (; first != last; ++first)
      *first = g();
  }

  template<class ForwardIt, class Generator>
  constexpr
    inline  void s_fill(ForwardIt first, ForwardIt last, Generator g) {
    for (; first != last; ++first)
      *first = g;
  }
  template<class type, class gen>
  constexpr
    inline  void s_fill_func(type arr, int size, gen g) {
    for (int i = 0; i < size; i++) {
      arr[i] = g();
    }
  }
  template<class type, class gen>
  constexpr
    inline  void s_fill(type arr, int size, gen g) {
    for (int i = 0; i < size; i++) {
      arr[i] = g;
    }
  }

  /*inline char s_print(to_rvalue(wstring*) in) {
    int temp_size = s_get_size(in);
    for (int i = 0; i < temp_size;i++) {
      wcout << in[i];
      if (i == temp_size - 1)wcout << endl; else wcout << ',' << ' ';
    }
    return '\0';
  }*/
  template<class type>
  inline char* s_getraw(type* in) {
    return ((char*)((uint*)(in)-1) - 2);
  }
  /*
  template<class type>
  inline void s_delete(type*& in) {
    Lock::CountPointers<type>::size-=s_get_size(in);
    Lock::MemUsed-=s_get_size(in)*sizeof(type);
    RG_Debug::addl(RG_LOG_MEM,"Memory has been cleared: '"+to_string(s_get_size(in)*sizeof(type))+" bytes");

    char* rawmem = s_getraw(in);
    if (s_rawmemtest(rawmem)) {
      free(rawmem);
      in = nullptr;
    }
    else {
      RG_Debug::addl(RG_LOG_CRITICAL, "Memory Deallocation is failed, array is not RG type");
    }
    Lock::CountPointers<type>::count--;



  }
  template <typename type>
  typename std::enable_if<std::is_class<type>::value>::type
    s_delete(type* p) {
    char* rawmem = (char*)((uint*)(p)-1) - 2;
    if (p) {
      if (s_rawmemtest(rawmem)) {
        for (int i = 0; i < s_get_size(p);i++) {
          p[i].~type();
        }
        free(rawmem);
        p = nullptr;
      }
      else {
        RG_Debug::addl(RG_LOG_CRITICAL, "Memory Deallocation is failed, array is not RG type");
      }
    }
  }

  template <typename type>
  typename std::enable_if<!std::is_class<type>::value>::type
    s_delete(type* p) {
    char* rawmem = (char*)((uint*)(p)-1) - 2;
    if (p) {
      if (s_rawmemtest(rawmem)) {
        free(rawmem);
        p = nullptr;
      }
      else {
        RG_Debug::addl(RG_LOG_CRITICAL, "Memory Deallocation is failed, array is not RG type");
      }
    }
  }


  template<class type>
  inline void s_delete(type*& in) {
    Lock::CountPointers<type>::size-=s_get_size(in);
    Lock::MemUsed-=s_get_size(in)*sizeof(type);
    RG_Debug::addl(RG_LOG_MEM,"Memory has been cleared: '"+to_string(s_get_size(in)*sizeof(type))+" bytes");

    char* rawmem = s_getraw(in);
    if (s_rawmemtest(rawmem)) {
      free(rawmem);
      in = nullptr;
    }
    else {
      RG_Debug::addl(RG_LOG_CRITICAL, "Memory Deallocation is failed, array is not RG type");
    }
    Lock::CountPointers<type>::count--;



  }*/
  template <typename type>
  typename std::enable_if<std::is_class<type>::value, void>::type
    s_delete(type*& in) {
    if (in == nullptr)return;
    if (s_memtest(in)) {
      const uint& size = s_get_size(in);
      // rg_cout<<"ITS CALLED!!!!\n\n";
      // rg_cout<<"size is "<< size * sizeof(type) + sizeof(uint) + sizeof(char) * 2 <<"\n\n";
      RG_Debug::addl(RG_LOG_MEM, "Memory has been cleared: '" + to_string(s_get_size(in) * sizeof(type) + sizeof(uint) + sizeof(char) * 2) + "' bytes");

      Lock::CountPointers<type>::size -= size;
      Lock::MemUsed -= size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;
      for (int i = 0; i < size; i++) {
        // rg_cout << "in[" << i << "] is cleared\n";
        in[i].~type();
      }
      uint* clearsize = ((uint*)(in)) - 1;
      *clearsize = 0;
      free(s_getraw(in));
      in = nullptr;
    } else {
      RG_Debug::addl(RG_LOG_WARNING, "Memory Deallocation is failed, array is not RG type");
      free(in);
      in = nullptr;
    }

  }
  // template <typename type>
  // typename std::enable_if<std::is_class<type>::value, void>::type
  //   s_delete(type*& in) {


  //   if (in == nullptr) return;

  //   if (s_memtest(in)) {
  //     const uint& size = s_get_size(in);

  //     RG_Debug::addl(RG_LOG_MEM, "Memory has been cleared: '" + to_string(s_get_size(in) * sizeof(type) + sizeof(uint) + sizeof(char) * 2) + "' bytes");

  //     Lock::CountPointers<type>::size -= size;
  //     Lock::MemUsed -= size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;

  //     uint* clearsize = ((uint*)(in)) - 1;
  //     *clearsize = 0;

  //     // Создаем временный указатель для безопасного удаления
  //     type* temp = in;

  //     for (int i = 0; i < size; ++i) {
  //       rg_cout << "in[" << i << "] is cleared\n";

  //       // Вызываем деструктор для каждого элемента
  //       if constexpr (std::is_class<std::decay_t<decltype(temp[i])>>::value) {
  //         temp[i].~type(); // Вызов деструктора
  //       }
  //     }

  //     // Освобождаем память
  //     free(s_getraw(temp));
  //     in = nullptr;
  //   } else {
  //     RG_Debug::addl(RG_LOG_WARNING, "Memory Deallocation is failed, array is not RG type");
  //     free(in);
  //     in = nullptr;
  //   }
  // }
  template <typename type>
  typename std::enable_if<!std::is_class<type>::value, void>::type
    s_delete(type*& in) {
    if (in == nullptr)return;
    if (s_memtest(in)) {
      const uint& size = s_get_size(in);

      Lock::CountPointers<type>::size -= size;
      Lock::MemUsed -= size * sizeof(type) + sizeof(uint) + sizeof(char) * 2;
      RG_Debug::addl(RG_LOG_MEM, "Memory has been cleared: '" + to_string(size * sizeof(type) + sizeof(uint) + sizeof(char) * 2) + "' bytes");


      uint* clearsize = ((uint*)(in)) - 1;
      *clearsize = 0;
      free(s_getraw(in));
      in = nullptr;
    } else {
      RG_Debug::addl(RG_LOG_CRITICAL, "Memory Deallocation is failed, array is not RG type");
    }

  }
  template<typename T>
  decltype(auto) s_move(T& obj) {
    return (T&&)obj;
  }

  template<class type>
  inline void s_resize(type*& p, to_rvalue(int) newsize) {
    if (newsize > 0) {
      if (p != nullptr) {
        if (!s_memtest(p)) { RG_Debug::addl(RG_LOG_ERROR, "Memory Resize is failed, array is not RG type"); return; };
        int size = s_get_size(p);
        if (size != newsize) {
          type* out = s_new<type>(newsize);
          for (int i = 0; i < rg_min(size, newsize); i++) {
            //out[i] = p[i];
            out[i] = std::move(p[i]);
            // out[i] = p[i];
          }
          s_delete<type>(p);
          p = out;
          return;
        } else return;
      } else {
        //p = new type[newsize];
        p = s_new<type>(newsize);

        return;
      }
    } else { s_delete(p); return; }//delete[] p;p = nullptr;size = 0;return;};

  }
  template<class type>
  inline void s_renew(type*& p, to_rvalue(int) newsize) {
    if (newsize > 0) {
      if (p != nullptr) {
        if (!s_memtest(p)) { RG_Debug::addl(RG_LOG_ERROR, "Memory Renew is failed, array is not RG type"); return; };
        int size = s_get_size(p);
        if (size != newsize) {
          s_delete<type>(p);
          p = s_new<type>(newsize);
        }
      } else {
        p = s_new<type>(newsize);
      }
    } else { s_delete(p); return; }
  }






  template<class type>
  int s_erase(type*& p, int arrsize, int pos, int size) {// p - начала массива, arrsize - размер массива, pos - начала удаления, size - количество элементов для удаления
    RG_Debug::addl(RG_LOG_WARNING, "function s_erase(type*& p, int arrsize, int pos, int size) is deprecated. Please refer to the documentation");
    if (size == 0)return arrsize;
    int eracesize = size;
    int eracepos = pos;
    if (pos + size > arrsize) { RG_Debug::addl(RG_LOG_ERROR, "s_erase, size+pos is greater than the size of the passed array, erase pos = '" + to_string(pos) + "', erase size = '" + to_string(size) + "', array size = '" + to_string(arrsize) + "'"); }
    if (pos > arrsize) { RG_Debug::addl(RG_LOG_CRITICAL, "s_erase, pos is greater than the size of the passed array, erase pos = '" + to_string(pos) + "',array size = '" + to_string(arrsize) + "'"); }
    if (arrsize <= 0)RG_Debug::addl(RG_LOG_CRITICAL, "s_erase, array size less than or equal to 0, array size = " + to_string(arrsize) + "'");
    if (pos < 0)eracepos = arrsize + pos;
    if (size < 0) {
      if (size + pos <= 0)RG_Debug::addl(RG_LOG_CRITICAL, "I'm tired of writing errors, but here it's supposedly position + cleanup size is less than zero, understand it as you want. And i want to sleep.\n");
    }
    if (pos + size > arrsize)eracesize = arrsize - pos;
    if (arrsize - size <= 0) { RG_Debug::addl(RG_LOG_DEBUG, "s_erase, array size less than or equal to 0"); s_delete(p); return 0; }
    type* a = s_new<type>(arrsize - size);//new type[arrsize-size];
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


  template<class type>
  int s_erase_new(type*& p, int pos, int size) {// p - начала массива, arrsize - размер массива, pos - начала удаления, size - количество элементов для удаления
    RG_Debug::addl(RG_LOG_WARNING, "function s_erase(type*& p, int arrsize, int pos, int size) is deprecated. Please refer to the documentation");
    if (!s_memtest(p)) { RG_Debug::addl(RG_LOG_ERROR, "s_erase, array is not of type RG, 'size' 0 returned"); return 0; }
    uint arrsize = s_get_size(p);
    if (size == 0)return arrsize;
    int eracesize = size;
    int eracepos = pos;
    if (pos + size > arrsize) { RG_Debug::addl(RG_LOG_ERROR, "s_erase, size+pos is greater than the size of the passed array, erase pos = '" + to_string(pos) + "', erase size = '" + to_string(size) + "', array size = '" + to_string(arrsize) + "'"); }
    if (pos > arrsize) { RG_Debug::addl(RG_LOG_CRITICAL, "s_erase, pos is greater than the size of the passed array, erase pos = '" + to_string(pos) + "',array size = '" + to_string(arrsize) + "'"); }
    if (arrsize <= 0)RG_Debug::addl(RG_LOG_CRITICAL, "s_erase, array size less than or equal to 0, array size = " + to_string(arrsize) + "'");
    if (pos < 0)eracepos = arrsize + pos;
    if (size < 0) {
      if (size + pos <= 0)RG_Debug::addl(RG_LOG_CRITICAL, "I'm tired of writing errors, but here it's supposedly position + cleanup size is less than zero, understand it as you want. And i want to sleep.\n");
    }
    if (pos + size > arrsize)eracesize = arrsize - pos;
    if (arrsize - size <= 0) { RG_Debug::addl(RG_LOG_DEBUG, "s_erase, array size less than or equal to 0"); s_delete(p); return 0; }
    type* a = s_new<type>(arrsize - size);//new type[arrsize-size];
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




  template<class type>
  int Get_Count_Pointers() {
    return Lock::CountPointers<type>::count;
  }
  template<class type>
  RG_Array<type*> Get_All_Pointers() {
    RG_Array<type*> out(Lock::CountPointers<type>::count);
    long long contin = Lock::CountPointers<type>::min_pointer;
    for (int i = 0; i < Lock::CountPointers<type>::count; i++) {
      for (long long j = contin; j < Lock::CountPointers<type>::max_pointer; j++) {
        if (s_memtest((type*)j)) { contin = j + 1; out[i] = (type*)j; break; }
      }
    }
    return out;
  }

};

