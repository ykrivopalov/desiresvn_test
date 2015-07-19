#pragma once

#include <QObject>

#include <eval/integrator.h>

namespace gui {

class Integrator : public QObject {
  Q_OBJECT
  Q_PROPERTY(double from MEMBER from_)
  Q_PROPERTY(double to MEMBER to_)
  Q_PROPERTY(double step MEMBER step_)
  Q_PROPERTY(double answer READ answer NOTIFY integrated)

 public:
  explicit Integrator(QObject* parent = 0);

  double answer() { return answer_; }

 signals:
  void integrated();

 public slots:
  void integrate();

 private:
  eval::Integrator integrator_;
  double from_;
  double to_;
  double step_;
  double answer_;
};
}
