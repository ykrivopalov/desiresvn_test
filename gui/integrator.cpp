#include "integrator.h"

#include <cmath>

namespace gui {

Integrator::Integrator(QObject* /*parent*/)
    : from_(0), to_(1), step_(0.1), thread_count_(1) {}

void Integrator::cancel() { current_integration_->Cancel(); }

void Integrator::integrate() {
  try {
    integrator_.set_integration_step(step_);
    integrator_.set_threads_count(thread_count_);
    current_integration_ = integrator_.Integrate(
        [](double x) { return std::sin(x); }, from_, to_,
        [this](double result) { integration_completed(result); });
  } catch (const std::exception& err) {
    emit error(err.what());
  }
}

void Integrator::integration_completed(double result) {
  emit integrated(result);
}
}
