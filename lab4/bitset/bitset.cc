#include "bitset.h"
#include "bitreference.h"
#include "bitsetiterator.h"

Bitset::Bitset() : bits(0) {}

size_t Bitset::size() const { return BPW; }

bool Bitset::operator[](size_t pos) const { return (bits & (1L << pos)) != 0; }

BitReference Bitset::operator[](size_t pos) { return BitReference(&bits, pos); }

Bitset::iterator Bitset::begin() {
  iterator b(&bits, 0);
  return b;
}

Bitset::iterator Bitset::end() {
  iterator e(&bits, BPW);
  return e;
}
