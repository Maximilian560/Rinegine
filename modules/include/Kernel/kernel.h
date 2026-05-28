#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/kernel"
namespace Rinegine {
  namespace Kernel {
    // [Flags namespace for work with flags]
    namespace Flags {
      template <class T1, class T2>
      concept FlagTypeCompatible = requires(T1 val, T2 flag) {
        { val |= static_cast<T1>(flag) };
        { val &= ~static_cast<T1>(flag) };
        { (val & static_cast<T1>(flag)) != 0 };
      };
      // [2 args]
      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr void set(T1& val, T2 flag) { val |= static_cast<T1>(flag); }

      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr bool has(T1 val, T2 flag) { return (val & static_cast<T1>(flag)) != 0; }

      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr void clear(T1& val, T2 flag) { val &= ~static_cast<T1>(flag); }
    }
    // [Arrays with main arguments]
    extern std::vector<std::string> AMainArguments;  //TODO remove vector, set RG::Array!
    extern std::vector<std::wstring> WMainArguments; //TODO remove vector, set RG::Array!

    //
    template <class type1, class type2> struct MapData;
    //* types
    template <class type> class Matrix;
    template <class type> class Array;
    //* vars
    extern std::string AMainFolder;
    extern std::wstring WMainFolder;
    extern rg_string MainFolder;
    extern uint8_t RG_D_W_L;
    // typedef void_func  void(*)(void)
#ifndef RinegineLib
    int rg_main();
    int InterPoint(int, char**, int (*)() = rg_main);    // [done]
    int InterPoint(int, wchar_t**, int (*)() = rg_main); // [done]
#endif
    void init();                               // [todo]

    namespace Lock { // LOCK
      // friend class Kernel;

      struct LogVars;
      extern LogVars _vars;

      // public:
      void* s_new(const size_t&); // [done,stub]
      void* s_fast_new(const size_t& size); // [done,stub]
      uint s_delete(void*);                      // [done,stub]
      void s_fast_delete(void*);                 // [done,stub]
      // void s_depage(void* addr, size_t count); 
      bool s_rawmemtest(const char*);
      // template <class type> bool s_memtest(type *);
      int s_memtest(const void*);

      size_t s_get_size(const void*);
      size_t s_get_typesize(const void*);

      // template <class type> char s_print(type *);
        // void* s_page(size_t count = 1, void* addr = nullptr,
          // int prot = PROT_READ | PROT_WRITE,
          // int flags = MAP_PRIVATE | MAP_ANONYMOUS, int fd = -1,
          // off_t offset = 0); //[exp]
        // char s_print(void *, size_t = 1);

      void addl(Log::Types = Log::DEBUG, std::string = "NULL", bool = 1,
        std::string = "NULL", int = -1); // [done]
      void addl(Log::Types = Log::DEBUG, std::wstring = L"NULL", bool = 1,
        std::wstring = L"NULL", int = -1); // [done]

      template <class type> struct CountPointers;
    }
    // code


    std::wstring to_stringw(const std::string&);  // [done]
    std::wstring to_stringw(const std::wstring&); // [done]
    std::string to_stringa(const std::string&);   // [done]
    std::string to_stringa(const std::wstring&);  // [done]

    rg_string
      to_string(const std::string
        &); // [outdate], may do some bug. In fact - outdate
    rg_string
      to_string(const std::wstring
        &); // [outdate], may do some bug. In fact - outdate
    //!!! ↓outdate soon↓ !!!
    template <class type> struct POINT2D { // [done]
      type x = type(), y = type();
      POINT2D() {}
      POINT2D(type x_, type y_) : x(x_), y(y_) {}
      POINT2D<type> operator+(POINT2D<type> p) {
        return Kernel::POINT2D<type>(x + p.x, y + p.y);
      } // [done]
      POINT2D<type> operator-(POINT2D<type> p) {
        return Kernel::POINT2D<type>(x + -p.x, y - p.y);
      } // [done]
      POINT2D<type>& operator+=(POINT2D<type> p) {
        x += p.x;
        y += p.y;
        return *this;
      } // [done]
      POINT2D<type>& operator-=(POINT2D<type> p) {
        x -= p.x;
        y -= p.y;
        return *this;
      } // [done]
      bool operator==(POINT2D<type> p) {
        if (x == p.x && y == p.y)
          return true;
        return false;
      }
      bool operator>=(POINT2D<type> p) {
        if (x >= p.x && y >= p.y)
          return true;
        return false;
      }
      bool operator<=(POINT2D<type> p) {
        if (x <= p.x && y <= p.y)
          return true;
        return false;
      }
      bool operator>(POINT2D<type> p) {
        if (x > p.x && y > p.y)
          return true;
        return false;
      }
      bool operator<(POINT2D<type> p) {
        if (x < p.x && y < p.y)
          return true;
        return false;
      }
      type& operator[](uint i) { return (&x)[i % 2]; }
    };

    template <class type> struct POINT3D { // [todo]
      type x = type(), y = type(), z = type();
      bool operator==(POINT3D<type>);
      bool operator>=(POINT3D<type>);
      bool operator<=(POINT3D<type>);
      bool operator>(POINT3D<type>);
      bool operator<(POINT3D<type>);
      type& operator=(POINT2D<type>);
      type& operator[](uint);
    };
    template <class type> struct COLOR3D { // [todo]
      type r = type(), g = type(), b = type();
      bool operator==(COLOR3D<type>);
      bool operator>=(COLOR3D<type>);
      bool operator<=(COLOR3D<type>);
      bool operator>(COLOR3D<type>);
      bool operator<(COLOR3D<type>);
      type& operator=(POINT2D<type>);
      type& operator[](uint);
    };
    template <typename type> struct COLOR4D { // [todo]
      type r = type(), g = type(), b = type(), a = type();
      bool operator==(const COLOR4D<type>&);
      bool operator!=(const COLOR4D<type>&);
    };
    //!!! ↑outdate soon↑ !!!
    //!!! use vec types instead!!!
    //!!! as example vec3<int> instead POINT3<int> and COLOR3<int>!!!

