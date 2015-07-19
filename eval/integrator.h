#pragma once

#include <functional>
#include <memory>
#include <utility>

namespace eval {

typedef std::pair<double, double> Point;

typedef std::function<double(double)> Function;
typedef std::function<void(double)> ResultHandler;

class Execution {
 public:
  virtual void Wait() = 0;
  virtual void Cancel() = 0;
};

typedef std::shared_ptr<Execution> ExecutionPtr;

class Integrator {
 public:
  Integrator();

  ExecutionPtr Integrate(Function f, double x0, double x1, ResultHandler handler);

  void set_integration_step(double step) { integration_step_ = step; }
  void set_threads_count(std::size_t count) { thread_count_ = count; }

 private:
  double integration_step_;
  std::size_t thread_count_;
};

double IntegrateSync(eval::Function f, double x0, double x1, double step,
                    std::size_t thread_count);
}  // namespace eval
