#pragma once
namespace Rinegine::Kernel {

  namespace Console {

    // ===== ОБЩЕЕ ДЛЯ ВСЕХ =====
    static int close(void* handle) {
      (void)handle;
      return 0;
    }

    // ===== ПЛАТФОРМЕННАЯ ЧАСТЬ =====
#if defined(__linux__) || defined(__ANDROID__)

    static StreamResult write_raw(void* handle, const void* src, size_t len) {
      int fd = (int)(intptr_t)handle;
      ssize_t r = ::write(fd, src, len);
      if (r < 0) return { 0, -1 };
      return { (size_t)r, 0 };
    }
    static StreamResult read_raw(void* handle, void* dst, size_t len) {
      int fd = (int)(intptr_t)handle;
      ssize_t r = ::read(fd, dst, len);
      if (r < 0) return { 0, -1 };
      return { (size_t)r, 0 };
    }
    static void* get_stdin_handle() { return (void*)(intptr_t)0; }
    static void* get_stdout_handle() { return (void*)(intptr_t)1; }
    static void* get_stderr_handle() { return (void*)(intptr_t)2; }

#elif defined(_WIN32)

    static StreamResult write_raw(void* handle, const void* src, size_t len) {
      DWORD written = 0;
      BOOL ok = WriteFile((HANDLE)handle, src, (DWORD)len, &written, nullptr);
      if (!ok) return { 0, -1 };
      return { (size_t)written, 0 };
    }
    static StreamResult read_raw(void* handle, void* dst, size_t len) {
      DWORD rd = 0;
      BOOL ok = ReadFile((HANDLE)handle, dst, (DWORD)len, &rd, nullptr);
      if (!ok) return { 0, -1 };
      return { (size_t)rd, 0 };
    }
    static void* get_stdin_handle() { return GetStdHandle(STD_INPUT_HANDLE); }
    static void* get_stdout_handle() { return GetStdHandle(STD_OUTPUT_HANDLE); }
    static void* get_stderr_handle() { return GetStdHandle(STD_ERROR_HANDLE); }

#else

    static StreamResult write_raw(void* h, const void* s, size_t l) { (void)h; (void)s; (void)l; return { 0, -1 }; }
    static StreamResult read_raw(void* h, void* d, size_t l) { (void)h; (void)d; (void)l; return { 0, -1 }; }
    static void* get_stdin_handle() { return nullptr; }
    static void* get_stdout_handle() { return nullptr; }
    static void* get_stderr_handle() { return nullptr; }

#endif

    // ===== ОБЩЕЕ ДЛЯ ВСЕХ =====
    inline const StreamOps ops = {
      .read_raw = read_raw,
      .write_raw = write_raw,
      .close = close,
      .seek = nullptr,
      .tell = nullptr,
      .size = nullptr,
    };

    inline Stream stdin_stream() {
      Stream s;
      s.handle = get_stdin_handle();
      s.flags = STREAM_READABLE;
      s.buffer = nullptr;
      s.ops = &ops;
      return s;
    }
    inline Stream stdout_stream() {
      Stream s;
      s.handle = get_stdout_handle();
      s.flags = STREAM_WRITABLE;
      s.buffer = nullptr;
      s.ops = &ops;
      return s;
    }
    inline Stream stderr_stream() {
      Stream s;
      s.handle = get_stderr_handle();
      s.flags = STREAM_WRITABLE;
      s.buffer = nullptr;
      s.ops = &ops;
      return s;
    }

  }
}