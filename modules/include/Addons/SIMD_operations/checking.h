#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/SIMD_op-check"
namespace RG {
  namespace Checking {
    bool cpu_supports_avx() {
      static char support = -1;
      if (support >= 0) return support;
      int info[4];
      __cpuid(info, 1);
      bool hwAvx = (info[2] & (1 << 28)) != 0; // ECX bit 28

      // Проверяем, что ОС поддерживает XSAVE/XRESTORE и AVX-зоны
      bool osUsesXsave = (info[2] & (1 << 27)) != 0; // OSXSAVE
      if (!hwAvx || !osUsesXsave) return false;

      // читаем XCR0, проверяем биты 1 (SSE) и 2 (AVX)
      unsigned long long xcr0 = _xgetbv(0);
      support = ((xcr0 & 0x6) == 0x6);
      return support;
    }

    bool cpu_supports_avx2() {
      if (!cpu_supports_avx()) return false;
      static char support = -1;
      if (support >= 0) return support;
      int info[4];
      __cpuidex(info, 7, 0);
      support = (info[1] & (1 << 5)) != 0; // EBX bit 5
      return support;
    }

  }
}