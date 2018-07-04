//  Copyright © 2018 Sunil. All rights reserved.

#include "task_manager.h"

#include <functional>
#include <iostream>

#include "task.h"
#include "thread_extension.h"

namespace {
const std::string MAIN_THREAD = "main";
const std::string WORKER_THREAD = "wrk:";
const std::string WORKER_MANAGER_THREAD = "wrkMgr";
}  // namespace

TaskManager::TaskManager(int workers)
    : slaveWork(asio::io_service::work(slaves)),
      mainWork(asio::io_service::work(slaves)) {
  // Assume the whoever is creating the TaskManager to be
  // a main thread and attach a few worker threads to the
  // pool.
  std::this_thread::set_name(MAIN_THREAD);

  // factor in the worker manager when spinning up the worker pools
  for (size_t t = 0; t < workers - 1; t++) {
    workerPool.push_back(std::thread([&, this, t] {
      std::this_thread::set_name(WORKER_THREAD + std::to_string(t));
      this->slaves.run();
    }));
  }
}

TaskManager::~TaskManager() {
  main.stop();
  slaves.stop();

  std::cout << "TaskManager stopped!" << std::endl;
}

void TaskManager::Post(Task& task) {
  // Post to the worker thread
  slaves.post(std::bind(&Task::run, &task));
}

void TaskManager::PostToMain(Task& task) {
  // Post to the main thread
  main.post(std::bind(&Task::run, &task));
}

void TaskManager::Start() {
  // Run the slaves on a worker manager thread (a different thread);
  // because calling run from the current thread will attach current
  // thread to the slaves pool. And we don't want to add main thread
  // to the slaves pool.
  workManager = std::thread(([this]() {
    std::this_thread::set_name(WORKER_MANAGER_THREAD);
    this->slaves.run();
  }));

  main.run();

  for (std::thread& worker : workerPool) {
    worker.join();
  }
  workManager.join();
  std::cout << "Main thread is ready to process!" << std::endl;
  std::cout << "workers are ready to process!" << std::endl;
}
