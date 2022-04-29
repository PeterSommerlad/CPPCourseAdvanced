#include "min_with_concept.h"
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

static_assert(!MyMin::LessThanComparable<uncomparable>);

int main() {
	using Type=int;//uncomparable;

  Type first{};
  Type second{};
  if (std::cin >> first >> second) {
    auto const smaller = MyMin::min(first, second);
    std::cout << "Smaller of " << first
              << " and " << second
              << " is: " << smaller << '\n';
    auto const bigger = MyMin::max(first, second);
    std::cout << "Bigger of " << first
              << " and " << second
              << " is: " << bigger << '\n';
    std::cout << std::boolalpha
    		  << "values are equivalent? "
			  << MyMin::equivalent(first,second) << '\n';
 }
}
