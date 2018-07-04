//  Copyright © 2018 Sunil. All rights reserved.

#pragma once

class Task;

class TaskManagerDelegate {
public:
    virtual void Post(Task& task) = 0;
    virtual void PostToMain(Task& task) = 0;
    virtual void Dispatch(Task& task) = 0;
    virtual void DispatchToMain(Task& task) = 0;
};
