#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

template <typename T>
T min(T & left, T & right) {
  return left < right ? left : right;
}

std::string min(std::string const & left, std::string const & right) {
  return lexicographical_compare(begin(left), end(left),
				    begin(right), end(right),
				    [](char l, char r) {
    return tolower(l) < tolower(r);
  }) ? left : right;
}

int main() {
	std::string small{"aa"};
	std::string const capital{"ZZ"};
	std::cout << min(small, capital) << '\n'; //ZZ
}
