/**
 * @file gcc_amd64.hpp
 * @author askryabin
 * 
 */
#ifndef GREENY_GCC_AMD64_HPP_
#define GREENY_GCC_AMD64_HPP_

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
          "movq %%rsp, %0\n"
          "movq %%rbp, %1\n" : "=m"(sp_), "=m"(bp_));
      }

      inline
      void*
      push(void* preserve)  __attribute__((always_inline))
      {
        void* stack_ptr = put_on_stack(preserve);
        __asm__ __volatile__(
          "movq %1, %%rsp\n"
          "movq %2, %%rbp\n"
          "popq %0\n" : "+r"(preserve) : "m"(stack_ptr), "m"(bp_) : "memory");
        return preserve;
      }
    };
  }
}

#endif /* GREENY_GCC_AMD64_HPP_ */
