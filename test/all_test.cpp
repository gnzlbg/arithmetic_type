/// \file Tests the Integer wrapper
#include "arithmetic_type/arithmetic_type.hpp"
#include "arithmetic_type/primitive_cast.hpp"
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

TEST_CASE("Test arithmetic type", "[arithmetic_type]") {

  SECTION("Conversions") {
    /// Should be constructible from its underlying type
    auto a = Arithmetic<long>{2};

    /// Should be explicitly convertible to its underlying type
    long b = a();
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
    auto e = Arithmetic<long, class1>{2};
    auto f = Arithmetic<long, class2>{3};
    // e = f; // does not compile :)
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
}
