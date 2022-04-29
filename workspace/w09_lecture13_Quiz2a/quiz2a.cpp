#include <iostream>

template <typename T>
T const &
min(T const & left, T const & right) {
  return left < right ? left : right;
}

int main() {
  std::cout << min("Java", "Rust");
}
