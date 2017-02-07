#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream fin("/usr/share/dict/words");
  std::ofstream fout("words.txt");
  std::string line;

  while (getline(fin, line)) {
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    std::vector<std::string> trigrams;

    if (line.size() > 3) {
      unsigned long count;
      for (count = 0; count <= line.size() - 3; ++count) {
        trigrams.push_back(line.substr(count, 3));
      }

      sort(trigrams.begin(), trigrams.end());

      fout << line << " " << count;
      for (auto it = trigrams.begin(); it != trigrams.end(); ++it) {
        fout << " " << *it;
      }

      fout << std::endl;
    } else {
      fout << line << " 0" << std::endl;
    }
  }
}
