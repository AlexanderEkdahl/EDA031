#include <iostream>
#include <regex>
#include "tagremover.h"

TagRemover::TagRemover(std::istream& in) : instream(in) {}

void TagRemover::print(std::ostream& out) {
  std::string input;
  std::string line;

  while (std::getline(instream, line)) input += line + "\n";

  input = regex_replace(input, std::regex("<[^<>]*>"), "");
  input = regex_replace(input, std::regex("&lt;"), "<");
  input = regex_replace(input, std::regex("&gt;"), ">");
  input = regex_replace(input, std::regex("&nbsp;"), " ");
  input = regex_replace(input, std::regex("&amp;"), "&");

  out << input;
}
