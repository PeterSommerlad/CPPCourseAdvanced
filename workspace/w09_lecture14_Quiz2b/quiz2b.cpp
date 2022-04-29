#include <iostream>
#include <string>

template <typename T>
T const &
_min(T const & left, T const & right) {
  return left < right ? left : right;
}

int main() {
  std::string java{"Java"};
  std::string const rust{"Rust"};
  std::cout << _min(java, rust);
}
