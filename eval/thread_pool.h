#pragma once

#include <functional>
#include <memory>

namespace eval {

typedef std::function<void()> Routine;

class ThreadPool {
 public:
  ThreadPool() = default;
  ThreadPool(const ThreadPool& obj) = delete;
  virtual ~ThreadPool() {}

  virtual void Execute(Routine routine) = 0;
};

typedef std::shared_ptr<ThreadPool> ThreadPoolPtr;

ThreadPoolPtr CreateThreadPool(std::size_t thread_count);

}
