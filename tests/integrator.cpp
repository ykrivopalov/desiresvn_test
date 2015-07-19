#include "integrator.h"

#include <QTest>

#include <eval/integrator.h>

namespace tests {
void Integrator::CheckRectangleArea() {
  float result = eval::IntegrateSync([](float x) { return 6; }, 0, 5, 1, 1);
  QCOMPARE(result, 30.);
}

void Integrator::CheckSinusArea() {
  float result = eval::IntegrateSync([](float x) { return std::sin(x); }, 0, 10,
                                     0.00001, 1);
  QVERIFY(result > 1.83 && result < 1.84);
}

void Integrator::ForDifferentThreadCountResultIsSame() {
  using eval::IntegrateSync;
  float result1 = IntegrateSync([](float x) { return 6; }, 0, 5, 0.01, 1);
  float result2 = IntegrateSync([](float x) { return 6; }, 0, 5, 0.01, 2);
  float result3 = IntegrateSync([](float x) { return 6; }, 0, 5, 0.01, 2);
  float result13 = IntegrateSync([](float x) { return 6; }, 0, 5, 0.01, 2);
  QCOMPARE(result1, result2);
  QCOMPARE(result2, result3);
  QCOMPARE(result3, result13);
}
}
