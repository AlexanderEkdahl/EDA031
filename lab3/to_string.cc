#include <iostream>
#include <sstream>
#include "date.h"

template <typename T>
std::string toString(const T& t) {
  std::ostringstream oss;
  oss << t;
  return oss.str();
}

int main() {
  double d = 1.234;
  Date today;
  std::string sd = toString(d);
  std::string st = toString(today);

  std::cout << sd << std::endl;
  std::cout << st << std::endl;
}
