/**
 * @file gcc_i386.hpp
 * @author askryabin
 * 
 */
#ifndef GREENY_GCC_I386_HPP_
#define GREENY_GCC_I386_HPP_

#include <detail/RegistersBase.hpp>

namespace Greeny
{
  namespace Platform
  {
    class Registers : public RegistersBase
    {
    public:
      explicit
      Registers(void* stack) : RegistersBase(stack) {}

      inline
      void
      pull() __attribute__((always_inline))
      {
        __asm__ __volatile__(
          "mov %%esp, %0\n"
          "mov %%ebp, %1\n" : "=m"(sp_), "=m"(bp_));
      }

      inline
      void*
      push(void* preserve)  __attribute__((always_inline))
      {
        void* stack_ptr = put_on_stack(preserve);
        __asm__ __volatile__(
          "mov %1, %%esp\n"
          "mov %2, %%ebp\n"
          "pop %0\n" : "+r"(preserve) : "m"(stack_ptr), "m"(bp_) : "memory");
        return preserve;
      }
    };
  }
}

#endif /* GREENY_GCC_I386_HPP_ */
