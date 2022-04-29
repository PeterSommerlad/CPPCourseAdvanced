#include <iostream>
#include <string>



template<typename First, typename...Types>
void printAll(std::ostream & out, First const & first, Types const &...rest) {
  out << first;
  if constexpr (sizeof...(Types)) { // compile-time if
    out << ", ";
    printAll(out, rest...);
  } else {
    out << '\n';
  }
}

int main() {
	int i{42}; double d{1.25}; std::string book{"Lucid C++"};
	printAll(std::cout, i, d, book);
}
