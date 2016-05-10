#include "integrator.h"

#include <eval/integrator.h>

#include <QTest>
#include <cmath>

namespace tests {
void Integrator::CheckRectangleArea() {
  double result = eval::IntegrateSync([](double x) { return 6; }, 0, 5, 1, 1);
  QCOMPARE(result, 30.);
}

void Integrator::CheckSinusArea() {
  double result = eval::IntegrateSync([](double x) { return std::sin(x); }, 0, 10,
                                     0.00001, 1);
  QVERIFY(result > 1.83 && result < 1.84);
}

void Integrator::ForDifferentThreadCountResultIsSame() {
  using eval::IntegrateSync;
  double result1 = IntegrateSync([](double x) { return 6; }, 0, 5, 0.01, 1);
  double result2 = IntegrateSync([](double x) { return 6; }, 0, 5, 0.01, 2);
  double result3 = IntegrateSync([](double x) { return 6; }, 0, 5, 0.01, 2);
  double result13 = IntegrateSync([](double x) { return 6; }, 0, 5, 0.01, 2);
  QCOMPARE(result1, result2);
  QCOMPARE(result2, result3);
  QCOMPARE(result3, result13);
}
}
