#pragma once

#include <functional>
#include <memory>

namespace Eval
{
  class Thread
  {
  public:
    virtual ~Thread() {}

    virtual void Wait() = 0;
  };

  typedef std::shared_ptr<Thread> ThreadPtr;

  typedef std::function<void()> Routine;

  class ThreadPool
  {
  public:
    ThreadPool();

    ThreadPtr Execute(Routine routine);
  };
}