    int KeyIs(int, bool);      // [done]
    int KeyIsPress(int, bool); // [done]
    int TestKeyIs(int, bool);  // [done]

    class SysTime {
      struct SysTimeVar;
      static SysTimeVar _vars;

    public:
      static void update();
      // W
      static std::wstring YearW();         // [done]
      static std::wstring MonthW();        // [done]
      static std::wstring DayOfWeekW();    // [done]
      static std::wstring DayW();          // [done]
      static std::wstring HourW();         // [done]
      static std::wstring MinuteW();       // [done]
      static std::wstring SecondW();       // [done]
      static std::wstring MillisecondsW(); // [done]
      // A
      static std::string YearA();         // [done]
      static std::string MonthA();        // [done]
      static std::string DayOfWeekA();    // [done]
      static std::string DayA();          // [done]
      static std::string HourA();         // [done]
      static std::string MinuteA();       // [done]
      static std::string SecondA();       // [done]
      static std::string MillisecondsA(); // [done]
      //
      static rg_string
        Year(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Month(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        DayOfWeek(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Day(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Hour(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Minute(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Second(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Milliseconds(); // [outdate], may do some bug. In fact - outdate
    };
    // #ifdef RG_WIN
    //     void SetColorTCMD(WORD); // [done,exp]
    // #else
    void SetColorConsole(WORD); // [done,exp]
    // #ifdef RG_WIN
#ifdef __WIN32
    inline void SetColorTCMD(WORD col) { // [done,exp]
      static HANDLE HandleMainConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(HandleMainConsole, col);
    }
#endif
    // #ifdef __WIN32 && !defined(RinegineLib)

    // #endif
    void SetTrueColorConsole(
      COLOR3D<uint8_t>,
      Rinegine::CONSOLE_COLOR = Rinegine::CONSOLE_COLOR::C_TEXT);      // [done,exp]
    // #endif
    bool isSubstringAt(const char&, const std::string&);        // [done]
    bool isSubstringAt(const wchar_t&, const std::wstring&);    // [done]
    bool isSubstringAt(const std::string&, const std::string&); // [done]
    bool isSubstringAt(const std::string&,
      const std::wstring&); // []
    void Open(std::string);                   // [done]
    void Open(std::wstring);                  // [done,exp]

    std::string tolowstr(std::string); // [done]
    /// @brief Converts the string to lowercase. Does not work with unicode!!!
    /// Only Latin
    /// @param wstring any case
    /// @return `wstring`  lowercase
    std::wstring tolowwstr(std::wstring); // [redo,exp]

    //* decode
    char* itoa(int, int = 10, char* = nullptr);            // [done,todo]
    // std::string itos(long long int, long long int = 10);   // [done]
    std::string itos(size_t, size_t = 10);                 // [done]
    std::wstring itows(long long int, long long int = 10); // [done]
    std::wstring itows(size_t, size_t = 10);               // [done]
    //*folder
    bool isDirectory(std::string);        // [done]
    bool isDirectory(std::wstring);       // [done]
    bool CreateFolder(std::string path);  // [done]
    bool CreateFolder(std::wstring path); // [done]

    //*debug
    class Debug {             // [done]
      struct DebugVars;       // [done]
      // static DebugVars _vars; // [done]

    public:
      Debug();                                // [done]
      Debug(rg_string);                       // [done]
      static void init();                     // [done]
      static void init(rg_string);            // [done]
      static void open_log_after_error(bool); // [done]
      static void open_shell(bool); // [done] (same as open_log_after_error)
      static rg_string log_path();  // [done]
      static void update();         // [done]
      static void stop() __attribute__((noreturn)); // [done]
      static void no_close();                       // [done]
      static DebugVars& DebugVars_safe_get();   //[done]
      ~Debug();                                     // [done]

      //*special add/addl for dif os
      static void add(rg_string = "NULL", Log::Types = Log::DEBUG, bool = true,
        rg_string = "NULL", int = -1); // [done]
      template <class string1, class string2>
      static void add(string1, Log::Types = Log::DEBUG, bool = true,
        string2 = string2(), int = 0); // [done]
      static void addl(Log::Types = Log::DEBUG, rg_string = RG_L "empty",
        bool = true, rg_string = rg_to_string(RG_HERE_FILE_NAME),
        int = -1); // [done]
      //*other add/addl
      template <class string1, class string2>
      static void addl(Log::Types = Log::DEBUG, string1 = string1(), bool = true,
        string2 = string2(), int = -1); // [done]

    }; // [done]
    // std::wstring GetLastErrorStringW(DWORD);//todo... i guess
    // std::string GetLastErrorStringA(DWORD);//todo... i guess
    rg_string GetLastErrorString(DWORD); // [done]

    // ALLOC

    // template <class type> static type *s_new(int, type &&);

    // template <class type> type *s_new(int, const type &);
    template <class type> type* s_new(size_t s) { // [done]
      if (!std::is_default_constructible<type>::value) {
        RG_LOG_LOCK_ERROR("Type must be default constructible");
        return nullptr;
      }
      // type* t = (type*)Lock::s_new(s, sizeof(type));
      type* t = (type*)Lock::s_new(s * sizeof(type));
      return t;
    }

    template <class type> type* s_new(size_t s, type&& in) { // [done]
      if (!std::is_default_constructible<type>::value) {
        RG_LOG_LOCK_ERROR("Type must be default constructible");
        return nullptr;
      }
      type* t = (type*)Lock::s_new(s * sizeof(type));
      for (size_t i = 0; i < s; i++)
        new (t + i) type(std::move(in));
      // new (t + i) type(std::forward<type>(in));
      return t;
    }

    template <class type> type* s_new(size_t s, const type& in) { // [done]
      if (!std::is_default_constructible<type>::value) {
        RG_LOG_LOCK_ERROR("Type must be default constructible");
        return nullptr;
      }
      type* t = (type*)Lock::s_new(s * sizeof(type));
      for (size_t i = 0; i < s; i++)
        t[i] = in;
      return t;
    }

    template <class type, class gen>
    std::enable_if_t<std::is_invocable_r_v<type, gen>, type*>
      s_new(size_t s, gen&& in) { // [done]
      type* t = (type*)Lock::s_new(s * sizeof(type));
      for (size_t i = 0; i < s; i++)
        new (t + i) type(in());
      return t;
    }
    // new fast
    template <class type> type* s_fast_new(size_t s) { // [done]
      type* t = (type*)Lock::s_fast_new(s * sizeof(type));
      return t;
    }

    template <class type>
    type* s_fast_new(size_t s, type&& in) { // [done]
      type* t = (type*)Lock::s_fast_new(s * sizeof(type));
      for (size_t i = 0; i < s; i++)
        new (t + i) type(std::forward<type>(in));
      return t;
    }
    template <class type>
    type* s_fast_new(size_t s, const type& in) { // [done]
      type* t = (type*)Lock::s_fast_new(s * sizeof(type));
      for (size_t i = 0; i < s; i++)
        new (t + i) type(in);
      return t;
    }

    template <class type, class gen>
    std::enable_if_t<std::is_invocable_r_v<type, gen>, type*>
      s_fast_new(size_t s, gen&& in) { // [done]
      type* t = (type*)Lock::s_fast_new(s * sizeof(type));
      for (size_t i = 0; i < s; i++)
        new (t + i) type(in());
      return t;
    }
    // void *s_fast_new(size_t s, int typesize) { return
    // Lock::s_fast_new(s, typesize); }

    size_t s_get_typesize(void*);

    /**
     * @brief
     *
     * @brief Allocates memory to pages, wrapper over mmap
     * @param count
     *   The number of pages to allocate.
     *   Set on 1.
     * @param addr
     *   Suggested starting address for the mapping.
     *   Set on nullptr.
     * @param prot
     *   Memory protection flags for the mapped region .
     *   Set on PROT_READ | PROT_WRITE.
     * @param flags
     *   Controls the type and behavior of the mapping.
     *   Set on MAP_PRIVATE | MAP_ANONYMOUS.
     * @param fd
     *   File descriptor of the file to map.
     *   Set on -1.
     * @param offset
     *   Offset within the file where mapping starts.
     *   Set on 0 .
     * @return
     *    Returns a pointer to the page on success, or MAP_FAILED if allocation
     *    fails.
     */

     /**
      * @brief Deallocate the memory allocated by s_page
      *
      * @param addr
      * Address of the page that needs to be deallocate
      *
      * @param count
      * Count of page,
      *
      */


    char s_print(to_rrvalue(char*));

    char s_print(to_rrvalue(wchar_t*));

    char s_print(to_rrvalue(std::string*));

    char s_print(to_rrvalue(std::wstring*));

    char s_print(std::string*);

    char s_print(std::wstring*);

    template <class type> char s_print(type* in) {
      size_t temp_size = (size_t)Kernel::Lock::s_get_size(in);
      for (size_t i = 0; i < temp_size; i++) {
        if (i != temp_size - 1)
          rg_cout << in[i] << ", ";
        else
          rg_cout << in[i];
      }
      return '\0';
    }

    template <class ForwardIt, class Generator>
    void s_fill_func(ForwardIt first, ForwardIt last,
      Generator g) {
      for (; first != last; ++first)
        *first = g();
    }

    template <class ForwardIt, class Generator>
    void s_fill(ForwardIt first, ForwardIt last, Generator g) {
      for (; first != last; ++first)
        *first = g;
    }
    template <class type, class gen>
    void s_fill_func(type arr, int size, gen g) {
      for (int i = 0; i < size; i++) {
        arr[i] = g();
      }
    }
    template <class type, class gen>
    void s_fill(type arr, int size, gen g) {
      for (int i = 0; i < size; i++) {
        arr[i] = g;
      }
    }

    char* s_getraw(void* in);

    template <typename type>
    typename std::enable_if<std::is_class<type>::value,
      void>::type s_delete(type*& in) {
      if (in == nullptr)
        return;
      if (!Lock::s_memtest(in)) {
        RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
        return;
      }
      const unsigned long long& size = Rinegine::Kernel::Lock::s_get_size(in);
      for (int i = 0; i < size; i++) {
        in[i].~type();
      }
      Lock::s_delete(in);
    }

    template <typename type>
    typename std::enable_if<!std::is_class<type>::value,
      void>::type s_delete(type*& in) {
      if (in == nullptr)
        return;
      if (!Lock::s_memtest(in)) {
        RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
        return;
      }
      Lock::s_delete(in);
    }

    template <typename type>
    typename std::enable_if<std::is_class<type>::value,
      void>::type s_fast_delete(type*
        & in) {
      if (in == nullptr)
        return;
      if (!Lock::s_memtest(in)) {
        RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
        return;
      }
      const unsigned long long& size = Rinegine::Kernel::Lock::s_get_size(in);
      for (int i = 0; i < size; i++) {
        in[i].~type();
      }
      Lock::s_fast_delete(in);
    }

    template <typename type>
    typename std::enable_if<!std::is_class<type>::value,
      void>::type s_fast_delete(type*
        & in) {
      if (in == nullptr)
        return;
      if (!Lock::s_memtest(in)) {
        RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
        return;
      }
      Lock::s_fast_delete(in);
    }

    template <typename T> decltype(auto) s_move(T& obj) {
      return (T&&)obj;
    }

    // template <class type> void s_resize(type *&, to_rvalue(int));
    template <class type>
    void s_resize(type*& in, to_rvalue(int) n_size) { // 
      if (n_size <= 0) {
        s_delete(in);
        return;
      }
      if (in == nullptr) {
        in = s_new<type>(n_size);
        return;
      }
      if (!s_memtest(in)) {
        RG_LOG_LOCK_ERROR("Memory Resize is failed, array is not RG type");
        return;
      }
      int size = s_get_size(in);
      if (size == n_size)
        return;
      type* temp = s_new<type>(n_size);
      for (int i = 0; i < rg_min(size, n_size); i++) {
        temp[i] = std::move(in[i]);
      }
      s_delete<type>(in);
      in = temp;
    }

    //* raw pointer
    struct Raw_Pointer { // [exp]
      void* ptr = nullptr;
      size_t typesize = 0;
      size_t arrsize = 0;
      // init test
      bool is_init() const;

      // POINTER GET
      void* get() const;

      // CONSTRUCTORs
      Raw_Pointer();
      Raw_Pointer(void* in);
      // В Raw_Pointer можно добавить:
      Raw_Pointer(const Raw_Pointer&) = default;
      Raw_Pointer& operator=(const Raw_Pointer&) = default;
      Raw_Pointer(Raw_Pointer&&) = default;
      Raw_Pointer& operator=(Raw_Pointer&&) = default;

      // INITs
      void init();
      void init(void* in);
      // OPERATORs
      Raw_Pointer& operator=(void* in);
      void* operator->();

      void clear();
      operator void* () const;
      ~Raw_Pointer();
    };
    //* pointer
    template <typename type> class Pointer { // [exp]
      Raw_Pointer _ptr;

    public:
      bool is_init() const { return _ptr.is_init(); }
      type* get() const { return (type*)_ptr.get(); }
      Pointer() : _ptr() {}
      Pointer(const type& in) : _ptr(s_new(1, in)) {}
      // Pointer(Pointer&& in) noexcept : _ptr(s_new(1, in)) {}
      Pointer(Pointer&& in) noexcept : _ptr(in._ptr) {
        in._ptr.init(); // или in._ptr.ptr = nullptr, чтобы избежать двойного освобождения
      }

      // Pointer(const Pointer<type>& in) : _ptr(in.get()) {}
      Pointer(const Pointer<type>& in) : _ptr(in._ptr) {}
      Pointer(type* in) : _ptr(in) {}
      void init() {
        if (is_init())
          clear();
        _ptr.init(s_new<type>(1));
      }
      void init(type& in) { _ptr.init(s_new(1, in)); }
      void init(const type& in) { _ptr.init(s_new(1, in)); }
      void init(type in) { _ptr.init(s_new(1, in)); }
      void init(type* in) { _ptr.init(in); }
      Pointer& operator=(const type& in) {
        _ptr.init(s_new(1, in));
        return *this;
      }
      // Pointer& operator=(Pointer&& in) noexcept {
      //   _ptr.init(s_new(1, in));
      //   return *this;
      // }
      Pointer& operator=(Pointer&& in) noexcept {
        if (this != &in) {
          _ptr.clear();      // освободить старое
          _ptr = in._ptr;    // забрать владение
          in._ptr.init();    // обнулить источник
        }
        return *this;
      }
      // Pointer& operator=(const Pointer& in) {
      //   _ptr.init(s_new(1, in));
      //   return *this;
      // }
      Pointer& operator=(const Pointer& in) {
        if (this != &in) {
          _ptr = in._ptr;  // ← копировать ВЕСЬ Raw_Pointer
        }
        return *this;
      }
      Pointer& operator=(type* in) {
        _ptr.init(in);
        return *this;
      }
      inline type* operator->() { return (type*)_ptr.get(); }
      void clear() { _ptr.clear(); }
      operator type* () const { return (type*)_ptr.get(); }
    };
    //*array
    /*
    class RawArray {
      template <class type>
      friend class Array;
      DATA_OUT* ptr = nullptr;
      inline void* get() const { return (void*)(ptr + 1); }
    public:
      RawArray() = default;
      RawArray(size_t);
      RawArray(const RawArray&);
      RawArray& operator=(const RawArray&);
      void resize(const size_t& size);
      size_t size() const;
      void clear();
      ~RawArray();
    };
    template <class type>
    class Array :protected RawArray {

    public:
      inline Array() = default;
      inline Array(Array&&) = default;
      inline Array(const Array& in) {
        RawArray::resize(in.size());
        for (size_t i = 0; i < in.size(); i++)
          ((type*)get())[i] = ((type*)in.get())[i];
      };
      inline Array(const size_t& size) { resize(size); }
      // inline Array(const size_t& size, type&& in) { resize(size); for (size_t i = 0; i < size; i++) ((type*)get())[i] = std::move(in); }
      inline Array(const size_t& size, const type& in) { resize(size); for (size_t i = 0; i < size; i++) ((type*)get())[i] = in; }
      inline Array(type&& in) { resize(1); ((type*)get())[0] = std::move(in); }
      inline Array(const type& in) { resize(1); ((type*)get())[0] = in; }


      inline type& operator[](long i) const {
        if (ptr == nullptr)
          RG_LOG_LOCK_CRITICAL("Array not initialized");
        if (i >= ptr->size)
          RG_LOG_LOCK_CRITICAL("Index out of range");
        if (i < 0)
          return *(type*)(((char*)get())[ptr->size + i]);
        return ((type*)get())[i];
      }
      inline type* back() const { if (ptr == nullptr) RG_LOG_LOCK_CRITICAL("Array not initialized"); return ((type*)get()) + (size() - 1); }

      inline type* begin() const { return ((type*)ptr); }
      inline type* end() const { if (ptr == nullptr) RG_LOG_LOCK_CRITICAL("Array not initialized"); return ((type*)get()) + size(); }
      inline type* data() {
        return (type*)ptr;
      }
      inline void resize(const size_t& size) {
        RawArray::resize(size * sizeof(type));
      }
      // inline void push_back(type&& in) {
      //   if (ptr == nullptr) {
      //     resize(1);
      //     ((type*)get())[0] = std::move(in);
      //   }
      //   else {
      //     resize(ptr->size + sizeof(type));
      //     ((type*)get())[ptr->size - 1] = std::move(in);
      //   }
      // }
      inline void push_back(const type& in) {
        if (ptr == nullptr) {
          resize(1);
          ((type*)get())[0] = std::move(in);
        }
        else {
          resize(ptr->size + sizeof(type));
          ((type*)get())[ptr->size - 1] = in;
        }
      }
      inline size_t size() const { if (ptr == nullptr)return 0; else return ptr->size / sizeof(type); }
      inline void clear() {
        Rinegine::Kernel::s_delete(ptr);
        ptr = nullptr;
      }
      inline ~Array() { clear(); }
    };
    / *template <class type> class Array {
      struct ArrayVars;
      ArrayVars _vars;

    public:
      Array();
      Array(Array&&) noexcept;
      Array(to_rvalue(Array<type>));
      Array(int, to_rvalue(type));
      Array(int, type*);
      Array(int);
      Array(to_rvalue(std::initializer_list<type>));
      template <class type2> Array(to_rvalue(std::initializer_list<type2>));
      explicit Array(to_rrvalue(type*));
      void fastpop();
      void fastpush();
      void fastpush(to_rvalue(type));
      void fastpush(to_rvalue(Array<type>));
      void fastpush(to_rvalue(std::initializer_list<type>));
      void fastpush(to_rvalue(type*));
      void fastpush(type&&) noexcept;
      void fastpush(Array<type>&&);
      template <typename... Args> void fastemplace(Args &&...) noexcept;
      void set_push_reserve(to_rvalue(uint));
      void init(int);
      void init(to_rvalue(int), to_rvalue(type));
      void init(to_rvalue(type*));
      void init(to_rvalue(uint), to_rrvalue(type*));
      void init(to_rvalue(std::initializer_list<type>));
      template <class type2> void init(to_rvalue(std::initializer_list<type2>));
      void init(to_rvalue(Array<type>));
      void resize(int);
      void fast_clear();
      void reserve(to_rvalue(int));
      void reserve_fill();
      void reinit(to_rvalue(int));
      void fill(type(*)());
      void fillfull(to_rvalue(uint), to_rvalue(type));
      void fill(type);
      template <class type2> void fill(type2);
      void fill(type*);
      void push_back();
      void push_back(to_rvalue(type));
      void push_back(to_rvalue(Array<type>));
      void push_back(to_rvalue(std::initializer_list<type>));
      void push_back(to_rvalue(type*));
      template <typename... Args> void emplace_back(Args &&...);
      type& operator[](to_rvalue(int)) const;
      type& operator[](to_rvalue(uint)) const;
      Array<type> operator*(to_rvalue(Matrix<type>)) const;
      Array<type> operator*(to_rvalue(type)) const;
      Array<type> operator-(to_rvalue(Array<type>)) const;
      Array<type> operator+(to_rvalue(Array<type>)) const;
      Array<type> operator%(to_rvalue(Array<type>)) const;
      Array<type> operator*(to_rvalue(Array<type>)) const;
      template <class em> void operator=(to_rvalue(em));
      void operator=(to_rvalue(type));
      void operator=(to_rvalue(Array<type>));
      void operator=(const std::initializer_list<type>*);
      void operator=(const char*);
      void copy(to_rvalue(Array<type>));
      void operator-=(to_rvalue(Array<type>));
      void operator+=(to_rvalue(Array<type>));
      Matrix<type> transpose() const;
      type* get() const;
      type* data() const;
      type* get_array() const;
      type* get_arr() const;
      type& get(to_rvalue(int)) const;
      type& get(to_rvalue(uint)) const;
      type* begin() const;
      type* end() const;
      type* back() const;
      uint size() const;
      uint true_size() const;
      void print() const;
      rg_string get_string();
      type sum() const;
      void fill_range_random(to_rvalue(type), to_rvalue(type));
      bool empty() const;
      void movefill(to_rvalue(uint), type*);
      void clear();
      void fastclear();
      ~Array();
    };*/
    // matrix
    template <typename type> class Matrix {
      struct MatrixVars;
      MatrixVars _vars;

    public:
      void init(to_rvalue(Array<type>));
      void init(to_rvalue(std::initializer_list<std::initializer_list<type>>));
      uint rows() const;
      uint cols() const;
      void init(uint, uint);
      void init(to_rvalue(uint), to_rvalue(uint), type*);
      void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(type));
      void init(to_rvalue(Matrix<type>));
      Matrix();
      Matrix(uint, uint);
      Matrix(to_rvalue(uint), to_rvalue(uint), to_rvalue(type));
      void
        operator=(to_rvalue(std::initializer_list<std::initializer_list<type>>));
      void operator=(to_rvalue(Array<type>));
      void operator=(to_rvalue(Matrix<type>));
      void resize(to_rvalue(uint));
      void resize(to_rvalue(uint), to_rvalue(uint));
      void resize(to_rvalue(POINT2D<uint>));
      void fill(to_rvalue(Matrix<type>));
      void fill(to_rvalue(uint), to_rvalue(uint), type*);
      void fill(to_rvalue(Array<type>));
      void fill(to_rvalue(std::initializer_list<std::initializer_list<type>>));
      template <class type2>
      void fill(to_rvalue(std::initializer_list<std::initializer_list<type2>>));
      void movefill(to_rvalue(uint), to_rvalue(uint), type*);
      void fill(to_rvalue(type));
      void fill(to_rvalue(uint), to_rvalue(uint), to_rvalue(type));
      void randomBoolFill(to_rvalue(double), to_rvalue(double));
      void randomBoolAddFill(to_rvalue(double), to_rvalue(double));
      void randomAddFill(to_rvalue(double), to_rvalue(double));
      void random_fill(to_rvalue(double));
      void noise_fill(to_rvalue(int));
      void noise_dbool_fill(to_rvalue(int));
      void fill_range_random(to_rvalue(type), to_rvalue(type));
      void scale(to_rvalue(uint));
      void smoothScale(to_rvalue(int));
      Matrix<type>& transpose();
      type& get_t(const uint&, const uint&) const;
      void update_transpose();
      type* operator[](const uint&) const;
      type& operator()(const uint&, const uint&) const;
      type& operator()(to_rvalue(POINT2D<uint>)) const;
      type& operator()(to_rvalue(POINT2D<int>)) const;
      type& operator[](to_rvalue(POINT2D<uint>)) const;
      type& operator[](to_rvalue(POINT2D<int>)) const;
      type& get(const uint&, const uint&) const;
      type& getyx(to_rvalue(uint), to_rvalue(uint)) const;
      type& get(to_rvalue(POINT2D<uint>)) const;
      type& get(to_rvalue(POINT2D<int>)) const;
      void print() const;
      std::string print_d() const;
      rg_ostrem& print(rg_ostrem&) const;
      operator type* ();
      type* get() const;
      type* data() const;
      type* get_mat() const;
      operator Array<type>& () const;
      bool empty() const;
      operator bool();
      uint size(to_rvalue(uint)) const;
      operator Array<type>() const;
      operator uint() const;
      POINT2D<uint> size() const;
      void clear();
      ~Matrix();
      void operator*=(const type*);
      void operator*=(const std::initializer_list<std::initializer_list<type>>&);
      template <class type2>
      void
        operator*=(const std::initializer_list<std::initializer_list<type2>>&);
      void operator*=(const Matrix<type>&);
      template <class type2> Matrix<type> operator*(const type2&) const;
      template <class type2>
      Matrix<type> operator%(to_rvalue(Matrix<type2>)) const;
      Matrix<type> operator*(const Matrix<type>&);
      Matrix<type> operator*(const Array<type>&) const;
      void operator+=(const Matrix<type>&);
      void operator-=(const Matrix<type>&);
      Matrix<type> operator+(const Matrix<type>&);
      Matrix<type> operator-(const Matrix<type>&);
      template <class tttt> void place(POINT2D<int>, Matrix<tttt>&);
    };
    template <class type, class type2>
    type SpecialMatMulti(Matrix<type>&, Matrix<type2>&, int, int);
    // [todo] Удалить
    template <class type, class type2>
    bool CountMatMinus(Matrix<type>&, Matrix<type2>&, int, int);
    //* 3D Matrix
    template <typename type> class RG_Matrix3D {
      struct Matrix3DVars;
      Matrix3DVars _vars;

    public:
      void init(to_rvalue(Array<type>));
      void init(to_rvalue(std::initializer_list<std::initializer_list<type>>));
      void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint));
      void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type*);
      void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint),
        to_rvalue(type));
      void init(to_rvalue(RG_Matrix3D<type>));
      RG_Matrix3D();
      RG_Matrix3D(to_rvalue(Array<type>));
      RG_Matrix3D(to_rvalue(RG_Matrix3D<type>));
      RG_Matrix3D(to_rvalue(std::initializer_list<std::initializer_list<type>>));
      RG_Matrix3D(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint));
      RG_Matrix3D(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type*);
      RG_Matrix3D(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint),
        to_rvalue(type));
      void
        operator=(to_rvalue(std::initializer_list<std::initializer_list<type>>));
      void operator=(to_rvalue(Array<type>));
      void operator=(to_rvalue(RG_Matrix3D<type>));
      void resize(to_rvalue(uint));
      void resize(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint));
      void resize(to_rvalue(POINT3D<uint>));
      void resize(to_rvalue(POINT3D<int>));
      void fill(to_rvalue(RG_Matrix3D<type>));
      void fill(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type*);
      void fill(to_rvalue(Array<type>));
      void fill(to_rvalue(std::initializer_list<
        std::initializer_list<std::initializer_list<type>>>));
      template <class type2>
      void fill(to_rvalue(std::initializer_list<
        std::initializer_list<std::initializer_list<type2>>>));
      void movefill(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type*);
      void fill(to_rvalue(type));
      void fill(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint),
        to_rvalue(type));
      void randomBoolFill(to_rvalue(double), to_rvalue(double));
      void randomBoolAddFill(to_rvalue(double), to_rvalue(double));
      void randomAddFill(to_rvalue(double), to_rvalue(double));
      void random_fill(to_rvalue(double));
      void noise_fill(to_rvalue(int));
      void noise_dbool_fill(to_rvalue(int));
      void fill_range_random(to_rvalue(type), to_rvalue(type) b);
      void scale(to_rvalue(uint));
      type& get(const uint&, const uint&, const uint&) const;
      type& getzyx(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint)) const;
      type& get(to_rvalue(POINT3D<uint>)) const;
      type& get(to_rvalue(POINT3D<int>)) const;
      void print() const;
      operator type* ();
      type* get() const;
      type* get_mat() const;
      operator Array<type>& () const;
      bool empty() const;
      operator bool();
      uint size(to_rvalue(uint)) const;
      operator Array<type>() const;
      operator uint() const;
      POINT3D<uint> size() const;
      void clear();
      ~RG_Matrix3D();
      template <class type2> RG_Matrix3D<type> operator*(const type2&) const;
      template <class type2>
      RG_Matrix3D<type> operator%(to_rvalue(RG_Matrix3D<type2>)) const;
      void operator+=(const RG_Matrix3D<type>&);
      void operator-=(const RG_Matrix3D<type>&);
      template <class tttt> void place(POINT3D<int>, RG_Matrix3D<tttt>&);
    };
    // map
    // class RawMap {
    //   template <class key, class value>
    //   friend class Map;
    //   RawArray keys;
    //   RawArray values;
    //   size_t count = 0;
    // public:
    //   RawMap() = default;
    //   RawMap(size_t size) : count(0) { init(size); }
    //   void init(size_t size) {
    //     resize(size);
    //   }
    //   void resize(size_t size) {
    //     keys.resize(size);
    //     values.resize(size);
    //   }
    //   ~RawMap() {
    //     keys.~RawArray();
    //     values.~RawArray();
    //   }
    // };
    // class RawMap {
    //   template<class key, class value>
    //   friend class Map;
    //   char* key = nullptr;
    //   char* value = nullptr;
    //   size_t count = 0;
    // public:
    //   RawMap() :key(nullptr), value(nullptr) {}
    //   void set_type_size(size_t key, size_t value);
    //   void resize(size_t size);
    //   void init(size_t key, size_t value,size_t size);
    //   ~RawMap();
    //   char* getkey(size_t i);
    //   char* getval(size_t i);
    // };
    // template<class Key, class Value>
    // class Map :protected RawMap {
    // public:
    //   Map() {
    //     init();
    //   }
    //   void init() {
    //     set_type_size(sizeof(Key), sizeof(Value));
    //   }
    //   void init(size_t count){
    //     set_type_size(sizeof(Key), sizeof(Value));
    //     resize(count);
    //   }
    //   Value& operator[](Key in){
    //     Value* out = nullptr;
    //     for(size_t i = 0; i < count; i++){
    //       if(RawMap::)
    //     }
    //   }

    // };
    // template <class type> class RG_Map {
    // public:
    //   RG_Map();
    //   RG_Map(uint size);
    //   RG_Map(std::string key, type val);
    //   RG_Map(MapData<std::string, type>);
    //   RG_Map(Array<MapData<std::string, type>>);
    //   RG_Map(std::initializer_list<MapData<std::string, type>>);
    //   void init(uint size);
    //   void init(std::string key, type val);
    //   void init(MapData<std::string, type>);
    //   void init(Array<MapData<std::string, type>>);
    //   void init(std::initializer_list<MapData<std::string, type>>);
    //   void fill(std::string key, type val);
    //   void fill(MapData<std::string, type>);
    //   void fill(uint size);
    //   void fill(Array<MapData<std::string, type>>);
    //   void fill(std::initializer_list<MapData<std::string, type>>);
    //   int findpos(std::string ii);
    //   type find(std::string ii);
    //   type find(int ii);
    //   type operator[](std::string i);
    //   void sort();
    //   MapData<std::string, type>& operator[](uint i);
    //   void push_back(MapData<std::string, type>);
    //   void resize(uint size);
    //   int size();
    //   MapData<std::string, type>* get_arr();
    //   Array<type>& get_rgarr();
    //   void clear();
    //   ~RG_Map();
    // };
    // template <class type> class RG_WMap {

    // public:
    //   RG_WMap();
    //   RG_WMap(uint size);
    //   RG_WMap(std::wstring key, type val);
    //   RG_WMap(MapData<std::wstring, type>);
    //   RG_WMap(Array<MapData<std::wstring, type>>);
    //   RG_WMap(std::initializer_list<MapData<std::wstring, type>>);
    //   void init(uint size);
    //   void init(std::wstring key, type val);
    //   void init(MapData<std::wstring, type>);
    //   void init(Array<MapData<std::wstring, type>>);
    //   void init(std::initializer_list<MapData<std::wstring, type>>);
    //   void fill(std::wstring key, type val);
    //   void fill(MapData<std::wstring, type>);
    //   void fill(uint size);
    //   void fill(Array<MapData<std::wstring, type>>);
    //   void fill(std::initializer_list<MapData<std::wstring, type>>);
    //   int findpos(std::wstring ii);
    //   type& find(std::wstring ii);
    //   type& find(int ii);
    //   MapData<std::wstring, type>& findstring(std::wstring ii);
    //   type& operator[](std::wstring i);
    //   MapData<std::wstring, type>& findchar(wchar_t in);
    //   void revsort();
    //   void sort();
    //   MapData<std::wstring, type>& operator[](uint i);
    //   void push_back(MapData<std::wstring, type>);
    //   void resize(uint size);
    //   int size();
    //   MapData<std::wstring, type>* get_arr();
    //   Array<type>& get_rgarr();
    //   void clear();
    //   ~RG_WMap();
    // };
    uint64_t wstring_to_seed(const std::wstring&);
    class RG_CRand {
    public:
      RG_CRand();
      RG_CRand(uint64_t);
      void init(uint64_t);
      bool is_init();
      uint64_t rand();
    };
    int set_seed();
    uint64_t RG_Rand();
    uint64_t Rand();
    double RandRange(double, double);
    // encode
    template <class type> class RG_List {
    public:
      operator Array<type>& ();
      int size();
      RG_List(std::initializer_list<type>);
      type operator[](int i);
    };
    struct RG_ENCODE_TYPE;
    struct RG_ENCODE_VALUE;
    class RG_ENCODE {
    public:
      static bool is_init();
      static wchar_t get_size(std::string);
      static int get_id(std::string);
      static RG_ENCODE_VALUE get(std::string);
    };
    // files
