#include <ios>
#include <iostream>
#include <memory>
#include <utility>

// it is ridiculous to use unique_ptr for int !!!
int main() {
  std::cout << std::boolalpha;
  auto pi = std::make_unique<int>(42);
  std::cout << "*pi = " << *pi << '\n';
  std::cout << "pi.valid? " << static_cast<bool>(pi) << '\n';
  auto const pj = std::move(pi);
  std::cout << "*pj = " << *pj << '\n';
  std::cout << "pi.valid? " << static_cast<bool>(pi) << '\n';
}
