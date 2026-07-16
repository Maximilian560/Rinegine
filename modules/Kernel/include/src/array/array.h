#pragma once

namespace Rinegine {
  namespace Kernel {
    struct RawArray {
      BYTE* data;
      size_t real_size;
      size_t size;
      RawArray();

      RawArray(const RawArray& other);

      RawArray(RawArray&& other) noexcept;
      RawArray& operator=(const RawArray& other);
      RawArray& operator=(std::initializer_list<BYTE> ilist);
      RawArray& operator=(RawArray&& other) noexcept;
      void resize(size_t nsize);
      void reserve(size_t nsize);
      BYTE& operator[](size_t i);
      const BYTE& operator[](size_t i) const;
      BYTE* begin() noexcept;
      const BYTE* begin() const noexcept;

      BYTE* end() noexcept;
      const BYTE* end() const noexcept;

      BYTE& back() noexcept;
      const BYTE& back() const noexcept;

      void push_back(BYTE value);
      BYTE pop_back();
      ~RawArray();
    };


    template<class type>
    class Array : private RawArray {
    public:
      //[CONSTRUCT]
      Array() = default;

      Array(const Array& other) {
        resize(other.size());
        if (size() > 0) [[likely]] {
          if constexpr (Rinegine::Kernel::Util::is_trivial_v<type>) {
            std::memcpy(data(), other.data(), RawArray::size);
          }
          else {
            for (size_t i = 0; i < size(); ++i) {
              new (Rinegine::Kernel::Util::addressof(data()[i])) type(other.data()[i]);
            }
          }
        }
      }

      Array(Array&& other) noexcept : RawArray(std::move(other)) {}

      Array(std::initializer_list<type> ilist) {
        reserve(ilist.size());
        RawArray::size = ilist.size() * sizeof(type);
        if constexpr (Rinegine::Kernel::Util::is_trivial_v<type>) {
          std::memcpy(data(), ilist.begin(), RawArray::size);
        }
        else {
          size_t i = 0;
          for (const type& item : ilist) {
            new (Rinegine::Kernel::Util::addressof(data()[i++])) type(item);
          }
        }
      }
      //[operators]
      Array& operator=(const Array& other) {
        if (this == &other) [[unlikely]] return *this;
        clear();
        resize(other.size());
        if (size() > 0) [[likely]] {
          if constexpr (Rinegine::Kernel::Util::is_trivial_v<type>) {
            std::memcpy(data(), other.data(), RawArray::size);
          }
          else {
            for (size_t i = 0; i < size(); ++i) {
              new (Rinegine::Kernel::Util::addressof(data()[i])) type(other.data()[i]);
            }
          }
        }
        return *this;
      }

      Array& operator=(Array&& other) noexcept {
        if (this == &other) [[unlikely]] return *this;
        clear();
        RawArray::operator=(std::move(other));
        return *this;
      }
      Array& operator=(std::initializer_list<type> ilist) {
        clear();
        reserve(ilist.size());
        RawArray::size = ilist.size() * sizeof(type);

        if constexpr (Rinegine::Kernel::Util::is_trivial_v<type>) {
          std::memcpy(data(), ilist.begin(), RawArray::size);
        }
        else {
          size_t i = 0;
          for (const type& item : ilist) {
            new (Rinegine::Kernel::Util::addressof(data()[i++])) type(item);
          }
        }
        return *this;
      }

      //[main ptr]
      type* data() noexcept {
        return reinterpret_cast<type*>(RawArray::data);
      }

      const type* data() const noexcept {
        return reinterpret_cast<const type*>(RawArray::data);
      }

      //[capacity]
      size_t size() const noexcept {
        return RawArray::size / sizeof(type);
      }

      size_t capacity() const noexcept {
        return RawArray::real_size / sizeof(type);
      }

      //[iterator]
      type& operator[](size_t i) {
        return *reinterpret_cast<type*>(RawArray::data + (i * sizeof(type)));
      }

