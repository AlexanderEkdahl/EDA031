#include "word.h"
#include <string>
#include <vector>

Word::Word(const std::string& w, const std::vector<std::string>& t)
    : word(w), trigrams(t) {}

std::string Word::get_word() const { return word; }

unsigned int Word::get_matches(const std::vector<std::string>& t) const {
  int matches = 0;
  unsigned int i = 0;
  unsigned int j = 0;

  while (i < t.size() && j < trigrams.size()) {
    if (t[i] < trigrams[j]) {
      i++;
    } else if (t[i] > trigrams[j]) {
      j++;
    } else {
      matches++;
      i++;
      j++;
    }
  }

  return matches;
}
