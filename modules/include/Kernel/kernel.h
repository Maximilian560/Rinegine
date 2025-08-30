#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/kernel"
//
// #ifdef RG_UTF
// inlinestd::wostream &operator<<(std::wostream &out, const std::wstring &text)
// {
//   return out.write(text.data(), text.size());
// }
// std::wostream &operator<<(std::wostream &out, const std::string &text);
// #else
// std::ostream &operator<<(std::ostream &out, const std::string &text);
// #endif

namespace Rinegine {
class Kernel {
public:
  //* types
  template <class type> class Matrix;
  template <class type> class Array;
  //* vars
  static std::string AMainFolder;
  static std::wstring WMainFolder;
  static rg_string MainFolder;
  static __uint8_t RG_D_W_L;

  static int InterPoint(int, char **, int (*)());    // done
  static int InterPoint(int, wchar_t **, int (*)()); // done
  static void init();                                // todo

  class Lock {
    friend class Kernel;

    struct LogVars;
    static LogVars _vars;

  public:
    static void *s_new(const unsigned long long &,
                       const unsigned long long & = 1);
    static void *s_fast_new(const unsigned long long &size,
                            const unsigned long long &typesize = 1);
    static void s_delete(void *, unsigned int);
    static void s_fast_delete(void *, unsigned int);
    // static char s_print(void *, unsigned int = 1);

    static void addl(Log::Types = Log::DEBUG, std::string = "NULL", bool = 1,
                     std::string = "NULL", int = -1); // done
    static void addl(Log::Types = Log::DEBUG, std::wstring = L"NULL", bool = 1,
                     std::wstring = L"NULL", int = -1); // done

    template <class type> struct CountPointers;
  };

  static std::wstring utf8_decode(const std::string &); // done
  static std::string utf8_encode(const std::wstring &); // done

  static std::wstring to_stringw(const std::string &);  // done
  static std::wstring to_stringw(const std::wstring &); // done
  static std::string to_stringa(const std::string &);   // done
  static std::string to_stringa(const std::wstring &);  // done
  static rg_string
  to_string(const std::string &); // done, may do some bug. In fact - outdate
  static rg_string
  to_string(const std::wstring &); // done, may do some bug. In fact - outdate
  //!!! ↓outdate soon↓ !!!
  template <class type> struct POINT2D {
    type x = type(), y = type();

    bool operator==(POINT2D<type>); // done
    bool operator>=(POINT2D<type>); // done
    bool operator<=(POINT2D<type>); // done
    bool operator>(POINT2D<type>);  // done
    bool operator<(POINT2D<type>);  // done
    type &operator[](uint);         // done
  };

  template <class type> struct POINT3D {
    type x = type(), y = type(), z = type();
    bool operator==(POINT3D<type>); // done
    bool operator>=(POINT3D<type>); // done
    bool operator<=(POINT3D<type>); // done
    bool operator>(POINT3D<type>);  // done
    bool operator<(POINT3D<type>);  // done
    type &operator=(POINT2D<type>); // done
    type &operator[](uint);         // done
  };
  template <class type> struct COLOR3D {
    type r = type(), g = type(), b = type();
    bool operator==(COLOR3D<type>); // done
    bool operator>=(COLOR3D<type>); // done
    bool operator<=(COLOR3D<type>); // done
    bool operator>(COLOR3D<type>);  // done
    bool operator<(COLOR3D<type>);  // done
    type &operator=(POINT2D<type>); // done
    type &operator[](uint);         // done
  };
  template <typename type> struct COLOR4D {
    type r = type(), g = type(), b = type(), a = type();
    bool operator==(const COLOR4D<type> &);
    bool operator!=(const COLOR4D<type> &);
  };
  //!!! ↑outdate soon↑ !!!
  //!!! use vec types instead!!!
  //!!! as example vec3<int> instead POINT3<int> and COLOR3<int>!!!

  static int KeyIs(int, bool);      // done
  static int KeyIsPress(int, bool); // done
  static int TestKeyIs(int, bool);  // done

  class SysTime {
    struct SysTimeVar;
    static SysTimeVar _vars;

