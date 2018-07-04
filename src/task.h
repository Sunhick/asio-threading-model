//  Copyright © 2018 Sunil. All rights reserved.

#pragma once

#include "task_manager_delegate.h"

class Task {
 public:
  virtual ~Task();

  // Run this unit work on the worker threads
  virtual void run(TaskManagerDelegate& delegate) = 0;
};
