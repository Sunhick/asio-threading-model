//  Copyright © 2018 Sunil. All rights reserved.

#include "thread_extension.h"

#include <pthread.h>

namespace std {
namespace this_thread {

void set_name(const std::string& tname) {
  pthread_setname_np(tname.c_str());
}

std::string get_name() {
  char name[16];
  pthread_getname_np(pthread_self(), &name[0], sizeof(name));
  return name;
}

}  // namespace this_thread
}  // namespace std