  public:
    static void update();
    // W
    static std::wstring YearW();         // done
    static std::wstring MonthW();        // done
    static std::wstring DayOfWeekW();    // done
    static std::wstring DayW();          // done
    static std::wstring HourW();         // done
    static std::wstring MinuteW();       // done
    static std::wstring SecondW();       // done
    static std::wstring MillisecondsW(); // done
    // A
    static std::string YearA();         // done
    static std::string MonthA();        // done
    static std::string DayOfWeekA();    // done
    static std::string DayA();          // done
    static std::string HourA();         // done
    static std::string MinuteA();       // done
    static std::string SecondA();       // done
    static std::string MillisecondsA(); // done
    //
    static rg_string Year();         // done, may do some bug. In fact - outdate
    static rg_string Month();        // done, may do some bug. In fact - outdate
    static rg_string DayOfWeek();    // done, may do some bug. In fact - outdate
    static rg_string Day();          // done, may do some bug. In fact - outdate
    static rg_string Hour();         // done, may do some bug. In fact - outdate
    static rg_string Minute();       // done, may do some bug. In fact - outdate
    static rg_string Second();       // done, may do some bug. In fact - outdate
    static rg_string Milliseconds(); // done, may do some bug. In fact - outdate
  };
  static void SetColorConsole(WORD);                                    // done
  static bool isSubstringAt(const char &, const std::string &);         // done
  static bool isSubstringAt(const wchar_t &, const std::wstring &);     // done
  static bool isSubstringAt(const std::string &, const std::string &);  // done
  static bool isSubstringAt(const std::string &, const std::wstring &); // done
  static void Open(std::string);                                        // done
  static void Open(std::wstring);                                       // done

  static std::string tolowstr(std::string); // done
  /// @brief Converts the string to lowercase. Does not work with unicode!!!
  /// Only Latin
  /// @param wstring any case
  /// @return `wstring`  lowercase
  static std::wstring tolowwstr(std::wstring); // done // todo

  //* decode
  static char *itoa(int, int = 10, char * = nullptr); // done
  static std::string itos(int, int = 10);             // done
  static std::wstring itows(int, int = 10);           // done
  //*folder
  static bool isDirectory(std::string);        // done
  static bool isDirectory(std::wstring);       // done
  static bool CreateFolder(std::string path);  // done
  static bool CreateFolder(std::wstring path); // done

  //*debug
  class Debug {             // done
    struct DebugVars;       // done
    static DebugVars _vars; // done

  public:
    Debug();                                // done
    Debug(rg_string);                       // done
    static void init();                     // done
    static void init(rg_string);            // done
    static void open_log_after_error(bool); // done
    static void open_shell(bool); // done (same as open_log_after_error)
    static rg_string log_path();  // done
    static void update();         // done
    static void stop() __attribute__((noreturn)); // done
    static void no_close();                       // done
    ~Debug();                                     // done

    //*special add/addl for dif os
    static void add(rg_string = "NULL", Log::Types = Log::DEBUG, bool = true,
                    rg_string = "NULL", int = -1); // done
    template <class string1, class string2>
    static void add(string1, Log::Types = Log::DEBUG, bool = true,
                    string2 = string2(), int = 0); // done
    static void addl(Log::Types = Log::DEBUG, rg_string = RG_L "empty",
                     bool = true, rg_string = rg_to_string(RG_HERE_FILE_NAME),
                     int = -1); // done
    //*other add/addl
    template <class string1, class string2>
    static void addl(Log::Types = Log::DEBUG, string1 = string1(), bool = true,
                     string2 = string2(), int = -1); // done

  }; // done
  // std::wstring GetLastErrorStringW(DWORD);//todo... i guess
  // std::string GetLastErrorStringA(DWORD);//todo... i guess
  rg_string GetLastErrorString(DWORD); // done

  // ALLOC

  // template <class type> static type *s_new(int, type &&);

  // template <class type> static type *s_new(int, const type &);
  template <class type> static type *s_new(int s) {
    if (!std::is_default_constructible<type>::value) {
      RG_LOG_LOCK_ERROR("Type must be default constructible");
      return nullptr;
    }
    type *t = (type *)Lock::s_new(s, sizeof(type));
    return t;
  }

