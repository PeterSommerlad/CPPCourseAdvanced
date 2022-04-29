#include <iostream>
#include <string>

template <typename T>
T const & _min(T const & left, T const & right) {
  return left < right ? left : right;
}

int main() {
	using namespace std::string_literals;
	std::string const & smaller = _min("a"s, "b"s);
	std::cout << "smaller is: " << smaller;
}
