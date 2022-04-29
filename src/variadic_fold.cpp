#include <iostream>
#include <string>


template<typename...Types>
void printAll(std::ostream & out,  Types const &...params) {
  (out << ... << params) << '\n';
}

template<typename...Types>
void printAllCommaSeparated(std::ostream & out,  Types const &...params) {
  bool first{true};
  (out << ... << ((first?(first=false):bool(out << ", ")), params)) << '\n';
}


int main() {
  int i{42}; double d{1.25}; std::string book{"Lucid C++"};
  printAll(std::cout, i, d, book);
  printAll(std::cout,1);
  printAll(std::cout, "the answer is ", 6*7);
  auto const number = 2;
  printAll(std::cout, 5, " times ", number, " is ", 5 * number, '\n');
  // comma separated
  printAllCommaSeparated(std::cout, i, d, book);
  printAllCommaSeparated(std::cout,1);
  printAllCommaSeparated(std::cout, "the answer is ", 6*7);
  printAllCommaSeparated(std::cout, 5, " times ", number, " is ", 5 * number, '\n');
}
