/**
 * @file Greeny.cpp
 * @author askryabin
 * 
 */

#include "Greeny.hpp"

namespace Greeny
{
  bool
  Context::next(Tid tid)
  {
    Thread& gt = get(tid);
    while(true)
    {
      switch(gt.status_)
      {
        case Thread::gts_new:
        case Thread::gts_ready:
          yield(false);
          continue;
        case Thread::gts_posted:
          gt.status_ = Thread::gts_ready;
          return true;
        case Thread::gts_zomby:
          return false;
      }
    }
    return true;
  }

  Tid
  Context::next()
  {
    while(true)
    {
      Tid tid = find_next(Thread::gts_posted);
      if (tid)
      {
        get(tid).status_ = Thread::gts_ready;
        return tid;
      }
      tid = find_next(Thread::gts_new | Thread::gts_ready);
      if (tid)
      {
        yield(false);
        continue;
      }
      //only zombies remain
      break;
    }
    return 0;
  }

  Tid
  Context::find_next(unsigned status_mask)
  {
    for (Tid tid = cur_ + 1; tid != cur_; ++tid)
    {
      if (tid > threads_.size())
      {
        tid = 0;
        continue;
      }
      Thread& t = get(tid);
      if (t.status_ & status_mask)
      {
        return tid;
      }
    }
    return 0;
  }

  void
  Context::run()
  {
    Thread& gt = get(cur_);
    if (gt.status_ == Thread::gts_new)
    {
      gt.status_ = Thread::gts_ready;
      gt.fun_();
      gt.status_ = Thread::gts_zomby;
      yield(false);//thats pure gold right there
    }
  }

  void
  Context::yield(bool posted)
  {
    Thread& gt = get(cur_);
    if (posted)
    {
      gt.status_ = Thread::gts_posted;
    }
    Tid next_tid = find_next(Thread::gts_new | Thread::gts_ready);
    if (!next_tid)
    {
      return;
    }
    Thread& next_gt = get(next_tid);
    cur_ = next_tid;

    gt.regs_.pull();

    Context* new_this = static_cast<Context*>(next_gt.regs_.push(this));
    new_this->run();
  }
}

