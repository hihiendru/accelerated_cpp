#include "Str2.h"
#include <iostream>
using std::endl;
using std::cin;
using std::cout;


int ch12_1(){
  Str2 S;
  S = "hello";
  Str2 W = "world Str2";
  S += W;
  cout << S << endl;

  Str2 s("hello");   // construct s
  Str2 t = "hello";  // initialize t
  s = "hello";      // assign a new value to s
  Str2 s1 = "test";
  Str2 s2 = "ing";
  cout << s << endl;
  cout << "Enter a Str2 string: ";
  cin >> s;           // use the input operator to read a string
  cout << s << endl;  // use the output operator to write a string
  s[3];               // use the index operator to access a character
  s1 + s2;            // use the addition operator to concatenate two strings

  Str2 name = "Andrew ver. Str2";
  Str2 greeting = "Hello, " + name + "!";

  Str2 temp1("Hello, ");      // Str::Str(const char*)
  Str2 temp2 = temp1 + name;  // operator*(const Str&, const Str&)
  Str2 temp3("!");            // Str::Str(const char*)
  greeting = temp2 + temp3;  // operator*(const Str&, const Str&)

  cout << greeting << endl;
  return 0;
}