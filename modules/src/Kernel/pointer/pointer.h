#pragma once

namespace Rinegine {

// init test
bool Kernel::Raw_Pointer::is_init() const { return ptr != nullptr; }

// POINTER GET
const void *Kernel::Raw_Pointer::get() const { return ptr; }

// CONSTRUCTORs
Kernel::Raw_Pointer::Raw_Pointer() : ptr(nullptr) {}
Kernel::Raw_Pointer::Raw_Pointer(void *in) : ptr(in) {}

// INITs
void Kernel::Raw_Pointer::init() {
  clear();
  ptr = Lock::s_new(1,typesize);
}
void Kernel::Raw_Pointer::init(void *in) {
  clear();
  ptr = in;
}
// OPERATORs
Kernel::Raw_Pointer &Kernel::Raw_Pointer::operator=(void *in) {
  clear();
  ptr = in;
}
void *Kernel::Raw_Pointer::operator->() { return ptr; }
void Kernel::Raw_Pointer::clear() {
  if (ptr) {
    Lock::s_delete(ptr,typesize);
    ptr = nullptr;
  }
}
Kernel::Raw_Pointer::operator void *() const { return ptr; }
Kernel::Raw_Pointer::~Raw_Pointer() { clear(); }

}