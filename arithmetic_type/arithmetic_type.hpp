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
  constexpr Arithmetic() noexcept(T{T{}}) : value{T{}} {}
  constexpr Arithmetic(const Arithmetic& other) noexcept(T{T{}})
    : value{other.value} {}
  constexpr Arithmetic(Arithmetic&& other) noexcept(T{T{}})
    : value{other.value} {}
  constexpr explicit Arithmetic(const T& other) noexcept(T{T{}})
    : value{other} {}
  template <class U, class V>
  constexpr explicit Arithmetic(const Arithmetic<U, V>& other) noexcept(T{T{}})
    : value(other.value) {}

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

  template <class U, class V>
  explicit constexpr inline operator Arithmetic<U, V>() noexcept {
    return value;
  }

  template <class U, class V>
  explicit constexpr inline operator const Arithmetic<U, V>() const noexcept {
    return value;
  }
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

  /// \name Access operator
  ///@{
  constexpr inline T& operator()() & noexcept { return value; }
  constexpr inline T operator()() && noexcept { return value; }
  constexpr inline T operator()() const& noexcept { return value; }
  ///@}

  /// Data (wrapped value):
  T value;
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
#endif  // BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TYPE_
