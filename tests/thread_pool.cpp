#include "thread_pool.h"

#include <chrono>
#include <iostream>
#include <thread>

#include <QTest>

#include <eval/thread_pool.h>

namespace tests {

void SetTrue(bool& val) { val = true; }

void ThreadPool::ExecutesRoutine() {
  eval::ThreadPoolPtr pool = eval::CreateThreadPool(1);
  bool executed = false;
  pool->Execute(std::bind(SetTrue, std::ref(executed)));
  std::this_thread::sleep_for(std::chrono::seconds(1));
  QVERIFY(executed);
}

void ThreadPool::ThreadCanBeReused() {
  eval::ThreadPoolPtr pool = eval::CreateThreadPool(1);
  bool executed = false;
  pool->Execute(std::bind(SetTrue, std::ref(executed)));
  bool executed2 = false;
  pool->Execute(std::bind(SetTrue, std::ref(executed2)));
  std::this_thread::sleep_for(std::chrono::seconds(1));
  QVERIFY(executed && executed2);
}
}
