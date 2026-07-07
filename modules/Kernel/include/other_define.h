#pragma once


// debug




namespace Rinegine {

  // Чистый интерфейс — пользователь видит ТОЛЬКО это
  int TryCatch(std::function<void()> func);

} // namespace Rinegine

// Макросы остаются, но ТОЛЬКО как обёртка
#define RG_CATCH_ERROR return Rinegine::TryCatch([&]() {
#define RG_ERROR_LOG  });

#ifndef RinegineLib
namespace Rinegine {
#ifdef RG_UTF
  std::vector<std::wstring>& MainArguments = Kernel::WMainArguments; //TODO remove vector, set RG::Array!
#else
  std::vector<std::string>& MainArguments = Kernel::AMainArguments; //TODO remove vector, set RG::Array!
#endif
}
#endif