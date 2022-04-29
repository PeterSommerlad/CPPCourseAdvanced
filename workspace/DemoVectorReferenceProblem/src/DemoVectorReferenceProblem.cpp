#include <vector>
#include <iostream>
#include <string>

auto make = [](auto ... vals){
	return std::vector{std::string{vals}...};
};

int main() {
  std::string  &s = make("hello","world").at(1); // immediately dangles!

  std::cout << "Hello " << s <<'\n';
  s.append("!!!");
  std::cout << "Hello " << s <<'\n';

}
