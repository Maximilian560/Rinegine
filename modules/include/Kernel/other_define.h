#pragma once
// debug




namespace Rinegine {

// Чистый интерфейс — пользователь видит ТОЛЬКО это
int TryCatch(std::function<void()> func);

} // namespace Rinegine

// Макросы остаются, но ТОЛЬКО как обёртка
#define RG_CATCH_ERROR return Rinegine::TryCatch([&]() {
#define RG_ERROR_LOG  });