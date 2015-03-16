/**
 * @file test.cpp
 * @author askryabin
 * 
 */

#include "Greeny.hpp"
#include <iostream>

struct Enumerate
{
  unsigned start;
  unsigned end;
  unsigned cur;
};

unsigned ITERS = 10;
unsigned SLEEP = 1;
unsigned PRINT_EACH = 1;

void
enumerate_integers(Enumerate& e, Greeny::Context& ctx)
{
  for (e.cur = e.start; e.cur < e.end; e.cur++)
  {
    if (e.cur % PRINT_EACH == 0)
    {
      std::cout << "S: " << e.cur << std::endl;
    }
    if (SLEEP)
    {
      ::sleep(SLEEP);
    }
    ctx.yield(true);
  }
  std::cout << "S: exit" << std::endl;
}

void
print_integrers(unsigned start, unsigned end)
{
  Greeny::Context ctx;
  Enumerate e = {start, end, 0};

  const Greeny::Tid tid1 = ctx.add(
    std::bind(&enumerate_integers, std::ref(e), std::ref(ctx)));

  assert(tid1 == 2);

  for (Greeny::Tid tid = ctx.next(); tid; tid = ctx.next())
  {
    assert(tid == tid1);
    if (e.cur % PRINT_EACH == 0)
    {
      std::cout << "M: " << e.cur << std::endl;
    }
    if (SLEEP)
    {
      ::sleep(SLEEP);
    }
  }
  std::cout << "M: exit" << std::endl;
}

int main()
{
  print_integrers(0, ITERS);
  std::cout << "main: exit" << std::endl;
  return 0;
}

