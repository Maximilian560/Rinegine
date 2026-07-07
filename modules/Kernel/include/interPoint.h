#pragma once


#ifndef RinegineLib
#ifdef RG_UTF
int wmain(int argc, wchar_t *argv[]) {
  return Rinegine::Kernel::InterPoint(argc, argv, Rinegine::Kernel::rg_main);
}
#else
int main(int argc, char *argv[]) {
  return Rinegine::Kernel::InterPoint(argc, argv, Rinegine::Kernel::rg_main);
}
#endif
#endif