#include <iostream>
#include <string>

template <typename T>
T min(T left, T right) {
  return left < right ? left : right;
}

template <typename T>
T * min(T * left, T * right) {
  return *left < *right ? left : right;
}

char const * min(char const * left,
                 char const * right) {
  return std::string{left} < std::string{right} ? left : right;
}

int main() {
  std::cout << min("Gregor Clegane", "Tyrion Lannister") << '\n';
  std::cout << min("Samwell Tarly", "Sansa Stark") << '\n';
}

