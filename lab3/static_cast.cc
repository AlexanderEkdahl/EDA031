#include <iostream>
#include <sstream>
#include "date.h"
#include <stdexcept>

template <typename T>
T string_cast(std::string str) {
  T result;
  std::istringstream iss(str);

  if (iss >> result) {
    return result;
  }

  throw std::invalid_argument("Invalid");
}

int main() {
  try {
    int i = string_cast<int>("123");
    double d = string_cast<double>("12.34");
    Date date = string_cast<Date>("2015-01-10");
    std::cout << i << std::endl;
    std::cout << d << std::endl;
    std::cout << date << std::endl;
  } catch (std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
}
