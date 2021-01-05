#pragma once

#include <string>
#include <functional>
#include <fstream>
#include <iostream>

namespace algolab {
struct Judge {
  static void runTests(const std::function<void(std::istream&)>& logic, std::string&& path = "");
}; // struct Judge
} // namespace algolab