#ifdef RG_WIN
    std::wstring utf8_to_utf16(const std::string& str);
    std::string utf16_to_utf8(const std::wstring& wstr);
#endif
    std::string AFileLoad(std::string path);
    std::wstring WFileLoad(std::string path);
    std::wstring WFileLoad(std::wstring path);
    // #ifdef RG_UTF
        // template <class in_string> rg_string FileLoad(in_string path);
#ifdef RG_UTF
    template <class in_string>
    rg_string FileLoad(in_string path) {
      return WFileLoad(rg_to_stringa(path));
    }
#else
    template <class in_string>
    rg_string FileLoad(in_string path) {
      return AFileLoad(rg_to_stringa(path));
    }
#endif
    // #else
        // template <class in_string> rg_string FileLoad(in_string path);
    // #endif
    bool RG_IsFile(std::string path);
    std::string GetTypePath(std::string path);
#ifdef RG_WINos
    class FileFinder {
      HANDLE hFindFile;
      WIN32_FIND_DATA findFileData; // Используем объект, а не указатель
      bool _init = false;
      bool _eof = false;
    public:
      bool eof();
      WIN32_FIND_DATA* init(const rg_string& path);
      WIN32_FIND_DATA* next();
      void close();
      ~FileFinder();
    };
    class FileFinderA {
      HANDLE hFindFile;
      WIN32_FIND_DATAA findFileData; // Используем объект, а не указатель
      bool _init = false;
      bool _eof = false;
    public:
      bool eof();
      WIN32_FIND_DATAA* init(const std::string& path);
      WIN32_FIND_DATAA* next();
      void close();
      ~FileFinderA();
    };
    class FileFinderW {
      HANDLE hFindFile;
      WIN32_FIND_DATAW findFileData; // Используем объект, а не указатель
      bool _init = false;
      bool _eof = false;
    public:
      bool eof();
      WIN32_FIND_DATAW* init(const std::wstring& path);
      WIN32_FIND_DATAW* next();
      void close();
      ~FileFinderW();
  };
