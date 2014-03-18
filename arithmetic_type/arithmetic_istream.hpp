#ifndef BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_ISTREAM_
#define BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_ISTREAM_
////////////////////////////////////////////////////////////////////////////////
#include <istream>
////////////////////////////////////////////////////////////////////////////////

namespace boost {

/// \brief istream operator
template <class C, class CT, class T, class B>
inline auto operator>>(std::basic_istream<C, CT>& i, Arithmetic<T, B>& v)
-> decltype (i >> v()) { return i >> v(); }

}  // namespace boost

////////////////////////////////////////////////////////////////////////////////
#endif  // BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_ISTREAM_
