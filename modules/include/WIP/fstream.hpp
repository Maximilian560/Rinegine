#pragma once
#include <fcntl.h>
namespace Rinegine::Kernel {
  namespace File {
    enum FLAG : uint32_t {
      READ = 1 << 0,   // Читать
      WRITE = 1 << 1,   // Писать
      CREATE = 1 << 2,   // Создать если нет
      APPEND = 1 << 3,   // Дописывать в конец
      TRUNC = 1 << 4,   // Очистить если существует
      BINARY = 1 << 5,   // Бинарный режим (только Windows, на Linux игнор)
    };
    // ОБЩЕЕ — не зависит от ОС
    static Rinegine::Kernel::Stream open(const char* path, uint32_t flags);
    static Rinegine::Kernel::StreamResult read_raw(void* handle, void* dst, size_t len);
    static Rinegine::Kernel::StreamResult write_raw(void* handle, const void* src, size_t len);
    static int close(void* handle);
    static int seek(void* handle, int64_t offset, int origin);
    static int64_t tell(void* handle);
    static int64_t size(void* handle);
    inline const StreamOps ops = { .read_raw = read_raw,.write_raw = write_raw,.close = close,.seek = seek,.tell = tell,.size = size };
    // ПЛАТФОРМЕННОЕ — разное на Linux/Windows
#if defined(__linux__) || defined(__ANDROID__)
    // read_raw, write_raw, open
    Stream open(const char* path, uint32_t flags) {
      int os_flags = 0;

      // Транслируем наши флаги → POSIX флаги
      if ((flags & File::FLAG::READ) && (flags & File::FLAG::WRITE))
        os_flags = O_RDWR;
      else if (flags & File::FLAG::READ)
        os_flags = O_RDONLY;
      else if (flags & File::FLAG::WRITE)
        os_flags = O_WRONLY;

      if (flags & File::FLAG::CREATE)  os_flags |= O_CREAT;
      if (flags & File::FLAG::TRUNC)   os_flags |= O_TRUNC;
      if (flags & File::FLAG::APPEND)  os_flags |= O_APPEND;

      // Открываем
      int fd = ::open(path, os_flags, 0644);  // 0644 = права для нового файла
      if (fd < 0) {
        Stream s{};
        Flags::set(s.flags, STREAM_ERROR);
        return s;
      }

      // Собираем Stream
      Stream s;
      s.handle = (void*)(intptr_t)fd;
      s.flags = 0;
      if (flags & File::FLAG::READ)  Flags::set(s.flags, STREAM_READABLE);
      if (flags & File::FLAG::WRITE) Flags::set(s.flags, STREAM_WRITABLE);
      s.buffer = nullptr;
      s.ops = &ops;
      return s;
    }
    static StreamResult read_raw(void* handle, void* dst, size_t len) {
      int fd = (int)(intptr_t)handle;
      ssize_t r = ::read(fd, dst, len);
      if (r < 0) return { 0, -1 };       // ошибка ОС
      return { (size_t)r, 0 };            // прочитали r байт (может быть < len — EOF)
    }

    static StreamResult write_raw(void* handle, const void* src, size_t len) {
      int fd = (int)(intptr_t)handle;
      ssize_t r = ::write(fd, src, len);
      if (r < 0) return { 0, -1 };
      return { (size_t)r, 0 };
    }
    static int close(void* handle) {
      int fd = (int)(intptr_t)handle;
      return ::close(fd);    // 0 = успех, -1 = ошибка
    }
    static int seek(void* handle, int64_t offset, int origin) {
      int fd = (int)(intptr_t)handle;
      int whence = (origin == 0) ? SEEK_SET : (origin == 1) ? SEEK_CUR : SEEK_END;
      return (::lseek(fd, offset, whence) == -1) ? -1 : 0;
    }
    static int64_t tell(void* handle) {
      int fd = (int)(intptr_t)handle;
      return (int64_t)::lseek(fd, 0, SEEK_CUR);
    }
    static int64_t size(void* handle) {
      int fd = (int)(intptr_t)handle;
      // Сохраняем текущую позицию
      int64_t cur = ::lseek(fd, 0, SEEK_CUR);
      // Идём в конец, узнаём позицию
      int64_t end = ::lseek(fd, 0, SEEK_END);
      // Возвращаемся обратно
      ::lseek(fd, cur, SEEK_SET);
      return end;
    }

#elif defined(_WIN32)
    inline constexpr FLAG operator~(FLAG f) noexcept {
      return static_cast<FLAG>(~static_cast<unsigned>(f));
    }

    // Разрешаем побитовое И
    inline constexpr unsigned operator&(FLAG lhs, FLAG rhs) noexcept {
      return static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs);
    }

