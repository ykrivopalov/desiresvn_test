#include "integrator.h"

#include <cmath>

namespace gui {

Integrator::Integrator(QObject* /*parent*/) : from_(0), to_(0), step_(1) {}

void Integrator::integrate() {
  eval::PointIteratorPtr iterator = eval::CreateIterator(
      from_, to_, step_, [](float x) { return std::sin(x); });
  answer_ = integrator_.Integrate(iterator);
  emit integrated();
}
}
