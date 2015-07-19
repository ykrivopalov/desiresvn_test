#pragma once

#include <QObject>

namespace tests {

class Integrator : public QObject {
  Q_OBJECT
 private slots:
  void CheckRectangleArea();
  void CheckSinusArea();
  void ForDifferentThreadCountResultIsSame();
};
}
