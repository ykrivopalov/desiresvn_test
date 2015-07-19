#include "integrator.h"

#include <cmath>

namespace gui {

Integrator::Integrator(QObject* /*parent*/) : from_(0), to_(0), step_(1) {}

void Integrator::integrate() {
  answer_ = eval::IntegrateSync([](double x) { return std::sin(x); }, from_, to_,
                                step_, 1);
  emit integrated();
}
}
