#include "thread_pool.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

namespace Eval
{
  namespace
  {
    typedef std::shared_ptr<Routine> RoutinePtr;

    class RoutineQueue
    {
    public:
      RoutineQueue()
        : Stopped(false)
      {
      }

      void Push(const Routine& routine)
      {
        {
          std::lock_guard<std::mutex> lock(Guard);
          Queue.push(routine);
        }
        Condition.notify_one();
      }

      void Stop()
      {
        Stopped = true;
        Condition.notify_all();
      }

      RoutinePtr Pop()
      {
        RoutinePtr result;
        {
          std::unique_lock<std::mutex> lock(Guard);
          Condition.wait(lock, [this]{return Queue.size() > 0 || Stopped;});
          if (!Stopped)
          {
            ///@todo move?
            result.reset(new Routine(Queue.front()));
            Queue.pop();
          }
        }
        Condition.notify_one();
        return result;
      }

    private:
      std::mutex Guard; ///@todo something lighter?
      std::condition_variable Condition;
      std::queue<Routine> Queue;
      std::atomic<bool> Stopped;
    };


    ///@todo sigmask?
    class Worker
    {
    public:
      Worker(RoutineQueue& queue)
        : Queue(queue)
        , Thread(&Worker::Loop, this)
      {
      }

      void Wait()
      {
        Thread.join();
      }

    private:
      void Loop()
      {
        while (RoutinePtr routine = Queue.Pop())
        {
          (*routine)();
        }
      }

      RoutineQueue& Queue;
      std::thread Thread;
    };
  }

  typedef std::shared_ptr<Worker> WorkerPtr;

  class ThreadPoolImpl : public ThreadPool
  {
  public:
    ThreadPoolImpl(std::size_t threadCount)
    {
      /// @todo maybe some sugar exists?
      for (std::size_t i = 0; i < threadCount; ++i)
      {
        Workers.push_back(WorkerPtr(new Worker(Queue)));
      }
    }

    ~ThreadPoolImpl()
    {
      Queue.Stop();
      for (WorkerPtr& w: Workers)
      {
        w->Wait();
      }
    }

    virtual void Execute(Routine routine)
    {
      Queue.Push(routine);
    }

  private:
    RoutineQueue Queue;
    std::vector<WorkerPtr> Workers;
  };

  ThreadPoolPtr CreateThreadPool(std::size_t threadCount)
  {
    return ThreadPoolPtr(new ThreadPoolImpl(threadCount));
  }
}
