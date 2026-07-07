#include <cstddef>
#include <cstdint>

#if defined(__linux__) || defined(__ANDROID__)
#include <unistd.h>
#include <sys/types.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

namespace Rinegine {
  namespace Kernel {

    // [Elemental Types Definition]
    template<class T1, class T2>
    struct Pair {//! [Not needed yet, later when i make a map type]
      T1 first = T1{};
      T2 second = T2{};
    };

    template<typename From, typename To>
    concept Convertible = requires(From f) {
      { To(f) };
    };
    /*namespace Flags {
      template <class T1, class T2>
      concept FlagTypeCompatible = requires(T1 val, T2 flag) {
        { val |= static_cast<T1>(flag) };
        { val &= ~static_cast<T1>(flag) };
        { (val & static_cast<T1>(flag)) != static_cast<T1>(0) };
      };
      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr void set(T1& val, T2 flag) { val |= static_cast<T1>(flag); }

      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr bool has(T1 val, T2 flag) { return (val & static_cast<T1>(flag)) != 0; }

      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr void clear(T1& val, T2 flag) { val &= ~static_cast<T1>(flag); }
    }*/
    // [Stream realization]
    enum STREAM_FLAG : uint32_t {
      STREAM_READABLE = 1 << 0,   // Поток поддерживает чтение
      STREAM_WRITABLE = 1 << 1,   // Поток поддерживает запись
      STREAM_BUFFERED = 1 << 2,   // Буферизация включена
      STREAM_OWN_BUF = 1 << 3,   // Поток владеет буфером (освободит при destroy)
      STREAM_EOF = 1 << 4,   // Достигнут конец потока
      STREAM_ERROR = 1 << 5,   // Ошибка операции
    };

    // template<size_t N>
    struct StreamResult {
      size_t bytes;
      int err;
      constexpr bool ok() const { return err == 0; }
    };
    struct StreamBuffer {
      uint8_t* data;
      size_t capacity;
      size_t write_pos;
      size_t read_pos;

      constexpr void init(uint8_t* _data, size_t _size) {
        data = _data;
        capacity = _size;
        write_pos = 0;
        read_pos = 0;
      }
      constexpr size_t space() const {
        return capacity - write_pos;
      }
      constexpr size_t available() const {
        return write_pos > read_pos ? write_pos - read_pos : 0;
      }
      constexpr size_t write(const void* src, size_t len) {
        size_t spc = space();
        size_t copy = (len < spc) ? len : spc;
        __builtin_memcpy(data + write_pos, src, copy);
        write_pos += copy;
        return copy;
      }
      constexpr size_t read(void* dst, size_t len) {
        size_t avail = available();
        size_t copy = (len < avail) ? len : avail;
        __builtin_memcpy(dst, data + read_pos, copy);
        read_pos += copy;
        return copy;
      }
      constexpr void reset_read() {
        read_pos = 0;
      }
      constexpr void clear() {
        write_pos = 0;
        read_pos = 0;
      }
      constexpr bool empty() const {
        return available() == 0;
      }
      constexpr bool full() const {
        return write_pos >= capacity;
      }
    };


    struct StreamOps {
      StreamResult(*read_raw)(void* handle, void* dst, size_t len);
      StreamResult(*write_raw)(void* handle, const void* src, size_t len);
      int          (*close)(void* handle);
      int          (*seek)(void* handle, int64_t offset, int origin);
      int64_t(*tell)(void* handle);
      int64_t(*size)(void* handle);
    };


    // [STREAM]
    struct Stream {
      void* handle;
      uint32_t flags;
      StreamBuffer* buffer;
      const StreamOps* ops;

