#include <iostream>

template <typename F, typename...T>
F min(F const & first, T const &...rest) {
  auto const & restMin = min(rest...);
  return first < restMin ? first : restMin;
}

int main() {
  std::cout << min(3, 1, 4, 1, 5);
}
