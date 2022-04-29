#include <iostream>
#include <string>


void printAll(std::ostream & out) { // recursion base case
  out << '\n';
}
template<typename First, typename...Types>
void printAll(std::ostream & out, First const & first, Types const &...rest) {
  out << first;
  if (sizeof...(Types)) {
    out << ", ";
  }
  printAll(out, rest...);
}

int main() {
  int i{42}; double d{1.25}; std::string book{"Lucid C++"};
  printAll(std::cout, i, d, book);
  printAll(std::cout,1);
  printAll(std::cout, "the answer is ", 6*7);
  auto const number = 2;
  printAll(std::cout, 5, " times ", number, " is ", 5 * number, '\n');
}