#endif
    // otherDef
    int RG_CMD(std::string, bool = true);
    // struct ConfigRunProgram;
    struct ConfigRunProgram {
      std::string path = "err";
      bool assinhrone = true;
      bool InItFol = false;
      bool otherCMD = false;
    };
#ifdef RG_WIN
    int RunProgram(ConfigRunProgram conf);
#elif defined(RG_Linux)
    int RunProgram(ConfigRunProgram conf);
#endif
    std::string RG_AGetMainFolder();
    std::wstring RG_WGetMainFolder();
#ifdef RG_UTF
    std::wstring RG_GetMainFolder();
#else
    std::string RG_GetMainFolder();
#endif
    template <class type> struct vec2 {
      void operator=(vec2<type> in);
      type& operator[](int i);
      vec2 operator*(const vec2& in);
      vec2 operator*(const POINT2D<type>& in);
    };
    template <class type> struct vec3 {
      void operator=(vec3<type> in);
      void operator=(vec2<type> in);
      vec3<type>& operator=(std::initializer_list<type> list);
      vec3<type> operator*(const vec3<type>& in);
      vec3<type> operator*(const type& in);
      vec3<type> operator+(const vec3<type>& in);
      vec3<type> operator+(const type& in);
      vec3<type> operator-(const vec3<type>& in);
      vec3<type> operator-(const type& in);
      void operator+=(const vec3<type>& in);
      type& operator[](int i) const;
    };
    template <class type> struct vec4 {
      template <class type2> void operator=(Matrix<type2> in);
      template <class type2> void operator=(Array<type2> in);
      void operator=(vec4<type> in);
      void operator=(vec3<type> in);
      void operator=(vec2<type> in);
      type& operator[](int i) const;
      template <class type2> vec4<type> operator*(const Matrix<type2>& in);
    };
    // Version    // class File {
    // public:
    //   template <typename lambda> static void Read(std::string path, lambda func);
    //   void Write(std::string path, const std::string& in);
    //   template <typename lambdaw>
    //   static void ReadW(const wchar_t* path, lambdaw func);
    //   void WriteW(const char* path, const std::wstring& in);
    // };
    void RG_GetVersion(int& major, int& minor, int& patch, int& wip);
    void RG_GetVersion(int& major, int& minor, int& patch);
    // class File {
    // public:
    //   template <typename lambda> static void Read(std::string path, lambda func);
    //   void Write(std::string path, const std::string& in);
    //   template <typename lambdaw>
    //   static void ReadW(const wchar_t* path, lambdaw func);
    //   void WriteW(const char* path, const std::wstring& in);
    // };
};
} // namespace Rinegine
