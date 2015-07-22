#pragma once

#include <functional>
#include <memory>

namespace eval {

typedef std::function<void()> Routine;

/// @brief interface for thread pool management
class ThreadPool {
 public:
  ThreadPool() = default;
  ThreadPool(const ThreadPool& obj) = delete;
  virtual ~ThreadPool() {}

  /// @brief execute routine in separate thread
  virtual void Execute(Routine routine) = 0;
};

typedef std::shared_ptr<ThreadPool> ThreadPoolPtr;

/// @brief Creates thread pool that manages specified threads number.
/// @note All the routines are executed in preallocated threads. If the number
/// of threads is not enough then routine will be put in the queue.
ThreadPoolPtr CreateThreadPool(std::size_t thread_count);
}
