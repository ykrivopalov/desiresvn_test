#pragma once

#include <functional>
#include <memory>
#include <utility>

namespace eval {

typedef std::pair<float, float> Point;

typedef std::function<float(float)> Function;
typedef std::function<void(float)> ResultHandler;

class Execution {
 public:
  virtual void Wait() = 0;
  virtual void Cancel() = 0;
};

typedef std::shared_ptr<Execution> ExecutionPtr;

class Integrator {
 public:
  Integrator();

  ExecutionPtr Integrate(Function f, float x0, float x1, ResultHandler handler);

  void set_integration_step(float step) { integration_step_ = step; }
  void set_threads_count(std::size_t count) { thread_count_ = count; }

 private:
  float integration_step_;
  std::size_t thread_count_;
};

float IntegrateSync(eval::Function f, float x0, float x1, float step,
                    std::size_t thread_count);
}  // namespace eval
