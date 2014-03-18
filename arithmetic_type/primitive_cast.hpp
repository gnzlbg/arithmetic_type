#ifndef ARITHMETIC_UTILITIES_ARITHMETIC_TYPE_PRIMITIVE_CAST_
#define ARITHMETIC_UTILITIES_ARITHMETIC_TYPE_PRIMITIVE_CAST_
////////////////////////////////////////////////////////////////////////////////
#include "arithmetic_type/traits.hpp"
////////////////////////////////////////////////////////////////////////////////

namespace arithmetic {

namespace detail_ {
enum class enabler {};
constexpr enabler dummy = {};

template <class C, class T = enabler>
using EnableIf = std::enable_if_t<C::value, T>;

template <class C, class T = enabler>
using DisableIf = std::enable_if_t<!(C::value), T>;

}  // namespace detail_

template <class T, detail_::EnableIf<is_arithmetic<T>> = detail_::dummy>
constexpr inline auto&& primitive_cast(T&& t) {
  static_assert(is_arithmetic<T>::value, "T must be an integer!");
  return t();
}

template <class T, detail_::EnableIf<is_arithmetic<T>> = detail_::dummy>
constexpr inline auto primitive_cast(const T& t) -> decltype(t()) {
  static_assert(is_arithmetic<T>::value, "T must be an integer!");
  return t();
}

template <class T, detail_::EnableIf<is_arithmetic<T>> = detail_::dummy>
constexpr inline auto& primitive_cast(T& t) {
  static_assert(is_arithmetic<T>::value, "T must be an integer!");
  return t();
}

template <class T, detail_::DisableIf<is_arithmetic<T>> = detail_::dummy>
constexpr inline auto&& primitive_cast(T&& t) {
  static_assert(!is_arithmetic<T>::value, "T can't be an integer!");
  return std::forward<T>(t);
}

template <class T, detail_::DisableIf<is_arithmetic<T>> = detail_::dummy>
constexpr inline auto primitive_cast(const T& t) -> decltype(t) {
  static_assert(!is_arithmetic<T>::value, "T can't be an integer!");
  return t;
}

template <class T, detail_::DisableIf<is_arithmetic<T>> = detail_::dummy>
constexpr inline auto& primitive_cast(T& t) {
  static_assert(!is_arithmetic<T>::value, "T can't be an integer!");
  return t;
}

}  // namespace arithmetic

////////////////////////////////////////////////////////////////////////////////
#endif  // ARITHMETIC_UTILITIES_ARITHMETIC_TYPE_PRIMITIVE_CAST_