  template <class type> static type *s_new(int s, type &&in) {
    if (!std::is_default_constructible<type>::value) {
      RG_LOG_LOCK_ERROR("Type must be default constructible");
      return nullptr;
    }
    type *t = (type *)Lock::s_new(s, sizeof(type));
    for (int i = 0; i < s; i++)
      new (t + i) type(std::forward<type>(in));
    return t;
  }
  template <class type> static type *s_new(int s, const type &in) {
    if (!std::is_default_constructible<type>::value) {
      RG_LOG_LOCK_ERROR("Type must be default constructible");
      return nullptr;
    }
    type *t = (type *)Lock::s_new(s, sizeof(type));
    for (int i = 0; i < s; i++)
      t[i] = in;
    return t;
  }
  // static void *s_new(int s, int typesize) { return Lock::s_new(s, typesize);
  // }

  // new fast
  template <class type> static type *s_fast_new(unsigned int s) {
    type *t = (type *)Lock::s_fast_new(s, sizeof(type));
    return t;
  }

  // template <class type> static type *s_fast_new(unsigned int s, type &&in) {
  //   type *t = (type *)Lock::s_fast_new(s, sizeof(type));
  //   for (unsigned int i = 0; i < s; i++)
  //     new (t + i) type(std::forward<type>(in));
  //   return t;
  // }
  template <class type>
  static type *s_fast_new(unsigned int s, const type &in) {
    type *t = (type *)Lock::s_fast_new(s, sizeof(type));
    for (unsigned int i = 0; i < s; i++)
      new (t + i) type(in);
    return t;
  }

  // template <class type, class gen>
  // static std::enable_if_t<std::is_invocable_r_v<type, gen>, type*>
  // s_fast_new(unsigned int s, gen&&in) {
  //   type *t = (type *)Lock::s_fast_new(s, sizeof(type));
  //   for (unsigned int i = 0; i < s; i++)
  //     // t[i] = in();
  //     new (t + i) type(in());
  //   return t;
  // }
  // static void *s_fast_new(unsigned int s, int typesize) { return
  // Lock::s_fast_new(s, typesize); }

  //! ALLOCATOR EXPERIMENTAL

  template <typename T> struct Allocator {
    using value_type = T;

    Allocator() = default;
    template <class U> constexpr Allocator(const Allocator<U> &) noexcept {}

    T *allocate(std::size_t n) {
      if (n == 0)
        return nullptr;
      void *ptr = Kernel::s_fast_new<T>(static_cast<unsigned int>(n));
      if (!ptr)
        throw std::bad_alloc{};
      return static_cast<T *>(ptr);
    }

    void deallocate(T *ptr, std::size_t n) noexcept {
      if (ptr) {
        Kernel::Lock::s_fast_delete(ptr, sizeof(T));
      }
    }

    bool operator==(const Allocator &) const { return true; }
    bool operator!=(const Allocator &) const { return false; }
  }; //! EXPERIMENTAL
  static bool s_rawmemtest(char *); // done

  // template <class type> static bool s_memtest(type *);
  static bool s_memtest(const void *); // done

  static const unsigned long long &s_get_size(const void *); // done

  // template <class type> static char s_print(type *);

  static char s_print(to_rrvalue(char *)); // done

  static char s_print(to_rrvalue(wchar_t *)); // done

  static char s_print(to_rrvalue(std::string *)); // done

  static char s_print(to_rrvalue(std::wstring *)); // done

  static char s_print(std::string *); // done

  static char s_print(std::wstring *); // done

  template <class type> static char s_print(type *in) { // done
    int temp_size = Kernel::s_get_size(in);
    for (int i = 0; i < temp_size; i++) {
      if (i != temp_size - 1)
        rg_cout << in[i] << ", ";
      else
        rg_cout << in[i];
    }
    return '\0';
  }

  template <class ForwardIt, class Generator>
  static void s_fill_func(ForwardIt first, ForwardIt last,
                          Generator g) { // done
    for (; first != last; ++first)
      *first = g();
  }