      const type& operator[](size_t i) const {
        return *reinterpret_cast<const type*>(RawArray::data + (i * sizeof(type)));
      }

      //[useful ptr]
      type* begin() noexcept { return data(); }
      const type* begin() const noexcept { return data(); }

      type* end() noexcept { return data() + size(); }
      const type* end() const noexcept { return data() + size(); }

      //[resize]
      void reserve(size_t n_elements) {
        size_t nreal_size = low_level::align_to_cache_line(n_elements * sizeof(type));
        if (RawArray::real_size >= nreal_size) return;

        if constexpr (Rinegine::Kernel::Util::is_trivial_v<type>) {
          RawArray::reserve(n_elements * sizeof(type));
        }
        else {
          BYTE* ndata = GlobalAllocator.allocate(nreal_size);
          type* new_objects = reinterpret_cast<type*>(ndata);
          size_t current_size = size();

          if (RawArray::data != nullptr) {
            for (size_t i = 0; i < current_size; ++i) {
              new (Rinegine::Kernel::Util::addressof(new_objects[i])) type(std::move(data()[i]));
              data()[i].~type();
            }
            GlobalAllocator.deallocate(RawArray::data);
          }
          RawArray::data = ndata;
          RawArray::real_size = nreal_size;
          RawArray::size = current_size * sizeof(type);
        }
      }

      void resize(size_t n_elements) {
        size_t prevsize = size();
        size_t nsize = n_elements;

        if (nsize < prevsize) {
          if constexpr (!Rinegine::Kernel::Util::has_trivial_destructor_v<type>) {
            for (size_t i = nsize; i < prevsize; ++i) {
              data()[i].~type();
            }
          }
          RawArray::resize(nsize * sizeof(type));
        }
        else if (nsize > prevsize) {
          reserve(nsize);
          RawArray::resize(nsize * sizeof(type));
          for (size_t i = prevsize; i < nsize; ++i) {
            new (Rinegine::Kernel::Util::addressof(data()[i])) type();
          }
        }
      }

      //[som back]
      void push_back(type value) {
        size_t current_size = size();

        if (current_size >= capacity()) {
          reserve(current_size == 0 ? 1 : current_size * 2);
        }
        new (static_cast<void*>(Rinegine::Kernel::Util::addressof(data()[current_size]))) type(std::move(value));
        RawArray::size += sizeof(type);
      }

      template<typename... Args>
      type& emplace_back(Args&&... args) {
        size_t current_size = size();
        if (current_size >= capacity()) [[unlikely]] {
          reserve(current_size == 0 ? 1 : current_size * 2);
        }
        type* placed_object = ::new (static_cast<void*>(Rinegine::Kernel::Util::addressof(data()[current_size])))
          type(Rinegine::Kernel::Util::forward<Args>(args)...);
        RawArray::size += sizeof(type);
        return *placed_object;
      }


      void pop_back() {
        size_t current_size = size();
        if (current_size == 0) [[unlikely]] {
          RG_LOG_CRITICAL("RG::K::Array pop_back error: array is empty");
          return;
        }

        if constexpr (!Rinegine::Kernel::Util::has_trivial_destructor_v<type>) {
          data()[current_size - 1].~type();
        }

        RawArray::size -= sizeof(type);
      }


      //[[DESTRUCT]]
      void clear() noexcept {
        if constexpr (!Rinegine::Kernel::Util::has_trivial_destructor_v<type>) {
          size_t current_size = size();
          for (size_t i = 0; i < current_size; ++i) {
            data()[i].~type();
          }
        }
        RawArray::size = 0;
      }
      ~Array() {
        if constexpr (!Rinegine::Kernel::Util::has_trivial_destructor_v<type>) {
          size_t current_size = size();
          for (size_t i = 0; i < current_size; ++i) {
            data()[i].~type();
          }
        }
      }
    };
  }
}