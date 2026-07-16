#pragma once

namespace Rinegine {
  namespace Kernel {
    // struct RawArray {
    // BYTE* RawArray::data = nullptr;
    // size_t RawArray::real_size = 0;
    // size_t RawArray::size = 0;
    RawArray::RawArray() :data(nullptr), real_size(0), size(0){};

    RawArray::RawArray(const RawArray& other):data(nullptr), real_size(0), size(0) {
      resize(other.size);
      if (size > 0) [[likely]] {
        std::memcpy(data, other.data, size);
      }
    }

    RawArray::RawArray(RawArray&& other) noexcept
      : data(other.data), real_size(other.real_size), size(other.size) {
      other.data = nullptr;
      other.size = 0;
      other.real_size = 0;
    }
    RawArray& RawArray::operator=(const RawArray& other) {
      if (this == &other) [[unlikely]] return *this;
      resize(other.size);
      if (size > 0) [[likely]] {
        std::memcpy(data, other.data, size);
      }
      return *this;
    }
    RawArray& RawArray::operator=(std::initializer_list<BYTE> ilist) {
      resize(ilist.size());
      if (ilist.size() > 0) [[likely]] {
        std::memcpy(data, ilist.begin(), ilist.size());
      }
      return *this;
    }
    RawArray& RawArray::operator=(RawArray&& other) noexcept {
      if (this == &other) [[unlikely]] return *this;
      GlobalAllocator.deallocate(data);
      data = other.data;
      real_size = other.real_size;
      size = other.size;
      other.data = nullptr;
      other.size = 0;
      other.real_size = 0;
      return *this;
    }
    void RawArray::resize(size_t nsize) {
      size_t nreal_size = low_level::align_to_cache_line(nsize);
      if (real_size >= nsize) {
        size = nsize;
      }
      else {
        BYTE* ndata = GlobalAllocator.allocate(nreal_size);
        if (data != nullptr)
          memcpy(ndata, data, size);
        GlobalAllocator.deallocate(data);
        real_size = nreal_size;
        size = nsize;
        data = ndata;
      }
    }
    void RawArray::reserve(size_t nsize) {
      size_t nreal_size = low_level::align_to_cache_line(nsize);
      if (real_size < nreal_size) {
        BYTE* ndata = GlobalAllocator.allocate(nreal_size);
        if (data != nullptr)
          memcpy(ndata, data, size);
        GlobalAllocator.deallocate(data);
        real_size = nreal_size;
        data = ndata;
      }
    }
    BYTE& RawArray::operator[](size_t i) {
      if (i >= size) {
        if (i >= real_size) {
          RG_LOG_CRITICAL(std::format("RG::K::Array index error: iterator {:d} > real size {:d}", i, real_size));
        }
        else {
          RG_LOG_WARNING(std::format("RG::K::Array index error: iterator {:d} > size {:d}", i, size));
        }
      }
      return data[i];
    }
    const BYTE& RawArray::operator[](size_t i) const {
      if (i >= size) {
        if (i >= real_size) {
          RG_LOG_CRITICAL(std::format("RG::K::Array index error: iterator {:d} > real size {:d}", i, real_size));
        }
        else {
          RG_LOG_WARNING(std::format("RG::K::Array index error: iterator {:d} > size {:d}", i, size));
        }
      }
      return data[i];
    }
    BYTE* RawArray::begin() noexcept { return data; }
    const BYTE* RawArray::begin() const noexcept { return data; }

    BYTE* RawArray::end() noexcept { return data + size; }
    const BYTE* RawArray::end() const noexcept { return data + size; }

    BYTE& RawArray::back() noexcept { return data[size - 1]; }
    const BYTE& RawArray::back() const noexcept { return data[size - 1]; }

    void RawArray::push_back(BYTE value) {
      resize(size + 1);
      data[size - 1] = value;
    }
    BYTE RawArray::pop_back() {
      BYTE out = data[size - 1];
      resize(size - 1);
      return out;
    }
    RawArray::~RawArray() {
      if (data != nullptr) {
        GlobalAllocator.deallocate(data);
      }
    }
    // };
  }
}