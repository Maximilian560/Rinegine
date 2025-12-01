#pragma once

/*struct rg_raw_array{
  void*arr;
  int size=0;
  void
};*/
#define to_rvalue(type)const type&

template<typename type>
class RG_Matrix;

namespace RG {
  template<typename type>
  class Pointer {
    bool _is_copy = false;
    mutable type* _pointer;
  public:
    //INIT CHECK
    inline bool is_init() const {
      return _pointer != nullptr;
    }
    //POINTER GET
    inline const type* get() const {
      return _pointer;
    }
    //CONSTRUCTORs
    Pointer() :_pointer(nullptr) {}
    Pointer(const type& in) :_pointer(RG::s_new<type>(1, in)) { }
    Pointer(Pointer&& other) noexcept : _pointer(other._pointer) {
      other._pointer = nullptr;
    }
    Pointer(const Pointer& other) : _pointer(other.is_init() ? RG::s_new(1, *other._pointer) : nullptr) {
    }
    Pointer(type* in) :_pointer(in) {}

    //INITs

    void init() {
      clear();
      _pointer = RG::s_new<type>(1);
    }
    void init(type& in) {
      clear();
      _pointer = RG::s_new<type>(1, in);
    }
    void init(const type& in) {
      clear();
      _pointer = RG::s_new<type>(1, in);
    }
    void init(type in) {
      clear();
      _pointer = RG::s_new<type>(1, in);
    }
    void init(type* in) {
      clear();
      _pointer = in;
    }
    //OPERATORs
    Pointer& operator=(const type& in) {
      if (_pointer) {
        (*_pointer) = in;
      } else {
        _pointer = RG::s_new(1, in);
      }
      return *this;
    }
    // Pointer& operator=(Pointer&& in) noexcept {
    //   clear();
    //   _pointer = in._pointer;
    //   in._pointer = nullptr;
    // }
    Pointer& operator=(Pointer&& in)noexcept {
      if (this != &in) {
        clear();
        _pointer = in._pointer;
        in._pointer = nullptr;
      }
      return *this;
    }
    Pointer& operator=(const Pointer& in) {
      if (this != &in) {
        clear();
        _pointer = RG::s_new<type>(1, *in._pointer);
      }
      return *this;
    }
    Pointer& operator=(type* in) {
      clear();
      _pointer = in;
    }
    type* operator->() {
      return _pointer;
    }
    // void to_copy(Pointer& in) {
    //   _is_copy = true;
    //   _pointer = in._pointer;
    // }
    inline void clear()const {
      if (_pointer && !_is_copy) {
        RG::s_delete<type>(_pointer);
        _pointer = nullptr;
      }
    }
    operator type* ()const {
      return _pointer;
    }
    ~Pointer() {
      if (_pointer && !_is_copy) {
        RG::s_delete<type>(_pointer);
        _pointer = nullptr;
      }
    }
  };
}