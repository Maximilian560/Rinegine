#pragma once

namespace Rinegine {
  namespace Kernel {
    class Raw_Pointer;struct Raw_Pointer { // [exp]
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
  }
} // namespace Rinegine