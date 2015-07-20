#pragma once

#include <functional>
#include <memory>
#include <utility>

namespace eval {

typedef std::pair<double, double> Point;

typedef std::function<double(double)> Function;
typedef std::function<void(double)> ResultHandler;

/// @brief class for async execution control
class Execution {
 public:
  /// @brief synchronously wait until execution finished
  virtual void Wait() = 0;

  /// @brief send cancel signal to execution, doesn't wait
  virtual void Cancel() = 0;
};

typedef std::shared_ptr<Execution> ExecutionPtr;

/// @brief class for asynchronous calculation of definite integral by trapesoid
/// rule
class Integrator {
 public:
  Integrator();

  /// @brief Run integration process
  /// @param f is function for integration
  /// @param x0 is left border of integration
  /// @param x1 is right border of integration
  /// @param handler is result of integration consumer
  ExecutionPtr Integrate(Function f, double x0, double x1,
                         ResultHandler handler);

  /// @brief set step of integration
  void set_integration_step(double step) { integration_step_ = step; }

  /// @brief set count of threads that used for integration
  void set_threads_count(std::size_t count) { thread_count_ = count; }

 private:
  double integration_step_;
  std::size_t thread_count_;
};

/// @brief integrate with Integrator, but synchronously
double IntegrateSync(eval::Function f, double x0, double x1, double step,
                     std::size_t thread_count);
}  // namespace eval
