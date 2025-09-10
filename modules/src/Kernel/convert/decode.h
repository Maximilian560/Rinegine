#pragma once

namespace Rinegine {
char *Kernel::itoa(int value, int base, char *result) {
  // check that the base if valid
  if (result == nullptr) {
    if (value > base) {
      // TODO ERROR HERE!!!
      return nullptr;
    }
  }
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
             "uvwxyz"[35 + (tmp_value - value * base)];
  } while (value);

  // Apply negative sign
  if (tmp_value < 0)
    *ptr++ = '-';
  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}
std::string Kernel::itos(long long int value, long long int base) {
  std::string buf;
  // check that the base if valid
  if (base < 2 || base > 36)
    return buf;

  enum { kMaxDigits = 35 };
  buf.reserve(kMaxDigits); // Pre-allocate enough space.

  long long int quotient = value;

  // Translating number to string with base:
  do {
    buf += "0123456789abcdefghijklmnopqrstuvwxyz"[std::abs(quotient % base)];
    quotient /= base;
  } while (quotient);

  // Append the negative sign
  if (value < 0)
    buf += '-';
  for (size_t i = 0; i < buf.size() / 2; i++) {
    std::swap(buf[i], buf[buf.size() - 1 - i]);
  }
  return buf;
}
std::string Kernel::itos(size_t value, size_t base) {
  std::string buf;
  // check that the base if valid
  if (base < 2 || base > 36)
    return buf;

  enum { kMaxDigits = 35 };
  buf.reserve(kMaxDigits); // Pre-allocate enough space.

  size_t quotient = value;

  // Translating number to string with base:
  do {
    buf += "0123456789abcdefghijklmnopqrstuvwxyz"[quotient % base];
    quotient /= base;
  } while (quotient);

  // Append the negative sign
  for (size_t i = 0; i < buf.size() / 2; i++) {
    std::swap(buf[i], buf[buf.size() - 1 - i]);
  }
  return buf;
}
std::wstring Kernel::itows(long long int value, long long int base) {

  std::wstring buf;

  // check that the base if valid
  if (base < 2 || base > 36)
    return buf;

  enum { kMaxDigits = 35 };
  buf.reserve(kMaxDigits); // Pre-allocate enough space.

  long long int quotient = value;

  // Translating number to string with base:
  do {
    buf += L"0123456789abcdefghijklmnopqrstuvwxyz"[std::abs(quotient % base)];
    quotient /= base;
  } while (quotient);

  // Append the negative sign
  if (value < 0)
    buf += '-';

  for (size_t i = 0; i < buf.size() / 2; i++) {
    wchar_t temp = buf[i];
    buf[i] = buf[buf.size() - 1 - i];
    buf[buf.size() - 1] = temp;
  }
  return buf;
}
std::wstring Kernel::itows(size_t value, size_t base) {

  std::wstring buf;

  // check that the base if valid
  if (base < 2 || base > 36)
    return buf;

  enum { kMaxDigits = 35 };
  buf.reserve(kMaxDigits); // Pre-allocate enough space.

  size_t quotient = value;

  // Translating number to string with base:
  do {
    buf += L"0123456789abcdefghijklmnopqrstuvwxyz"[quotient % base];
    quotient /= base;
  } while (quotient);

  // Append the negative sign

  for (size_t i = 0; i < buf.size() / 2; i++) {
    wchar_t temp = buf[i];
    buf[i] = buf[buf.size() - 1 - i];
    buf[buf.size() - 1] = temp;
  }
  return buf;
}
}