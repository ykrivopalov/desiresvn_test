#pragma once

#include <functional>
#include <memory>
#include <utility>

namespace eval {

typedef std::pair<float, float> Point;

template <typename Value>
class Iterator {
 public:
  virtual Value GetValue() = 0;
  virtual void Next() = 0;
  virtual bool IsValid() = 0;
};

typedef Iterator<Point> PointIterator;
typedef std::shared_ptr<PointIterator> PointIteratorPtr;

class Integrator {
 public:
  float Integrate(PointIteratorPtr points);
};

typedef std::function<float(float)> Function;
PointIteratorPtr CreateIterator(float x0, float x1, float step, Function f);
}
