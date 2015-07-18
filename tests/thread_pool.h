#pragma once

#include <QObject>

namespace tests {

class ThreadPool : public QObject {
  Q_OBJECT
 private slots:
  void ExecutesRoutine();
  void ThreadCanBeReused();
};
}
