#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <string>
#include <iostream>

class TagRemover {
 public:
  TagRemover(std::istream& in);
  void print(std::ostream& out);

 private:
  std::istream& instream;
};

#endif
