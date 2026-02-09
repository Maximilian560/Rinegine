#pragma once

namespace Rinegine {
  namespace Kernel {
    void RawArray::resize(const size_t& size) {
      if (ptr == nullptr) {
        if (size <= 0) return;
        ptr = Rinegine::s_raw_new(size);
      }
      else {
        if (size <= 0) {
          s_raw_delete(ptr);
        }
        else {
          s_raw_resize(ptr, size);
        }
      }
    }
    size_t RawArray::size()const {
      if (ptr == nullptr)return 0;
      else return ptr->size;
    }
    RawArray::RawArray(size_t size) {
      resize(size);
    }
    RawArray::RawArray(const RawArray& in) {
      if (in.size() != 0) {
        resize(in.size());
        memcpy(ptr, in.ptr, in.size() + sizeof(DATA_OUT));
      }
    }
    RawArray& RawArray::operator=(const RawArray& in) {
      if (size() != 0)clear();
      if (in.size() != 0) {
        resize(in.size());
        memcpy(ptr, in.ptr, in.size() + sizeof(DATA_OUT));
      }
      return *this;
    }

    void RawArray::clear() {
      if (ptr != nullptr) {
        s_raw_delete(ptr);
        ptr = nullptr;
      }
    }
    RawArray::~RawArray() {
      if (ptr != nullptr) {
        s_raw_delete(ptr);
      }
    }
  }
}