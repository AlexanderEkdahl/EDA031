#include <iostream>
#include <fstream>
#include <string>
#include "coding.h"

int main(__attribute__((unused)) int argc, char* argv[]) {
  std::ifstream fin(argv[1]);
  std::string file = argv[1];
  file += ".dec";
  std::ofstream fout(file);

  char c;
  while (fin.get(c)) {
    fout << Coding::decode(c);
  }
}
