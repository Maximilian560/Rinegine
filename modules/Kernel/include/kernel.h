#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/kernel"
namespace Rinegine {
  namespace Kernel {

    // [Arrays with main arguments]
    extern Array<std::string> AMainArguments;  //TODO remove vector, set RG::Array!
    extern Array<std::wstring> WMainArguments; //TODO remove vector, set RG::Array!

    // [Flags namespace for work with flags]


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


    int KeyIs(int, bool);      // [done]
    int KeyIsPress(int, bool); // [done]
    int TestKeyIs(int, bool);  // [done]

    // #ifdef RG_SYS_WINDOWS
    //     void SetColorTCMD(WORD); // [done,exp]
    // #else
    void SetColorConsole(WORD); // [done,exp]
    // #ifdef RG_SYS_WINDOWS
#ifdef __WIN32
    inline void SetColorTCMD(WORD col) { // [done,exp]
      static HANDLE HandleMainConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(HandleMainConsole, col);
    }
#endif
    // #ifdef __WIN32 && !defined(RinegineLib)

    // #endif

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

    // std::wstring GetLastErrorStringW(DWORD);//todo... i guess
    // std::string GetLastErrorStringA(DWORD);//todo... i guess
    rg_string GetLastErrorString(DWORD); // [done]

    // ALLOC

    // template <class type> static type *s_new(int, type &&);

    // template <class type> type *s_new(int, const type &);

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
#ifdef RG_SYS_WINDOWS
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
#ifdef RG_SYS_WINDOWS
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
    // struct ConfigRunProgram;

// #ifdef RG_SYS_WINDOWS
//     int RunProgram(ConfigRunProgram conf);
// #elif defined(RG_SYS_LINUX)
//     int RunProgram(ConfigRunProgram conf);
// #endif
    std::string RG_AGetMainFolder();
    std::wstring RG_WGetMainFolder();
#ifdef RG_UTF
    std::wstring RG_GetMainFolder();
#else
    std::string RG_GetMainFolder();
#endif

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
