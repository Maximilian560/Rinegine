#pragma once
/*
namespace Rinegine::Kernel {
  // init test
  bool Raw_Pointer::is_init() const { return ptr != nullptr; }

  // POINTER GET
  void* Raw_Pointer::get() const { return ptr; }

  // CONSTRUCTORs
  Raw_Pointer::Raw_Pointer() : ptr(nullptr) {}
  Raw_Pointer::Raw_Pointer(void* in) : ptr(in) {
    if (Lock::s_memtest(in)) {
      // typesize = Lock::s_get_typesize(in);
      arrsize = Lock::s_get_size(in);
    }
    else {
      RG_LOG_INFO("Raw Pointer received a pointer that is not of type rg, array "
        "size and type not received");
    }
  }

  // INITs
  void Raw_Pointer::init() {
    clear();
    ptr = Lock::s_new(typesize);
  }
  void Raw_Pointer::init(void* in) {
    clear();
    ptr = in;
  }
  // OPERATORs
  Raw_Pointer& Raw_Pointer::operator=(void* in) {
    clear();
    ptr = in;
    return *this;
  }
  void* Raw_Pointer::operator->() { return ptr; }

  void Raw_Pointer::clear() {
    if (ptr != nullptr) {
      Lock::s_delete(ptr);
      ptr = nullptr;
    }
  }
  Raw_Pointer::operator void* () const { return ptr; }
  Raw_Pointer::~Raw_Pointer() { clear(); }

} // namespace Rinegine
 */