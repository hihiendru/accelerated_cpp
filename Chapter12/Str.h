#ifndef GUARD_Str_h
#define GUARD_Str_h

#include <algorithm>  //copy
#include <cstring>    //strlen
#include <iostream>   //istream,ostream
#include <iterator>   //back_inserter

#include "Vec.h"

class Str {
 public:
  // required for write access to data
  friend std::istream& operator>>(std::istream&, Str&);

  typedef Vec<char>::size_type size_type;
  // default constructor, empty Str
  Str() {}
  // Str containing copies of c
  Str(size_type n, char c) : data(n, c) {}
  // Str from null-terminated array of char
  Str(const char* cp) {
    std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
  }
  // Str from range denoted by iterators
  template <class In>
  Str(In b, In e) {
    std::copy(b, e, std::back_inserter(data));
  }
  // operators, size
  size_type size() { return data.size(); }
  char& operator[](size_type i) { return data[i]; }
  const char& operator[](size_type i) const { return data[i]; }
  Str& operator+=(const Str& s) {
    std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
    return *this;
  }

 private:
  Vec<char> data;
};

// non-member operators operators
// input/output: implicit binding of lhs operands
std::istream& operator>>(std::istream& is, Str& s) {
  // obliterate existing values
  s.data.clear();
  // read and discard leading whitespace
  char c;
  while (is.get(c) && isspace(c)) {
    ;  // nothing to do, testing the condition
  }
  // if something to read, continue until next whitespace
  if (is) {
    do
      s.data.push_back(c);
    while (is.get(c) && !isspace(c));
    // if we encounter whitespace, put back on stream
    if (is) {
      is.unget();
    }
  }
  return is;
}
std::ostream& operator<<(std::ostream& os, Str& s) {
  for (Str::size_type i = 0; i < s.size(); ++i) {
    os << s[i];
  }
  return os;
}
// + operator: does not change the state of lhs operand
Str& operator+(const Str& a, const Str& b) {
  Str result = a;
  result += b;
  return result;
}

#endif