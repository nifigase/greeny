/**
 * @file Platform.hpp
 * @author askryabin
 * 
 */
#ifndef GREENY_PLATFORM_HPP_
#define GREENY_PLATFORM_HPP_

#if defined(__GNUC__)
# define NOINLINE_PRE
# define NOINLINE_POST __attribute__((noinline))
#elif defined(_MSC_VER)
# define NOINLINE_PRE __declspec(noinline)
# define NOINLINE_POST
#else
#  error "Your platform is not supported for Greeny"
#endif

#if defined(__GNUC__)
# if defined(__i386__)
#  include "detail/gcc_i386.hpp"
# elif defined(__amd64__)
#  include "detail/gcc_amd64.hpp"
# endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#  include "detail/vs_i386.hpp"
#else
#  error "Your platform is not supported for Greeny"
#endif

#endif /* GREENY_PLATFORM_HPP_ */