    // Разрешаем побитовое ИЛИ
    inline constexpr unsigned operator|(FLAG lhs, FLAG rhs) noexcept {
      return static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs);
    }

    // Разрешаем побитовое исключающее ИЛИ
    inline constexpr unsigned operator^(FLAG lhs, FLAG rhs) noexcept {
      return static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs);
    }

    // Разрешаем &=
    inline constexpr FLAG& operator&=(FLAG& lhs, FLAG rhs) noexcept {
      return lhs = static_cast<FLAG>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
    }

    // Разрешаем |=
    inline constexpr FLAG& operator|=(FLAG& lhs, FLAG rhs) noexcept {
      return lhs = static_cast<FLAG>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
    }
    inline constexpr unsigned operator&(unsigned lhs, FLAG rhs) noexcept { return lhs & static_cast<unsigned>(rhs); }
    inline constexpr unsigned operator&(FLAG lhs, unsigned rhs) noexcept { return static_cast<unsigned>(lhs) & rhs; }
    inline constexpr unsigned operator|(unsigned lhs, FLAG rhs) noexcept { return lhs | static_cast<unsigned>(rhs); }
    inline constexpr unsigned operator|(FLAG lhs, unsigned rhs) noexcept { return static_cast<unsigned>(lhs) | rhs; }
    inline constexpr FLAG& operator&=(FLAG& lhs, unsigned rhs) noexcept { return lhs = static_cast<FLAG>(static_cast<unsigned>(lhs) & rhs); }
    inline constexpr FLAG& operator|=(FLAG& lhs, unsigned rhs) noexcept { return lhs = static_cast<FLAG>(static_cast<unsigned>(lhs) | rhs); }

    // read_raw, write_raw, open
    Stream open(const char* path, uint32_t flags) {
      DWORD access = 0;
      if (flags & File::FLAG::READ)  access |= GENERIC_READ;
      if (flags & File::FLAG::WRITE) access |= GENERIC_WRITE;

      DWORD disposition = OPEN_EXISTING;
      if (flags & File::FLAG::CREATE && flags & File::FLAG::TRUNC)
        disposition = CREATE_ALWAYS;         // всегда новый
      else if (flags & File::FLAG::CREATE)
        disposition = OPEN_ALWAYS;           // открыть или создать
      else if (flags & File::FLAG::WRITE)
        disposition = TRUNCATE_EXISTING;     // очистить

      HANDLE h = CreateFileA(path, access, FILE_SHARE_READ, nullptr,
        disposition, FILE_ATTRIBUTE_NORMAL, nullptr);
      if (h == INVALID_HANDLE_VALUE) {
        Stream s{};
        Flags::set(s.flags, STREAM_ERROR);
        return s;
      }

      Stream s;
      s.handle = h;
      s.flags = 0;
      if (flags & File::FLAG::READ)  Flags::set(s.flags, STREAM_READABLE);
      if (flags & File::FLAG::WRITE) Flags::set(s.flags, STREAM_WRITABLE);
      s.buffer = nullptr;
      s.ops = &ops;
      return s;
    }
    static StreamResult read_raw(void* handle, void* dst, size_t len) {
      DWORD rd = 0;
      BOOL ok = ReadFile((HANDLE)handle, dst, (DWORD)len, &rd, nullptr);
      if (!ok) return { 0, -1 };
      return { (size_t)rd, 0 };
    }

    static StreamResult write_raw(void* handle, const void* src, size_t len) {
      DWORD wr = 0;
      BOOL ok = WriteFile((HANDLE)handle, src, (DWORD)len, &wr, nullptr);
      if (!ok) return { 0, -1 };
      return { (size_t)wr, 0 };
    }
    static int close(void* handle) {
      HANDLE h = (HANDLE)handle;
      return CloseHandle(h) ? 0 : -1;
    }
    static int seek(void* handle, int64_t offset, int origin) {
      LARGE_INTEGER li;
      li.QuadPart = offset;
      DWORD move = (origin == 0) ? FILE_BEGIN : (origin == 1) ? FILE_CURRENT : FILE_END;
      return SetFilePointerEx((HANDLE)handle, li, nullptr, move) ? 0 : -1;
    }
    static int64_t tell(void* handle) {
      LARGE_INTEGER pos;
      // if (!SetFilePointerEx((HANDLE)handle, { 0 }, &pos, FILE_CURRENT)) return -1;
      if (!SetFilePointerEx((HANDLE)handle, LARGE_INTEGER{ 0, 0 }, &pos, FILE_CURRENT)) return -1;
      return pos.QuadPart;
    }
    static int64_t size(void* handle) {
      LARGE_INTEGER sz;
      if (!GetFileSizeEx((HANDLE)handle, &sz)) return -1;
      return sz.QuadPart;
    }

#endif

    // ОБЩЕЕ — использует платформенные функции
    // inline const StreamOps ops = { ... };
    // Stream open(const char* path, uint32_t flags);
  }
}