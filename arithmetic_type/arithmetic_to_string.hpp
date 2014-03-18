#ifndef BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TO_STRING_
#define BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TO_STRING_
////////////////////////////////////////////////////////////////////////////////
#include <string>
////////////////////////////////////////////////////////////////////////////////

namespace boost {

/// \brief to_string
template<class T, class U>
inline std::string to_string(const Arithmetic<T, U> a) {
  return std::to_string(a());
}

}  // namespace boost

////////////////////////////////////////////////////////////////////////////////
#endif  // BOOST_UTILITIES_ARITHMETIC_TYPE_ARITHMETIC_TO_STRING_
