/**
 * @file Greeny.hpp
 * @author askryabin
 * 
 */
#ifndef GREENY_HPP_
#define GREENY_HPP_

#include "detail/Platform.hpp"

#include <functional>
#include <boost/ptr_container/ptr_vector.hpp>

namespace Greeny
{
  class Context;

  typedef unsigned Tid;

  /**
   * Green thread
   */
  class Thread
  {
  private:
    enum Status
    {
      gts_zomby = 0x1,
      gts_new = 0x2,
      gts_ready = 0x4,
      gts_posted = 0x8
    };

    /**
     * Callbacks are casted to std::function
     */
    typedef std::function<void ()> Fun;
    Fun fun_;

    const size_t stack_sz_;
    char* stack_;

    Status status_;
    Tid tid_;
    bool posted_;
    Platform::Registers regs_;

    template <typename T>
    Thread(const T& cb, size_t stack_sz, Tid tid) :
      fun_(cb), stack_sz_(stack_sz), stack_(new char[stack_sz_]),
      status_(gts_new), tid_(tid), posted_(false),
      regs_(stack_ + stack_sz_ - 1)
    {}

    /**
     * thread with no callback and no stack - represent main (current) thread.
     */
    explicit
    Thread(Tid tid) :
      stack_sz_(0), stack_(0),
      status_(gts_new), tid_(tid), posted_(false),
      regs_(0)
    {}

    //non-copyable
    Thread();
    Thread(const Thread&);

    friend class Context;

  public:
    ~Thread()
    {
      if (stack_)
      {
        delete[] stack_;
      }
    }

    unsigned
    tid() const
    {
      return tid_;
    }
  };

  /**
   * Represents a set of green threads executed in one physical thread.
   * You may create multiple contexts in one or multiple OS threads.
   */
  class Context
  {
  private:
    boost::ptr_vector<Thread> threads_;
    Tid cur_;

    Thread&
    get(Tid tid)
    {
      assert(tid);
      assert(tid <= threads_.size());
      return threads_[tid-1];
    }

    Tid
    find_next(unsigned status_mask);

    void
    run();

  public:
    static const size_t DEFAULT_STACK = 1024*8;

    /**
     * Add new green thread executing the given callback.
     */
    template <typename T>
    Tid
    add(const T& cb, size_t stack_sz = DEFAULT_STACK)
    {
      const Tid tid = threads_.size()+1;
      threads_.push_back(new Thread(cb, stack_sz, tid));
      return tid;
    }

    Context() : threads_(), cur_(0)
    {
      threads_.push_back(new Thread(1));
      threads_.front().status_ = Thread::gts_ready;
      cur_ = 1;
    }

    /**
     * Give up execution until the thread with given TID posts a value
     * (calling yield).
     * @return false if the thread is terminated.
     */
    bool
    next(Tid tid);

    /**
     * Pause execution until any other thread posts a value
     * (calling yield).
     * @return 0 TID if all other threads are terminated.
     */
    Tid
    next();

    /**
     * Give up execution of the current thread.
     * Optionally post a value to receiving thread.
     */
    NOINLINE_PRE
    void yield(bool posted)
    NOINLINE_POST ;
  };
}

#endif /* GREENY_HPP_ */
