#include "integrator.h"

#include <QTest>

#include <eval/integrator.h>

namespace tests {
namespace {
std::vector<eval::Point> GetPoints(eval::PointIteratorPtr points) {
  std::vector<eval::Point> result;
  for (; points->IsValid(); points->Next()) {
    result.push_back(points->GetValue());
  }
  return result;
}
}

void Integrator::CheckIterator() {
  eval::PointIteratorPtr iterator =
      eval::CreateIterator(0, 5, 1, [](float x) { return 2 * x; });
  using eval::Point;
  std::vector<Point> points = GetPoints(iterator);
  std::vector<Point> sample = {{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}, {5, 10}};
  QVERIFY(points == sample);
}

void Integrator::CheckRectangleArea() {
  eval::PointIteratorPtr iterator =
      eval::CreateIterator(0, 5, 1, [](float x) { return 6; });
  eval::Integrator integrator;
  float result = integrator.Integrate(iterator);
  QVERIFY(result == 30);
}

void Integrator::CheckSinusArea() {
  eval::PointIteratorPtr iterator =
      eval::CreateIterator(0, 10, 0.00001, [](float x) { return std::sin(x); });
  eval::Integrator integrator;
  float result = integrator.Integrate(iterator);
  QVERIFY(result > 1.83 && result < 1.84);
}
}
