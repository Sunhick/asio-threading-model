//  Copyright © 2018 Sunil. All rights reserved.

#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

#include "include/asio.hpp"
#include "task_manager.h"
#include "thread_extension.h"

#include "task.h"
#include "task_manager.h"

using namespace std::chrono_literals;

class SimpleTask : public Task {
 private:
  std::mutex& lock;

 public:
  SimpleTask(std::mutex& lock) : lock(lock) {}
  void run(TaskManagerDelegate& delegate) override {
    std::this_thread::sleep_for(1s);
    std::lock_guard<std::mutex> guard(lock);
    std::cout << "[SimpleTask] " << std::this_thread::get_name() << std::endl;
  }
};

class Task1 : public Task {
 private:
  std::mutex& lock;
  SimpleTask simpleTask;

 public:
  Task1(std::mutex& lock) : lock(lock), simpleTask(SimpleTask(lock)) {}
  void run(TaskManagerDelegate& delegate) override {
    int i = 0;
    while (i++ < 100) {
      delegate.Post(simpleTask);
      delegate.PostToMain(simpleTask);
    }

    std::lock_guard<std::mutex> guard(lock);
    std::cout << "[Task1] " << std::this_thread::get_name() << std::endl;
  }
};

class Task2 : public Task {
 private:
  std::mutex& lock;

 public:
  Task2(std::mutex& lock) : lock(lock) {}
  void run(TaskManagerDelegate& delegate) override {
    std::lock_guard<std::mutex> guard(lock);
    std::cout << "[Task2] " << std::this_thread::get_name() << std::endl;
  }
};

int main(int argc, const char* argv[]) {
  std::thread main([]() {
    std::mutex printMutex;
    TaskManager taskManager(10);
    Task1 t1(printMutex);
    Task2 t2(printMutex);

    // taskManager.Post(t1);
    // taskManager.PostToMain(t2);

    taskManager.DispatchToMain(t2);
    taskManager.Dispatch(t1);

    taskManager.Start();
  });

  main.join();

  return 0;
}
