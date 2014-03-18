#ifndef BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TYPE_
#define BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TYPE_
////////////////////////////////////////////////////////////////////////////////
#include <limits>
#include <type_traits>
////////////////////////////////////////////////////////////////////////////////
namespace boost {
////////////////////////////////////////////////////////////////////////////////

/// \name Index types
///@{
/// \brief Implements an integer type
template <class T, class B = void> struct Arithmetic {
  using value_type = T;
  using type = T;

  /// \name Asignment operators
  ///@{
  constexpr Arithmetic() = default;
  constexpr Arithmetic(const Arithmetic& other) = default;
  constexpr Arithmetic(Arithmetic&& other) = default;
  constexpr Arithmetic& operator=(const Arithmetic& other) = default;
  constexpr Arithmetic& operator=(Arithmetic&& other) = default;

  constexpr explicit Arithmetic(const T& other) noexcept(
      std::is_nothrow_constructible<T>::value)
    : value{other} {}
  template <class U, class V>
  constexpr explicit Arithmetic(const Arithmetic<U, V>& other) noexcept(
      std::is_nothrow_constructible<T>::value)
    : value(other.value) {}
  constexpr Arithmetic& operator=(const T& other) noexcept {
    value = other;
    return *this;
  }
  ///@}

  /// \name Conversion operators
  ///@{
  explicit constexpr operator T() noexcept { return value; }
  explicit constexpr operator const T() const noexcept { return value; }

  template <class U, class V>
  explicit constexpr operator Arithmetic<U, V>() noexcept {
    return value;
  }

  template <class U, class V>
  explicit constexpr operator const Arithmetic<U, V>() const noexcept {
    return value;
  }
  ///@}

  /// \name Compound assignment +=, -=, *=, /=
  ///@{
  constexpr Arithmetic& operator+=(const Arithmetic& other) noexcept {
    value += other.value;
    return *this;
  }
  constexpr Arithmetic& operator-=(const Arithmetic& other) noexcept {
    value -= other.value;
    return *this;
  }
  constexpr Arithmetic& operator*=(const Arithmetic& other) noexcept {
    value *= other.value;
    return *this;
  }
  constexpr Arithmetic& operator/=(const Arithmetic& other) noexcept {
    value /= other.value;
    return *this;
  }
  ///@}

  /// \name Prefix increment operators ++(),--()
  ///@{
  constexpr Arithmetic& operator++() noexcept {
    ++value;
    return *this;
  }
  constexpr Arithmetic& operator--() noexcept {
    --value;
    return *this;
  }
  ///@}

  /// \name Postfix increment operators ()++,()--
  ///@{
  constexpr Arithmetic operator++(int) noexcept {
    Arithmetic tmp(*this);
    ++(*this);
    return tmp;
  }
  constexpr Arithmetic operator--(int) noexcept {
    Arithmetic tmp(*this);
    --(*this);
    return tmp;
  }
  ///@}

  /// \name Access operator
  ///@{
  constexpr T& operator()() & noexcept { return value; }
  constexpr T operator()() && noexcept { return value; }
  constexpr T operator()() const& noexcept { return value; }
  ///@}

  /// Data (wrapped value):
  T value;
};
///@}

/// \brief swap
template <class T, class U>
constexpr void swap(Arithmetic<T, U>&& a, Arithmetic<T, U>&& b) noexcept {
  using std::swap;
  swap(a.value, b.value);
}

/// \name Arithmetic operators +,-,*,/,unary -
///@{
template <class T, class U>
constexpr Arithmetic<T, U> operator+(Arithmetic<T, U> a,
                                     const Arithmetic<T, U>& b) noexcept {
  return a += b;
}
template <class T, class U>
constexpr Arithmetic<T, U> operator-(Arithmetic<T, U> a,
                                     const Arithmetic<T, U>& b) noexcept {
  return a -= b;
}
template <class T, class U>
constexpr Arithmetic<T, U> operator*(Arithmetic<T, U> a,
                                     const Arithmetic<T, U>& b) noexcept {
  return a *= b;
}
template <class T, class U>
constexpr Arithmetic<T, U> operator/(Arithmetic<T, U> a,
                                     const Arithmetic<T, U>& b) noexcept {
  return a /= b;
}

template <class T, class U>
constexpr Arithmetic<T, U> operator-(Arithmetic<T, U> const& other) noexcept {
  static_assert(std::is_signed<T>::value, "Can't negate an unsigned type!");
  return Arithmetic<T, U>{-other.value};
}
///@}

/// \name Comparison operators ==, !=, <, >, <=, >=
///@{
template <class T, class U>
constexpr bool operator==(const Arithmetic<T, U>& a,
                          const Arithmetic<T, U>& b) noexcept {
  return a.value == b.value;
}
template <class T, class U>
constexpr bool operator<(const Arithmetic<T, U>& a,
                         const Arithmetic<T, U>& b) noexcept {
  return a.value < b.value;
}
template <class T, class U>
constexpr bool operator<=(const Arithmetic<T, U>& a,
                          const Arithmetic<T, U>& b) noexcept {
  return a < b || a == b;
}
template <class T, class U>
constexpr bool operator!=(const Arithmetic<T, U>& a,
                          const Arithmetic<T, U>& b) noexcept {
  return !(a == b);
}
template <class T, class U>
constexpr bool operator>(const Arithmetic<T, U>& a,
                         const Arithmetic<T, U>& b) noexcept {
  return !(a <= b);
}
template <class T, class U>
constexpr bool operator>=(const Arithmetic<T, U>& a,
                          const Arithmetic<T, U>& b) noexcept {
  return !(a < b);
}
///@}

////////////////////////////////////////////////////////////////////////////////
}  // namespace boost
////////////////////////////////////////////////////////////////////////////////

namespace std {

template <class T, class B>
class numeric_limits<boost::Arithmetic<T, B>> : public numeric_limits<T> {
 public:
  static constexpr bool is_specialized = true;
};

}  // namespace std

////////////////////////////////////////////////////////////////////////////////
#endif  // BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TYPE_
