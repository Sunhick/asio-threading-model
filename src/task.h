//  Copyright © 2018 Sunil. All rights reserved.

#pragma once

class Task {
 public:
  virtual ~Task();

  // Run this unit work on the worker threads
  virtual void run() = 0;
};
