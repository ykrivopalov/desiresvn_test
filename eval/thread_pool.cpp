#include "thread_pool.h"

#include <thread>

namespace Eval
{
  namespace
  {
    class StdThread : public Thread
    {
    public:
      StdThread(Routine routine)
        : Thread(routine)
      {
      }

      virtual void Wait()
      {
        Thread.join();
      }

    private:
      std::thread Thread;
    };
  }

  ThreadPool::ThreadPool()
  {
  }

  ThreadPtr ThreadPool::Execute(Routine routine)
  {
    return ThreadPtr(new StdThread(routine));
  }
}
