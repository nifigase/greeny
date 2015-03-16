/**
 * @file RegistersBase.hpp
 * @author askryabin
 * 
 */
#ifndef GREENY_REGISTERSBASE_HPP_
#define GREENY_REGISTERSBASE_HPP_

#include <cstring>

namespace Greeny
{
  namespace Platform
  {
    class RegistersBase
    {
    protected:
      void* sp_;
      void* bp_;

      inline
      void*
      put_on_stack(void* what)
      {
        void* stack_ptr = static_cast<char*>(sp_) - sizeof(void*);
        ::memcpy(stack_ptr, &what, sizeof(void*));
        return stack_ptr;
      }

    public:
      explicit
      RegistersBase(void* stack) :
        sp_(stack), bp_(sp_)
      {}
    };
  }
}

#endif /* GREENY_REGISTERSBASE_HPP_ */
