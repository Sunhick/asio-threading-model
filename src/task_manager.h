//  Copyright © 2018 Sunil. All rights reserved.

#pragma once

#include <memory>
#include <thread>
#include <vector>

#include "include/asio.hpp"
#include "task_manager_delegate.h"

class Task;

class TaskManager : public TaskManagerDelegate {
 private:
  std::vector<Task> tasks;
  std::vector<std::thread> workerPool;
  std::thread workManager;

  asio::io_service main;
  asio::io_service slaves;

  std::shared_ptr<asio::io_service::work> slaveWork;
  std::shared_ptr<asio::io_service::work> mainWork;

 public:
  TaskManager(int workers = std::thread::hardware_concurrency());
  ~TaskManager();

  void Post(Task& task) override;
  void PostToMain(Task& task) override;
  void Dispatch(Task& task) override;
  void DispatchToMain(Task& task) override;

  void Start();
};
