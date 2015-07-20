#include "integrator.h"

#include <atomic>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <mutex>

#include "thread_pool.h"

using namespace std::placeholders;

namespace eval {

namespace {
double TrapezoidArea(const Point& a, const Point& b) {
  return (a.second + b.second) * (b.first - a.first) / 2;
}

struct IntegrationParams {
  Function f;
  double x0;
  double x1;
  double step;
  std::size_t thread_count;
};

class Integration : public Execution {
 public:
  Integration(IntegrationParams params, ResultHandler handler)
      : canceled_(false),
        result_(0),
        evaluations_left_(0),
        params_(params),
        thread_pool_(CreateThreadPool(params.thread_count)),
        handler_(handler) {
    Start();
  }

  virtual void Wait() {
    std::unique_lock<std::mutex> lock(guard_);
    completion_.wait(lock, [this] { return evaluations_left_ == 0; });
  }

  virtual void Cancel() { canceled_ = true; }

 private:
  void Start() {
    const std::size_t tasks_per_thread = static_cast<std::size_t>(
        (params_.x1 - params_.x0) / (params_.step * params_.thread_count));

    evaluations_left_ = params_.thread_count;
    double current_x = params_.x0;
    ResultHandler tasks_handler =
        std::bind(&Integration::on_tasks_completed, this, _1);
    for (std::size_t i = 0; i < params_.thread_count - 1; ++i) {
      double next_x = current_x + tasks_per_thread * params_.step;
      thread_pool_->Execute(std::bind(&Integration::evaluate_tasks, this,
                                      current_x, next_x, tasks_handler));
      current_x = next_x;
    }

    thread_pool_->Execute(std::bind(&Integration::evaluate_tasks, this,
                                    current_x, params_.x1, tasks_handler));
  }

  void on_tasks_completed(double tasks_result) {
    std::size_t updated_evaluations_left = 0;
    {
      std::lock_guard<std::mutex> lock(guard_);
      updated_evaluations_left = --evaluations_left_;
      result_ += tasks_result;
    }

    if (updated_evaluations_left == 0 && !canceled_) {
      if (!canceled_) handler_(result_);

      completion_.notify_all();
    }
  }

  void evaluate_tasks(double x0, double x1, ResultHandler handler) const {
    double result = 0;
    Point previous_point(x0, params_.f(x0));
    for (double x = x0 + params_.step; x <= x1; x += params_.step) {
      if (canceled_) break;

      Point current_point(x, params_.f(x));
      result += TrapezoidArea(previous_point, current_point);
      previous_point = std::move(current_point);
    }
    handler(result);
  }

  std::atomic<bool> canceled_;

  std::mutex guard_;
  std::condition_variable completion_;
  double result_;
  std::size_t evaluations_left_;

  const IntegrationParams params_;
  ThreadPoolPtr thread_pool_;
  ResultHandler handler_;
};
}  // namespace

Integrator::Integrator() : integration_step_(0.1), thread_count_(1) {}

ExecutionPtr Integrator::Integrate(Function f, double x0, double x1,
                                   ResultHandler handler) {
  IntegrationParams params{f, x0, x1, integration_step_, thread_count_};

  return ExecutionPtr(new Integration(params, handler));
}

double IntegrateSync(eval::Function f, double x0, double x1, double step,
                     std::size_t thread_count) {
  eval::Integrator integrator;
  integrator.set_integration_step(step);
  integrator.set_threads_count(thread_count);

  double result = 0;
  auto handler = [&result](double val) { result = val; };
  eval::ExecutionPtr integration = integrator.Integrate(f, x0, x1, handler);
  integration->Wait();
  return result;
}
}  // namespace eval
