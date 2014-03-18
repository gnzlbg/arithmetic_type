## Arithmetic types

### Provides

`Arithmetic<T>` where `T` models the `Arithmetic` concept is a wrapper that
disables _any_ implicit conversions between `T` and other types. 

An `Arithmetic<T>` can be made opaque by passing it a unique tag as second
template parameter `Arithmetic<T, unique_tag>`.

### Why is this useful?

It let's you define opaque typedefs for arithmetic types which can be explicitly
convertible to each other. This allows to easily specify strongly typed
interfaces when Arithmetic types are involved.

### Example 1: disabling implicit conversions

```c++
int a{2};
long b{3};
b = a; // works: the implicit conversion is safe

Arithmetic<int> a{2};
Arithmetic<long> b{3};
b = a; // compile error: implicit conversion
b = Arithmetic<long>{a}; // works: explicit conversion
```

### Example 2: opaque type-defs

```c++
struct Tag1 {};
struct Tag2 {};

using Type1 = Arithmetic<int, Tag1>;
using Type2 = Arithmetic<int, Tag2>;
Type1 a{2};
Type2 b{3};
b = a; // compilation error: implicit conversion
b = Type2{a}; // works: explicit conversion
```

### Dependencies:
- C++11 compiler (currently tested with clang 3.5 only)

### License
- Boost Software License Version 1.0
