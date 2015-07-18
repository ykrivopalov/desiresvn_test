#include "integrator.h"
#include "thread_pool.h"

#include <QTest>

int main(int argc, char** argv) {
  tests::Integrator integrator_test;
  tests::ThreadPool thread_pool_test;

  int result = 0;
  if (result = QTest::qExec(&integrator_test, argc, argv)) return result;
  if (result = QTest::qExec(&thread_pool_test, argc, argv)) return result;
  return result;
}
