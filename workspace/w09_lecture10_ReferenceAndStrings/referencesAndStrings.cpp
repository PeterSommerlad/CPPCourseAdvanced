#include <iostream>
#include <string>

template <typename T>
T const & _min(T const & left, T const & right) {
  return left < right ? left : right;
}

int main() {
	using namespace std::string_literals;
	std::cout << _min("C++"s, "Java"s);
}
