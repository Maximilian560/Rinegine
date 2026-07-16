#pragma once

namespace Rinegine::Kernel {
  // Объявляем слабую функцию. Компилятор Clang разрешает такое в .a либе.
  __attribute__((weak)) void EarlyInit(); 
}

namespace Rinegine::Kernel {
  __attribute__((constructor(101)))
  static void EarlyInitCall() {
    if (Rinegine::Kernel::EarlyInit != nullptr) {
      Rinegine::Kernel::EarlyInit();
    }
  }
}