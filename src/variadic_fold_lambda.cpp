#include <iostream>
#include <string>

auto const suml{ [](auto ... xs){ return (... + xs);} };
auto const sumr{ [](auto ... xs){ return (xs + ... );} };


auto const printAll {
[](std::ostream & out,  auto const &...params) {
  (out << ... << params) << '\n';
}};

auto const printAllCommaSeparated{
[](std::ostream & out,  auto const &...params) {
  bool first{true};
  (out << ... << ((first?(first=false):bool(out << ", ")), params)) << '\n';
}};


int main() {

  std::cout << "suml is " << suml(1,2,3,4,5,6,7,8,9,10.0) << '\n';
  std::cout << "sumr is " << sumr(1,2,3,4,5,6,7,8,9,10.0) << '\n';

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
