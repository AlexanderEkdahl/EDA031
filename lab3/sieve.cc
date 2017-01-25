#include <string>
#include <iostream>

std::string find_primes(int nbr) {
  unsigned int m = nbr + 1;
  std::string primes(m, 'P');

  primes[0] = primes[1] = 'C';

  for (unsigned int i = 2; i < m; i++) {
    if (primes[i] == 'P') {
      for (unsigned int j = 2; j * i < m; j++) {
        primes[j * i] = 'C';
      }
    }
  }
  return primes;
}

int main() {
  std::string primes = find_primes(200);
  for (int i = 0; i <= 200; i++) {
    if (primes[i] == 'P') {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;

  primes = find_primes(100000);
  std::cout << primes.find_last_of('P') << std::endl;
}
