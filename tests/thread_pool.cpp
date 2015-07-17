#include <eval/thread_pool.h>
#include <iostream>
#include <thread>
#include <QTest>

namespace Tests
{
  void SetTrue(bool& val)
  {
    val = true;
  }

  void InfiniteLoop()
  {
    while (true) {}
  }

  class ThreadPool : public QObject
  {
    Q_OBJECT
  private slots:
      void ExecutesRoutine()
      {
        Eval::ThreadPool pool;
        bool executed = false;
        pool.Execute(std::bind(SetTrue, std::ref(executed)))->Wait();
        QVERIFY(executed);
      }
  };
}

QTEST_MAIN(Tests::ThreadPool)
#include "thread_pool.moc"

