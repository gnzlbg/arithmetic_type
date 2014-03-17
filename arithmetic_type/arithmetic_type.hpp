#ifndef BOOST_UTILITIES_ARITHMETIC_TYPE_
#define BOOST_UTILITIES_ARITHMETIC_TYPE_
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <limits>
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
////////////////////////////////////////////////////////////////////////////////
namespace boost {
////////////////////////////////////////////////////////////////////////////////

/// \name Index types
///@{
/// \brief Implements an integer type
template <class T, class B = void> struct Arithmetic {
  using value_type = T;

  /// \name Asignment operators
  ///@{
  constexpr Arithmetic() noexcept : value(T{}) {}
  constexpr Arithmetic(const Arithmetic& other) noexcept : value(other.value) {}
  constexpr Arithmetic(Arithmetic&& other) noexcept : value(other.value) {}
  constexpr explicit Arithmetic(const T& other) noexcept : value(other) {}

  constexpr inline Arithmetic& operator=(const Arithmetic& other) noexcept {
    value = other.value;
    return *this;
  }
  constexpr inline Arithmetic& operator=(Arithmetic&& other) noexcept {
    value = other.value;
    return *this;
  }
  constexpr inline Arithmetic& operator=(const T& other) noexcept {
    value = other;
    return *this;
  }
  ///@}

  /// \name Conversion operators
  ///@{

  explicit constexpr inline operator T() noexcept { return value; }
  explicit constexpr inline operator const T() const noexcept { return value; }

  ///@}

  /// \name Compound assignment +=, -=, *=, /=
  ///@{
  constexpr inline Arithmetic& operator+=(const Arithmetic& other) noexcept {
    value += other.value;
    return *this;
  }
  constexpr inline Arithmetic& operator-=(const Arithmetic& other) noexcept {
    value -= other.value;
    return *this;
  }
  constexpr inline Arithmetic& operator*=(const Arithmetic& other) noexcept {
    value *= other.value;
    return *this;
  }
  constexpr inline Arithmetic& operator/=(const Arithmetic& other) noexcept {
    value /= other.value;
    return *this;
  }
  ///@}

  /// \name Arithmetic operators +,-,*,/,unary -
  ///@{
  constexpr friend inline Arithmetic operator+(Arithmetic a,
                                               const Arithmetic& b) noexcept {
    return a += b;
  }
  constexpr friend inline Arithmetic operator-(Arithmetic a,
                                               const Arithmetic& b) noexcept {
    return a -= b;
  }
  constexpr friend inline Arithmetic operator*(Arithmetic a,
                                               const Arithmetic& b) noexcept {
    return a *= b;
  }
  constexpr friend inline Arithmetic operator/(Arithmetic a,
                                               const Arithmetic& b) noexcept {
    return a /= b;
  }

  constexpr inline Arithmetic operator-() noexcept {
    static_assert(std::is_signed<T>::value, "Can't negate an unsigned type!");
    return Arithmetic{-value};
  }
  ///@}

  /// \name Prefix increment operators ++(),--()
  ///@{
  constexpr inline Arithmetic& operator++() noexcept {
    ++value;
    return *this;
  }
  constexpr inline Arithmetic& operator--() noexcept {
    --value;
    return *this;
  }
  ///@}

  /// \name Postfix increment operators ()++,()--
  ///@{
  constexpr inline Arithmetic operator++(int) noexcept {
    Arithmetic tmp(*this);
    ++(*this);
    return tmp;
  }
  constexpr inline Arithmetic operator--(int) noexcept {
    Arithmetic tmp(*this);
    --(*this);
    return tmp;
  }
  ///@}

  /// \name Comparison operators ==, !=, <, >, <=, >=
  ///@{
  constexpr friend inline bool operator==(const Arithmetic& a,
                                          const Arithmetic& b) noexcept {
    return a.value == b.value;
  }
  constexpr friend inline bool operator<=(const Arithmetic& a,
                                          const Arithmetic& b) noexcept {
    return a.value <= b.value;
  }
  constexpr friend inline bool operator<(const Arithmetic& a,
                                         const Arithmetic& b) noexcept {
    return a.value < b.value;
  }  // return a <= b && !(a == b) -> slower?
  constexpr friend inline bool operator!=(const Arithmetic& a,
                                          const Arithmetic& b) noexcept {
    return !(a == b);
  }
  constexpr friend inline bool operator>(const Arithmetic& a,
                                         const Arithmetic& b) noexcept {
    return !(a <= b);
  }
  constexpr friend inline bool operator>=(const Arithmetic& a,
                                          const Arithmetic& b) noexcept {
    return !(a < b);
  }
  ///@}

  /// \brief swap
  constexpr friend inline void swap(Arithmetic&& a, Arithmetic&& b) noexcept {
    using std::swap;
    swap(a.value, b.value);
  }

  /// \brief to_string
  friend inline std::string to_string(const Arithmetic a) {
    return std::to_string(a.value);
  }

  /// \name Access operator
  ///@{
  constexpr inline T& operator()() noexcept { return value; }
  constexpr inline T operator()() const noexcept { return value; }
  ///@}

  T value;

  template <class C, class CT>
  friend inline std::basic_ostream<C, CT>& operator<<(
      std::basic_ostream<C, CT>& o, const Arithmetic<T, B>& i) {
    return o << i();
  }
};
///@}

////////////////////////////////////////////////////////////////////////////////
}  // namespace boost
////////////////////////////////////////////////////////////////////////////////

namespace std {

template <class T, class B>
class numeric_limits<boost::Arithmetic<T, B>> : public numeric_limits<T> {
 public:
  static const bool is_specialized = true;
};

}  // namespace std

////////////////////////////////////////////////////////////////////////////////
#endif