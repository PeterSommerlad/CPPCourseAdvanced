#include "min.h"
#include <iostream>


struct uncomparable{
	int i;
	friend std::ostream & operator<<(std::ostream& out, uncomparable const &val){
		return out << val.i;
	}
	friend std::istream & operator>>(std::istream& in, uncomparable &var){
		return in>>var.i;
	}
};


int main() {
  using Type=int;//uncomparable;

  Type first{};
  Type second{};
  if (std::cin >> first >> second) {
    auto const smaller = MyMin::min(first, second);
    std::cout << "Smaller of " << first
              << " and " << second
              << " is: " << smaller << '\n';
  }
}