  template <class ForwardIt, class Generator>
  static void s_fill(ForwardIt first, ForwardIt last, Generator g) { // done
    for (; first != last; ++first)
      *first = g;
  }
  template <class type, class gen>
  static void s_fill_func(type arr, int size, gen g) { // done
    for (int i = 0; i < size; i++) {
      arr[i] = g();
    }
  }
  template <class type, class gen>
  static void s_fill(type arr, int size, gen g) { // done
    for (int i = 0; i < size; i++) {
      arr[i] = g;
    }
  }

  static char *s_getraw(void *in); // done

  template <typename type>
  typename std::enable_if<std::is_class<type>::value,
                          void>::type static s_delete(type *&in) { // done
    if (in == nullptr)
      return;
    if (!s_memtest(in)) {
      RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
      return;
    }
    const unsigned long long &size = Rinegine::Kernel::s_get_size(in);
    for (int i = 0; i < size; i++) {
      in[i].~type();
    }
    Lock::s_delete(in, sizeof(type));
  }

  template <typename type>
  typename std::enable_if<!std::is_class<type>::value,
                          void>::type static s_delete(type *&in) { // done
    if (in == nullptr)
      return;
    if (!s_memtest(in)) {
      RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
      return;
    }
    Lock::s_delete(in, sizeof(type));
  }

  template <typename type>
  typename std::enable_if<std::is_class<type>::value,
                          void>::type static s_fast_delete(type *&in) { // done
    if (in == nullptr)
      return;
    if (!s_memtest(in)) {
      RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
      return;
    }
    const unsigned long long &size = Rinegine::Kernel::s_get_size(in);
    for (int i = 0; i < size; i++) {
      in[i].~type();
    }
    Lock::s_fast_delete(in, sizeof(type));
  }

  template <typename type>
  typename std::enable_if<!std::is_class<type>::value,
                          void>::type static s_fast_delete(type *&in) { // done
    if (in == nullptr)
      return;
    if (!s_memtest(in)) {
      RG_LOG_LOCK_ERROR("Memory Deallocation is failed, array is not RG type");
      return;
    }
    Lock::s_fast_delete(in, sizeof(type));
  }

  template <typename T> static decltype(auto) s_move(T &obj) { // done
    return (T &&)obj;
  }

  // template <class type> static void s_resize(type *&, to_rvalue(int));
  template <class type>
  static void s_resize(type *&in, to_rvalue(int) n_size) { // done
    if (n_size <= 0) {                                     // loss then zero
      s_delete(in);
      return;
    }
    if (in == nullptr) { // uninitialize
      in = s_new<type>(n_size);
      return;
    }
    if (!s_memtest(in)) { // is not the RG type
      RG_LOG_LOCK_ERROR("Memory Resize is failed, array is not RG type");
      return;
    }
    int size = s_get_size(in);
    if (size == n_size)
      return;
    type *temp = s_new<type>(n_size);
    for (int i = 0; i < rg_min(size, n_size); i++) {
      temp[i] = std::move(in[i]);
    }
    s_delete<type>(in);
    in = temp;
  }

  // template <class type> static void s_renew(type *&, to_rvalue(int));
  // //!outdate

  // template <class type> static int s_erase(type *&, int, int, int);
  // //!outdate

  // template <class type> static int s_erase_new(type *&, int, int); //!outdate

  // template <class type> static int Get_Count_Pointers(); //!outdate/useless
  // in new style

  // template <class type> static Array<type *> Get_All_Pointers();
  // //!outdate/useless in new style

  //* raw pointer
  //* raw pointer
  struct Raw_Pointer {
    void *ptr = nullptr;
    unsigned int typesize = 0;
    unsigned int arrsize = 0;
    // init test
    bool is_init() const;

    // POINTER GET
    const void *get() const;

    // CONSTRUCTORs
    Raw_Pointer();
    Raw_Pointer(void *in);

