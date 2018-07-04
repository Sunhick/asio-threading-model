//  Copyright © 2018 Sunil. All rights reserved.

#pragma once

#include <string>

namespace std {
namespace this_thread {

void set_name(const std::string& tname);
std::string get_name();

}  // namespace this_thread
}  // namespace std
