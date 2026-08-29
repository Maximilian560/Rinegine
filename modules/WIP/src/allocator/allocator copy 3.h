#pragma once

namespace Rinegine {
  const size_t Kernel::Lock::page_size = getpagesize();

  namespace Lock {
    inline static std::atomic_ullong MemUsed = 0;
    static int Magic_Num = 8 + (sizeof(size_t));//todo, i guese it shuld be removed
  }
  

}