      constexpr void init(void* _handle, const StreamOps* _ops, uint32_t _flags = 0) {
        handle = _handle;
        ops = _ops;
        flags = _flags;
        buffer = nullptr;
      }
      constexpr void set_buffer(StreamBuffer* _buffer) { buffer = _buffer; }
      constexpr StreamResult flush() {
        if (buffer == nullptr)
          return { 0,0 };

        size_t to_flush = buffer->available();
        StreamResult r = ops->write_raw(handle, buffer->data + buffer->read_pos, to_flush);
        if (r.ok())
          buffer->clear();
        else
          Flags::set(flags, STREAM_ERROR);

        return r;
      }
      constexpr StreamResult write(const void* src, size_t len) {
        // --- ПРОВЕРКИ ---
        if (!Flags::has(flags, STREAM_WRITABLE)) {
          Flags::set(flags, STREAM_ERROR);
          return { 0, -1 };
        }
        if (Flags::has(flags, STREAM_ERROR)) return { 0, -1 };
        if (!ops || !ops->write_raw) return { 0, -1 };

        // if (!buffer) return ops->write_raw(handle, src, len);
        if (!buffer) {
          StreamResult r = ops->write_raw(handle, src, len);
          if (!r.ok()) Flags::set(flags, STREAM_ERROR);
          return r;
        }

        size_t total = 0;
        const uint8_t* p = (const uint8_t*)src;
        while (total < len) {
          if (buffer->full()) {
            StreamResult r = flush();
            if (!r.ok()) return { total, r.err };
          }

          size_t copy = (len - total < buffer->space()) ? (len - total) : buffer->space();
          buffer->write(p + total, copy);
          total += copy;
        }
        return { total, 0 };
      }
      constexpr StreamResult read(void* dst, size_t len) {
        if (!Flags::has(flags, STREAM_READABLE)) {
          Flags::set(flags, STREAM_ERROR);
          return { 0, -1 };
        }
        if (Flags::has(flags, STREAM_ERROR)) return { 0, -1 };
        if (!ops || !ops->read_raw) return { 0, -1 };

        if (!buffer) {
          StreamResult r = ops->read_raw(handle, dst, len);
          if (r.bytes == 0 && r.err == 0) Flags::set(flags, STREAM_EOF);
          if (!r.ok()) Flags::set(flags, STREAM_ERROR);
          return r;
        }

        size_t total = 0;
        uint8_t* p = (uint8_t*)dst;

        while (total < len) {
          size_t avail = buffer->available();

          if (avail > 0) {
            size_t copy = (len - total < avail) ? (len - total) : avail;
            buffer->read(p + total, copy);
            total += copy;
            continue;
          }

          buffer->clear();
          StreamResult r = ops->read_raw(handle, buffer->data, buffer->capacity);

          if (!r.ok()) {
            Flags::set(flags, STREAM_ERROR);
            return { total, r.err };
          }

          if (r.bytes == 0) {
            Flags::set(flags, STREAM_EOF);
            return { total, 0 };
          }

          buffer->write_pos = r.bytes;
          buffer->read_pos = 0;
        }

        return { total, 0 };
      }
      constexpr StreamResult close_stream() {
        StreamResult r = { 0, 0 };

        if (buffer && !buffer->empty()) {
          r = flush();
        }

        if (ops && ops->close) {
          int err = ops->close(handle);
          if (err != 0 && r.ok()) r.err = err;
          else handle = nullptr;
        }
        else {
          handle = nullptr;
        }
        return r;
      }
      constexpr StreamResult seek(int64_t offset, int origin) {
        if (!ops || !ops->seek) return { 0, -1 };
        int err = ops->seek(handle, offset, origin);
        if (err != 0) {
          Flags::set(flags, STREAM_ERROR);
          return { 0, err };
        }
        Flags::clear(flags, STREAM_EOF);
        return { 0, 0 };
      }

      constexpr int64_t tell() const {
        if (!ops || !ops->tell) return -1;
        return ops->tell(handle);
      }

      constexpr int64_t size() const {
        if (!ops || !ops->size) return -1;
        return ops->size(handle);
      }
    };
  }
}