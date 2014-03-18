/// \file Tests the Integer wrapper
#include "arithmetic_type/arithmetic_type.hpp"
#include "arithmetic_type/primitive_cast.hpp"
#include "arithmetic_type/arithmetic_istream.hpp"
#include "arithmetic_type/arithmetic_ostream.hpp"
#include "arithmetic_type/arithmetic_to_string.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
////////////////////////////////////////////////////////////////////////////////

using namespace boost;

template <class T> void test_unsigned_integer_increment_operators() {
  auto i1 = T{1};
  auto i2 = T{2};
  ++i1;
  REQUIRE(i1 == i2);
  auto i3 = i2;
  REQUIRE(i3 == i2++);
  REQUIRE(i2 == T{3});
  --i2;
  REQUIRE(i2 == i1);
  auto i4 = i1;
  REQUIRE(i4 == i1--);
}

template <class T> void test_comparison_operators() {
  auto a = T{2};
  auto b = T{3};
  auto c = T{5};
  auto d = T{1};
  REQUIRE((a + b) == c);
  REQUIRE(a < b);
  REQUIRE(a <= b);
  REQUIRE(b <= b);
  REQUIRE(b >= b);
  REQUIRE(b > a);
  REQUIRE(b >= a);
  REQUIRE(b == b);
  REQUIRE(b != a);
  REQUIRE((b - a) == d);
  REQUIRE((a * b) == (c + d));

  auto a_old = a;
  a += b;
  REQUIRE(a == c);
  b -= a_old;
  REQUIRE(b == d);
}

template <class T> void test_integer_compound_assignment() {
  auto i1 = T{1};
  auto i2 = T{2};
  i1 += i1;
  REQUIRE(i1 == i2);
  i2 -= i2;
  REQUIRE(i2 == T{0});
  i1 *= T{2};
  REQUIRE(i1 == T{4});
  i1 /= T{2};
  REQUIRE(i1 == T{2});
}

template <class T> void test_unsigned_integer_arithmetic() {
  auto i1 = T{1};
  auto i2 = i1 + i1 + i1;
  auto i3 = i1 * T{3};
  REQUIRE(i2 == i3);
  REQUIRE((i3 / i2) == T{1});
  auto i4 = i3 - T{2} * i1;
  REQUIRE(i4 == i1);
}

template <class T> void static_assert_noexcept_constructors() {
  Arithmetic<T> a{};
  const Arithmetic<T> b{};
  static_assert(noexcept(Arithmetic<T>{}),
                "error: arithmetic default constructor is noexcept(false)");
  static_assert(noexcept(Arithmetic<T>{Arithmetic<T>{}}),
                "error: arithmetic move constructor is noexcept(false)");
  static_assert(noexcept(Arithmetic<T>{a}),
                "error: arithmetic copy constructor is noexcept(false)");
  static_assert(noexcept(Arithmetic<T>{b}),
                "error: arithmetic copy constructor is noexcept(false)");
  static_assert(noexcept(a = b),
                "error: arithmetic copy assignment is noexcept(false)");
  static_assert(noexcept(a = Arithmetic<T>{}),
                "error: arithmetic move assignment is noexcept(false)");
  static_assert(
      noexcept(Arithmetic<long double>{a}),
      "error: arithmetic generic copy constructor is noexcept(false)");
}

template <class T> constexpr Arithmetic<T> test_constexpr() {
  Arithmetic<T> a{0};
  a++;
  ++a;
  a *= Arithmetic<T>{2};
  --a;
  a--;
  return a;
}

