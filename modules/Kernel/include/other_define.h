#pragma once


// debug




namespace Rinegine {

  int TryCatch(std::function<void()> func);

} // namespace Rinegine

#define RG_CATCH_ERROR return Rinegine::TryCatch([&]() {
#define RG_ERROR_LOG  });

#ifndef RinegineLib
namespace Rinegine {
#ifdef RG_UTF
  Kernel::Array<std::wstring>& MainArguments = Kernel::WMainArguments; //TODO remove vector, set RG::Array!
#else
  Kernel::Array<std::string>& MainArguments = Kernel::AMainArguments; //TODO remove vector, set RG::Array!
#endif
}
#endif