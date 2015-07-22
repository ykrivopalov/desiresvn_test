#include "thread_pool.h"

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

namespace eval {

namespace {

typedef std::shared_ptr<Routine> RoutinePtr;

class RoutineQueue {
 public:
  RoutineQueue() : stopped_(false) {}

  void Push(const Routine& routine) {
    {
      std::lock_guard<std::mutex> lock(guard_);
      queue_.push(routine);
    }
    condition_.notify_one();
  }

  void Stop() {
    stopped_ = true;
    condition_.notify_all();
  }

  RoutinePtr Pop() {
    RoutinePtr result;
    {
      std::unique_lock<std::mutex> lock(guard_);
      condition_.wait(lock, [this] { return queue_.size() > 0 || stopped_; });
      if (!stopped_) {
        result.reset(new Routine(queue_.front()));
        queue_.pop();
      }
    }
    condition_.notify_one();
    return result;
  }

 private:
  std::mutex guard_;
  std::condition_variable condition_;
  std::queue<Routine> queue_;
  std::atomic<bool> stopped_;
};

class Worker {
 public:
  Worker(RoutineQueue& queue) : queue_(queue), thread_(&Worker::Loop, this) {}

  void Wait() { thread_.join(); }

 private:
  void Loop() {
    while (RoutinePtr routine = queue_.Pop()) {
      (*routine)();
    }
  }

  RoutineQueue& queue_;
  std::thread thread_;
};
}

typedef std::shared_ptr<Worker> WorkerPtr;

class ThreadPoolImpl : public ThreadPool {
 public:
  ThreadPoolImpl(std::size_t thread_count) {
    assert(thread_count > 0);
    try {
      for (std::size_t i = 0; i < thread_count; ++i) {
        workers_.push_back(WorkerPtr(new Worker(queue_)));
      }
    } catch (const std::exception&) {
      Shutdown();
      throw;
    }
  }

  ~ThreadPoolImpl() { Shutdown(); }

  virtual void Execute(Routine routine) { queue_.Push(routine); }

 private:
  void Shutdown() {
    queue_.Stop();
    for (WorkerPtr& w : workers_) {
      w->Wait();
    }
  }

  RoutineQueue queue_;
  std::vector<WorkerPtr> workers_;
};

ThreadPoolPtr CreateThreadPool(std::size_t thread_count) {
  return ThreadPoolPtr(new ThreadPoolImpl(thread_count));
}
}
