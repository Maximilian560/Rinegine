#pragma once

#ifndef _GLIBCXX_NOEXCEPT
#  define _GLIBCXX_NOEXCEPT noexcept
#endif
#ifndef _GLIBCXX_NOEXCEPT_PARM
#  define _GLIBCXX_NOEXCEPT_PARM
#endif
#ifndef _GLIBCXX_NOEXCEPT_QUAL
#  define _GLIBCXX_NOEXCEPT_QUAL noexcept
#endif
#ifndef _GLIBCXX_CONSTEXPR
#  define _GLIBCXX_CONSTEXPR constexpr
#endif
#ifndef _GLIBCXX17_CONSTEXPR
#  define _GLIBCXX17_CONSTEXPR constexpr
#endif
#ifndef _GLIBCXX_USE_NOEXCEPT
#  define _GLIBCXX_USE_NOEXCEPT noexcept
#endif
namespace Rinegine::Kernel::Util {
#if defined(__clang__) && __has_builtin(__is_trivially_destructible)
#  undef __has_trivial_destructor
#  define __has_trivial_destructor(T) __is_trivially_destructible(T)
#endif
  // Тривиальный конструктор
  template<typename T, typename... Args>
  struct is_trivially_constructible {
    static constexpr bool value = __is_trivially_constructible(T, Args...);
  };
  template<typename T, typename... Args>
  inline constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;

  // Тривиальный тип (POD — memcpy безопасен)
  template<typename T>
  struct is_trivial {
    static constexpr bool value = __is_trivial(T);
  };
  template<typename T>
  inline constexpr bool is_trivial_v = is_trivial<T>::value;

  // Тривиальный деструктор (без ~T())
  template<typename T>
  struct has_trivial_destructor {
    static constexpr bool value = __has_trivial_destructor(T);
  };
  template<typename T>
  inline constexpr bool has_trivial_destructor_v = has_trivial_destructor<T>::value;

  template<typename T>
  __attribute__((__always_inline__))
    inline _GLIBCXX_CONSTEXPR T*
    __addressof(T& __r) _GLIBCXX_NOEXCEPT
  {
    return __builtin_addressof(__r);
  }

  template<typename _Tp>
  [[__nodiscard__, __gnu__::__always_inline__]]
  inline _GLIBCXX17_CONSTEXPR _Tp*
    addressof(_Tp& __r) noexcept
  {
    return __addressof(__r);
  }
}