    // INITs
    void init();
    void init(void *in);
    // OPERATORs
    Raw_Pointer &operator=(void *in);
    void *operator->();
    void clear();
    operator void *() const;
    ~Raw_Pointer();
  };
  //* pointer
  template <typename type> class Pointer {
    struct PointerVars;
    PointerVars _vars;

  public:
    bool is_init() const;
    const type *get() const;
    Pointer();

    Pointer(const type &);
    Pointer(Pointer &&) noexcept;
    Pointer(const Pointer &);
    Pointer(type *);
    void init();
    void init(type &);
    void init(const type &);
    void init(type);
    void init(type *);
    Pointer &operator=(const type &);
    Pointer &operator=(Pointer &&) noexcept;
    Pointer &operator=(const Pointer &);
    Pointer &operator=(type *);
    type *operator->();
    void clear() const;
    operator type *() const;
    ~Pointer();
  };
  //*array
  template <class type> class Array {
    struct ArrayVars;
    ArrayVars _vars;

  public:
    Array();
    Array(Array &&) noexcept;
    Array(to_rvalue(Array<type>));
    Array(int, to_rvalue(type));
    Array(int, type *);
    Array(int);
    Array(to_rvalue(std::initializer_list<type>));
    template <class type2> Array(to_rvalue(std::initializer_list<type2>));
    explicit Array(to_rrvalue(type *));
    void fastpop();
    void fastpush();
    void fastpush(to_rvalue(type));
    void fastpush(to_rvalue(Array<type>));
    void fastpush(to_rvalue(std::initializer_list<type>));
    void fastpush(to_rvalue(type *));
    void fastpush(type &&) noexcept;
    void fastpush(Array<type> &&);
    template <typename... Args> void fastemplace(Args &&...) noexcept;
    void set_push_reserve(to_rvalue(uint));
    void init(int);
    void init(to_rvalue(int), to_rvalue(type));
    void init(to_rvalue(type *));
    void init(to_rvalue(uint), to_rrvalue(type *));
    void init(to_rvalue(std::initializer_list<type>));
    template <class type2> void init(to_rvalue(std::initializer_list<type2>));
    void init(to_rvalue(Array<type>));
    void resize(int);
    void fast_clear();
    void reserve(to_rvalue(int));
    void reserve_fill();
    void reinit(to_rvalue(int));
    void fill(type (*)());
    void fillfull(to_rvalue(uint), to_rvalue(type));
    void fill(type);
    template <class type2> void fill(type2);
    void fill(type *);
    void push_back();
    void push_back(to_rvalue(type));
    void push_back(to_rvalue(Array<type>));
    void push_back(to_rvalue(std::initializer_list<type>));
    void push_back(to_rvalue(type *));
    template <typename... Args> void emplace_back(Args &&...);
    type &operator[](to_rvalue(int)) const;
    type &operator[](to_rvalue(uint)) const;
    Array<type> operator*(to_rvalue(Matrix<type>)) const;
    Array<type> operator*(to_rvalue(type)) const;
    Array<type> operator-(to_rvalue(Array<type>)) const;
    Array<type> operator+(to_rvalue(Array<type>)) const;
    Array<type> operator%(to_rvalue(Array<type>)) const;
    Array<type> operator*(to_rvalue(Array<type>)) const;
    template <class em> void operator=(to_rvalue(em));
    void operator=(to_rvalue(type));
    void operator=(to_rvalue(Array<type>));
    void operator=(const std::initializer_list<type> *);
    void operator=(const char *);
    void copy(to_rvalue(Array<type>));
    void operator-=(to_rvalue(Array<type>));
    void operator+=(to_rvalue(Array<type>));
    Matrix<type> transpose() const;
    type *get() const;
    type *data() const;
    type *get_array() const;
    type *get_arr() const;
    type &get(to_rvalue(int)) const;
    type &get(to_rvalue(uint)) const;
    type *begin() const;
    type *end() const;
    type *back() const;
    uint size() const;
    uint true_size() const;
    void print() const;
    rg_string get_string();
    type sum() const;
    void fill_range_random(to_rvalue(type), to_rvalue(type));
    bool empty() const;
    void movefill(to_rvalue(uint), type *);
    void clear();
    void fastclear();
    ~Array();
  };
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
    void init(to_rvalue(uint), to_rvalue(uint), type *);
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
    void fill(to_rvalue(uint), to_rvalue(uint), type *);
    void fill(to_rvalue(Array<type>));
    void fill(to_rvalue(std::initializer_list<std::initializer_list<type>>));
    template <class type2>
    void fill(to_rvalue(std::initializer_list<std::initializer_list<type2>>));
    void movefill(to_rvalue(uint), to_rvalue(uint), type *);
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
    Matrix<type> &transpose();
    type &get_t(const uint &, const uint &) const;
    void update_transpose();
    type *operator[](const uint &) const;
    type &operator()(const uint &, const uint &) const;
    type &operator()(to_rvalue(POINT2D<uint>)) const;
    type &operator()(to_rvalue(POINT2D<int>)) const;
    type &operator[](to_rvalue(POINT2D<uint>)) const;
    type &operator[](to_rvalue(POINT2D<int>)) const;
    type &get(const uint &, const uint &) const;
    type &getyx(to_rvalue(uint), to_rvalue(uint)) const;
    type &get(to_rvalue(POINT2D<uint>)) const;
    type &get(to_rvalue(POINT2D<int>)) const;
    void print() const;
    std::string print_d() const;
    rg_ostrem &print(rg_ostrem &) const;
    operator type *();
    type *get() const;
    type *data() const;
    type *get_mat() const;
    operator Array<type> &() const;
    bool empty() const;
    operator bool();
    uint size(to_rvalue(uint)) const;
    operator Array<type>() const;
    operator uint() const;
    POINT2D<uint> size() const;
    void clear();
    ~Matrix();
    void operator*=(const type *);
    void operator*=(const std::initializer_list<std::initializer_list<type>> &);
    template <class type2>
    void
    operator*=(const std::initializer_list<std::initializer_list<type2>> &);
    void operator*=(const Matrix<type> &);
    template <class type2> Matrix<type> operator*(const type2 &) const;
    template <class type2>
    Matrix<type> operator%(to_rvalue(Matrix<type2>)) const;
    Matrix<type> operator*(const Matrix<type> &);
    Matrix<type> operator*(const Array<type> &) const;
    void operator+=(const Matrix<type> &);
    void operator-=(const Matrix<type> &);
    Matrix<type> operator+(const Matrix<type> &);
    Matrix<type> operator-(const Matrix<type> &);
    template <class tttt> void place(POINT2D<int>, Matrix<tttt> &);
  };
  template <class type, class type2>
  static type SpecialMatMulti(Matrix<type> &, Matrix<type2> &, int, int);
  // TODO Удалить
  template <class type, class type2>
  static bool CountMatMinus(Matrix<type> &, Matrix<type2> &, int, int);
  //* 3D Matrix
  template <typename type> class RG_Matrix3D {
    struct Matrix3DVars;
    Matrix3DVars _vars;

  public:
    void init(to_rvalue(Array<type>));
    void init(to_rvalue(std::initializer_list<std::initializer_list<type>>));
    void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint));
    void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type *);
    void init(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint),
              to_rvalue(type));
    void init(to_rvalue(RG_Matrix3D<type>));
    RG_Matrix3D();
    RG_Matrix3D(to_rvalue(Array<type>));
    RG_Matrix3D(to_rvalue(RG_Matrix3D<type>));
    RG_Matrix3D(to_rvalue(std::initializer_list<std::initializer_list<type>>));
    RG_Matrix3D(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint));
    RG_Matrix3D(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type *);
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
    void fill(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type *);
    void fill(to_rvalue(Array<type>));
    void fill(to_rvalue(std::initializer_list<
                        std::initializer_list<std::initializer_list<type>>>));
    template <class type2>
    void fill(to_rvalue(std::initializer_list<
                        std::initializer_list<std::initializer_list<type2>>>));
    void movefill(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint), type *);
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
    type &get(const uint &, const uint &, const uint &) const;
    type &getzyx(to_rvalue(uint), to_rvalue(uint), to_rvalue(uint)) const;
    type &get(to_rvalue(POINT3D<uint>)) const;
    type &get(to_rvalue(POINT3D<int>)) const;
    void print() const;
    operator type *();
    type *get() const;
    type *get_mat() const;
    operator Array<type> &() const;
    bool empty() const;
    operator bool();
    uint size(to_rvalue(uint)) const;
    operator Array<type>() const;
    operator uint() const;
    POINT3D<uint> size() const;
    void clear();
    ~RG_Matrix3D();
    template <class type2> RG_Matrix3D<type> operator*(const type2 &) const;
    template <class type2>
    RG_Matrix3D<type> operator%(to_rvalue(RG_Matrix3D<type2>)) const;
    void operator+=(const RG_Matrix3D<type> &);
    void operator-=(const RG_Matrix3D<type> &);
    template <class tttt> void place(POINT3D<int>, RG_Matrix3D<tttt> &);
  };
  // map
  template <class type> class RG_Map {
  public:
    RG_Map();
    RG_Map(uint size);
    RG_Map(std::string key, type val);
    RG_Map(RG_MapData<std::string, type>);
    RG_Map(Array<RG_MapData<std::string, type>>);
    RG_Map(std::initializer_list<RG_MapData<std::string, type>>);
    void init(uint size);
    void init(std::string key, type val);
    void init(RG_MapData<std::string, type>);
    void init(Array<RG_MapData<std::string, type>>);
    void init(std::initializer_list<RG_MapData<std::string, type>>);
    void fill(std::string key, type val);
    void fill(RG_MapData<std::string, type>);
    void fill(uint size);
    void fill(Array<RG_MapData<std::string, type>>);
    void fill(std::initializer_list<RG_MapData<std::string, type>>);
    int findpos(std::string ii);
    type find(std::string ii);
    type find(int ii);
    type operator[](std::string i);
    void sort();
    RG_MapData<std::string, type> &operator[](uint i);
    void push_back(RG_MapData<std::string, type>);
    void resize(uint size);
    int size();
    RG_MapData<std::string, type> *get_arr();
    Array<type> &get_rgarr();
    void clear();
    ~RG_Map();
  };
  template <class type> class RG_WMap {

  public:
    RG_WMap();
    RG_WMap(uint size);
    RG_WMap(std::wstring key, type val);
    RG_WMap(RG_MapData<std::wstring, type>);
    RG_WMap(Array<RG_MapData<std::wstring, type>>);
    RG_WMap(std::initializer_list<RG_MapData<std::wstring, type>>);
    void init(uint size);
    void init(std::wstring key, type val);
    void init(RG_MapData<std::wstring, type>);
    void init(Array<RG_MapData<std::wstring, type>>);
    void init(std::initializer_list<RG_MapData<std::wstring, type>>);
    void fill(std::wstring key, type val);
    void fill(RG_MapData<std::wstring, type>);
    void fill(uint size);
    void fill(Array<RG_MapData<std::wstring, type>>);
    void fill(std::initializer_list<RG_MapData<std::wstring, type>>);
    int findpos(std::wstring ii);
    type &find(std::wstring ii);
    type &find(int ii);
    RG_MapData<std::wstring, type> &findstring(std::wstring ii);
    type &operator[](std::wstring i);
    RG_MapData<std::wstring, type> &findchar(wchar_t in);
    void revsort();
    void sort();
    RG_MapData<std::wstring, type> &operator[](uint i);
    void push_back(RG_MapData<std::wstring, type>);
    void resize(uint size);
    int size();
    RG_MapData<std::wstring, type> *get_arr();
    Array<type> &get_rgarr();
    void clear();
    ~RG_WMap();
  };
  static uint64_t wstring_to_seed(const std::wstring &);
  class RG_CRand {
  public:
    RG_CRand();
    RG_CRand(uint64_t);
    void init(uint64_t);
    bool is_init();
    uint64_t rand();
  };
  static int set_seed();
  static uint64_t RG_Rand();
  static uint64_t Rand();
  static double RandRange(double, double);
  // encode
  template <class type> class RG_List {
  public:
    operator Array<type> &();
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
  std::wstring utf8_to_utf16(const std::string &str);
  std::string utf16_to_utf8(const std::wstring &wstr);
#endif
  static std::wstring WFileLoad(std::string path);
  static std::string AFileLoad(std::string path);
  static std::wstring WFileLoad(std::wstring path);
#ifdef RG_UTF
  template <class in_string> static rg_string FileLoad(in_string path);
#else
  template <class in_string> static rg_string FileLoad(in_string path);
#endif
  static bool RG_IsFile(std::string path);
  static std::string GetTypePath(std::string path);
#ifdef RG_WINos
  class FileFinder {
  public:
    bool eof();
    WIN32_FIND_DATA *init(const rg_string &path);
    WIN32_FIND_DATA *next();
    void close();
    ~FileFinder();
  };
  class FileFinderA {
  public:
    bool eof();
    WIN32_FIND_DATAA *init(const std::string &path);
    WIN32_FIND_DATAA *next();
    void close();
    ~FileFinderA();
  };
  class FileFinderW {
  public:
    bool eof();
    WIN32_FIND_DATAW *init(const std::wstring &path);
    WIN32_FIND_DATAW *next();
    void close();
    ~FileFinderW();
  };
#endif
  // otherDef
  static int RG_CMD(std::string, bool = true);
  struct RG_ConfigRunProgram;
#ifdef RG_WIN
  static int RG_RunProgram(RG_ConfigRunProgram conf);
#elif defined(RG_Linux)
  static int RG_RunProgram(RG_ConfigRunProgram conf);
#endif
  static std::string RG_AGetMainFolder();
  static std::wstring RG_WGetMainFolder();
#ifdef RG_UTF
  static std::wstring RG_GetMainFolder();
#else
  static std::string RG_GetMainFolder();
#endif
  template <class type> struct vec2 {
    void operator=(vec2<type> in);
    type &operator[](int i);
    vec2 operator*(const vec2 &in);
    vec2 operator*(const POINT2D<type> &in);
  };
  template <class type> struct vec3 {
    void operator=(vec3<type> in);
    void operator=(vec2<type> in);
    vec3<type> &operator=(std::initializer_list<type> list);
    vec3<type> operator*(const vec3<type> &in);
    vec3<type> operator*(const type &in);
    vec3<type> operator+(const vec3<type> &in);
    vec3<type> operator+(const type &in);
    vec3<type> operator-(const vec3<type> &in);
    vec3<type> operator-(const type &in);
    void operator+=(const vec3<type> &in);
    type &operator[](int i) const;
  };
  template <class type> struct vec4 {
    template <class type2> void operator=(Matrix<type2> in);
    template <class type2> void operator=(Array<type2> in);
    void operator=(vec4<type> in);
    void operator=(vec3<type> in);
    void operator=(vec2<type> in);
    type &operator[](int i) const;
    template <class type2> vec4<type> operator*(const Matrix<type2> &in);
  };
  // Version
  static void RG_GetVersion(int &major, int &minor, int &patch, int &wip);
  static void RG_GetVersion(int &major, int &minor, int &patch);
};
class File {
public:
  template <typename lambda> static void Read(std::string path, lambda func);
  void Write(std::string path, const std::string &in);
  template <typename lambdaw>
  static void ReadW(const wchar_t *path, lambdaw func);
  void WriteW(const char *path, const std::wstring &in);
};

} // namespace Rinegine

// template <class type>
// std::ostream &operator<<(std::ostream &st, Rinegine::Kernel::vec2<type> &in);
// template <class type>
// std::ostream &operator<<(std::ostream &st, Rinegine::Kernel::vec3<type> &in);
// template <class type>
// std::ostream &operator<<(std::ostream &st, Rinegine::Kernel::vec4<type> &in);
// template <class type>
// std::wostream &operator<<(std::wostream &st, Rinegine::Kernel::vec2<type>
// &in); template <class type> std::wostream &operator<<(std::wostream &st,
// Rinegine::Kernel::vec3<type> &in); template <class type> std::wostream
// &operator<<(std::wostream &st, Rinegine::Kernel::vec4<type> &in);