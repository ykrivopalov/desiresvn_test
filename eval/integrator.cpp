#include "integrator.h"

#include <cmath>

namespace eval {

float TrapezoidArea(const Point& a, const Point& b) {
  return (a.second + b.second) * (b.first - a.first) / 2;
}

float Integrator::Integrate(PointIteratorPtr points) {
  if (!points->IsValid()) return 0;

  float result = 0;

  Point previous = points->GetValue();
  points->Next();

  while (points->IsValid()) {
    Point current = points->GetValue();
    result += TrapezoidArea(previous, current);

    previous = current;
    points->Next();
  }

  return result;
}

class FunctionIterator : public PointIterator {
 public:
  FunctionIterator(float x0, float x1, float step, Function f)
      : current_(x0, f(x0)), x1_(x1), step_(step), f_(f) {}

  virtual Point GetValue() { return current_; }

  virtual void Next() {
    float new_x = current_.first + step_;
    float new_y = new_x <= x1_ ? f_(new_x) : 0;
    current_ = std::make_pair(new_x, new_y);
  }

  virtual bool IsValid() { return current_.first <= x1_; }

 private:
  Point current_;
  float x1_;
  float step_;
  Function f_;
};

PointIteratorPtr CreateIterator(float x0, float x1, float step, Function f) {
  return PointIteratorPtr(new FunctionIterator(x0, x1, step, f));
}
}
