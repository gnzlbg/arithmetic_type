#ifndef BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_OSTREAM_
#define BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_OSTREAM_
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
////////////////////////////////////////////////////////////////////////////////

namespace boost {

/// \brief ostream operator
template <class C, class CT, class T, class B>
inline auto operator<<(std::basic_ostream<C, CT>& o, const Arithmetic<T, B>& v)
-> decltype (o << v()) {  return o << v(); }

}  // namespace boost

////////////////////////////////////////////////////////////////////////////////
#endif  // BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_OSTREAM_