TEST_CASE("Test arithmetic type docs", "[arithmetic_type]") {
  SECTION("Example 1a") {
    int a{2};
    long b{3};
    b = a;  // works: the implicit conversion is safe
  }

  SECTION("Example 1b") {
    Arithmetic<int> a{2};
    Arithmetic<long> b{3};
    // b = a;  // error: implicit assignment requires implicit conversion
    static_assert(!std::is_assignable<Arithmetic<int>, Arithmetic<long>>::value,
                  "implicit assignment not allowed");
    static_assert(
        !std::is_convertible<Arithmetic<int>, Arithmetic<long>>::value,
        "implicit conversion not allowed");

    b = Arithmetic<long>{a};               // works: explicit construction
    b = static_cast<Arithmetic<long>>(a);  // works: explicit conversion
  }

  SECTION("Example 2") {
    struct Tag1 {};
    struct Tag2 {};

    using Type1 = Arithmetic<int, Tag1>;
    using Type2 = Arithmetic<int, Tag2>;
    Type1 a{2};
    Type2 b{3};
    // b = a; // compilation error: implicit conversion
    static_assert(!std::is_assignable<Type1, Type2>::value,
                  "implicit assignment not allowed");
    static_assert(!std::is_convertible<Type1, Type2>::value,
                  "implicit conversion not allowed");
    b = Type2{a};               // works: explicit construction
    b = static_cast<Type2>(a);  // works: explicit conversion
    Type2 c{a};                 // works: explicit construction
  }
}

TEST_CASE("Test arithmetic type", "[arithmetic_type]") {

  SECTION("Noexcept constructors") {
    static_assert_noexcept_constructors<int>();
    static_assert_noexcept_constructors<long>();
  }

  SECTION("Conversions") {
    /// Should be constructible from its underlying type
    auto a = Arithmetic<long>{2};

    /// Should be explicitly convertible to its underlying type
    long b = a();
    b = static_cast<long>(a);
    long c = 2;
    REQUIRE(b == c);
    auto lambda = [](long i) { return i; };
    REQUIRE(lambda(a()) == c);

    /// Should not be implicitly convertible to its underlying type
    // long d = a; // does not compile :)
    // lambda(a); // does not compile :)

    /// Should not implicitly convert to integer types of different families
    struct class1 {};
    struct class2 {};
    using Type1 = Arithmetic<long, class1>;
    using Type2 = Arithmetic<long, class2>;
    auto e = Type1{2};
    auto f = Type2{3};
    // e = f; // does not compile :)
    static_assert(!std::is_assignable<Type1, Type2>::value,
                  "implicit assignment not allowed");
    static_assert(!std::is_convertible<Type1, Type2>::value,
                  "implicit conversion not allowed");
    e = f();
  }

  SECTION("primitive_cast]") {
    struct class1 {};
    using T1 = Arithmetic<long, class1>;
    struct class2 {};
    using T2 = Arithmetic<long, class2>;

    auto a = T1{2};
    auto b = T2{3};

    primitive_cast(a) = primitive_cast(b);
    REQUIRE(a == T1{3});
  }

  SECTION("compund_assignment]") {
    test_integer_compound_assignment<Arithmetic<long>>();
    test_integer_compound_assignment<Arithmetic<int>>();
  }

  SECTION("arithmetic") {
    test_unsigned_integer_arithmetic<Arithmetic<long>>();
    test_unsigned_integer_arithmetic<Arithmetic<int>>();

    // signed integers:
    using I = Arithmetic<int>;
    auto i1 = I{1};
    auto i3 = i1 - I{2} * i1;
    REQUIRE(i3 == -i1);
  }

  SECTION("integer_increment_operators]") {
    test_unsigned_integer_increment_operators<Arithmetic<long>>();
    test_unsigned_integer_increment_operators<Arithmetic<int>>();
  }

  SECTION("comparison_operators") {
    test_comparison_operators<Arithmetic<long>>();
    test_comparison_operators<Arithmetic<int>>();
  }

  SECTION("to string") {
    using I = Arithmetic<int>;
    using std::to_string;
    auto i1 = I{1};
    std::string rep("1");
    REQUIRE(rep == to_string(i1));
  }

  SECTION("test constexpr") {
    constexpr Arithmetic<int> a{test_constexpr<int>()};
    REQUIRE(a() == 2);
    constexpr Arithmetic<long> b{test_constexpr<long>()};
    REQUIRE(b() == 2);
  }
}
