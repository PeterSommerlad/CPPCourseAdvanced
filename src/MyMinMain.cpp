#include "MyMin.h"
#include <iostrean>
#include <string>

int main(){
  using MyMin::min;
  using namespace std::string_literals;
  std::cout << "min(1,2) : " << min(1,2) << '\n';
  std::cout << "min(1.,2.) : " << min(1.,2.) << '\n';
  std::cout << "min(one,two) : " << min("one","two") << '\n'; // accidental!
  std::cout << "min(three,two) : " << min("three","two") << '\n'; // ??
  std::cout << "min(three,two) : " << min<std::string>("three","two") << '\n'; // ??
  std::cout << "min(three,two) : " << MyMin::min("three"s,"two"s) << '\n'; // ??
//    std::cout << "min(1,1.1) : " << min(1,1.1) << '\n'; // ambiguous
}