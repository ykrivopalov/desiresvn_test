#pragma once

#include <QObject>

#include <eval/integrator.h>

namespace gui {

class Integrator : public QObject {
  Q_OBJECT
  Q_PROPERTY(float from MEMBER from_)
  Q_PROPERTY(float to MEMBER to_)
  Q_PROPERTY(float step MEMBER step_)
  Q_PROPERTY(float answer READ answer NOTIFY integrated)

 public:
  explicit Integrator(QObject* parent = 0);

  float answer() { return answer_; }

 signals:
  void integrated();

 public slots:
  void integrate();

 private:
  eval::Integrator integrator_;
  float from_;
  float to_;
  float step_;
  float answer_;
};
}
