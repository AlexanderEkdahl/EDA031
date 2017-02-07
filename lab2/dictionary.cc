#include "dictionary.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "word.h"

Dictionary::Dictionary() {
  std::ifstream fin("/usr/share/dict/words");
  std::string line;

  while (getline(fin, line)) {
    dictionary.insert(line);

    if (line.size() > 3) {
      std::vector<std::string> trigrams;

      for (unsigned long count = 0; count <= line.size() - 3; ++count) {
        trigrams.push_back(line.substr(count, 3));
      }

      sort(trigrams.begin(), trigrams.end());

      Word w = Word(line, trigrams);
      words[line.size() - 1].push_back(w);
    }
  }
}

bool Dictionary::contains(const std::string& word) const {
  return dictionary.count(word);
}

std::vector<std::string> Dictionary::get_suggestions(
    const std::string& word) const {
  std::vector<std::string> suggestions;
  add_trigram_suggestions(suggestions, word);
  rank_suggestions(suggestions, word);
  trim_suggestions(suggestions);
  return suggestions;
}

void Dictionary::add_trigram_suggestions(std::vector<std::string>& suggestions,
                                         const std::string& word) const {
  std::vector<std::string> trigrams;

  if (word.size() >= 3) {
    for (unsigned long i = 0; i <= word.size() - 3; ++i) {
      trigrams.push_back(word.substr(i, 3));
    }
    sort(trigrams.begin(), trigrams.end());

    // Only check words that are -2 and +1 in size
    for (unsigned long i = word.size() - 2; i <= word.size(); ++i) {
      for (Word w : words[i]) {
        if (w.get_matches(trigrams) >= trigrams.size() / 2) {
          suggestions.push_back(w.get_word());
        }
      }
    }
  }
}

// https://en.wikipedia.org/wiki/Levenshtein_distance
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B
void Dictionary::rank_suggestions(std::vector<std::string>& suggestions,
                                  const std::string& word) const {
  int d[25][25];
  d[0][0] = 0;
  for (unsigned int i = 1; i <= 25; i++) d[i][0] = i;
  for (unsigned int j = 1; j <= 25; j++) d[0][j] = j;

  const std::size_t len1 = word.size();
  std::vector<std::pair<int, std::string> > ranked_suggestions;

  for (unsigned long suggested_place = 0; suggested_place < suggestions.size();
       suggested_place++) {
    const std::string& p = suggestions[suggested_place];
    const std::size_t len2 = p.size();

    for (unsigned int i = 1; i <= len1; ++i) {
      for (unsigned int j = 1; j <= len2; ++j) {
        d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1,
                            d[i - 1][j - 1] + (p[i] == word[j] ? 0 : 1)});
      }
    }

    ranked_suggestions.push_back(make_pair(d[len1][len2], p));
  }

  auto compare = [](std::pair<int, std::string> p1,
                    std::pair<int, std::string> p2) {
    return p1.first < p2.first;
  };
  sort(ranked_suggestions.begin(), ranked_suggestions.end(), compare);
  suggestions.clear();

  auto second = [](const std::pair<int, std::string>& p) { return p.second; };
  transform(ranked_suggestions.begin(), ranked_suggestions.end(),
            back_inserter(suggestions), second);
}

void Dictionary::trim_suggestions(std::vector<std::string>& suggestions) const {
  if (suggestions.size() > 5) {
    suggestions.resize(5);
  }
}
