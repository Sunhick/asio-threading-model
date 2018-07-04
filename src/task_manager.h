//  Copyright © 2018 Sunil. All rights reserved.

#pragma once

#include <thread>
#include <vector>

#include "include/asio.hpp"

class Task;

class TaskManager {
 private:
  std::vector<Task> tasks;
  std::vector<std::thread> workerPool;
  std::thread workManager;

  asio::io_service main;
  asio::io_service slaves;

  asio::io_service::work slaveWork;
  asio::io_service::work mainWork;

 public:
  TaskManager(int workers = std::thread::hardware_concurrency());
  ~TaskManager();

  void Post(Task& task);
  void PostToMain(Task& task);
  void Start();
};
