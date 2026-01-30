#pragma once

//_UNICODE

#ifndef RinegineLib
int rg_main();
#ifdef RG_UTF
int wmain(int argc, wchar_t *argv[]) {
  return Rinegine::Kernel::InterPoint(argc, argv, rg_main);
}
#else
int main(int argc, char *argv[]) {
  return Rinegine::Kernel::InterPoint(argc, argv, rg_main);
}
#endif
#endif