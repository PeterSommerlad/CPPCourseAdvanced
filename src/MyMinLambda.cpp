#include <iostream>
#include <string>

namespace MyMinLambda {
auto const min{ [](auto a, auto b){return a < b ? a : b;}};
}
int main(){
  using MyMinLambda::min; // min from namespace std:: is hidden
  using namespace std::string_literals;
  using std::cout;
  cout << "min(1,2) : " << min(1,2) << '\n';
  cout << "min(1.1,2) : " << min(1.1,2) << '\n';
  cout << "min(one,two) : " << min("one","two") << '\n'; // accidental!
  cout << "min(three,two) : " << min("three","two") << '\n'; // ??
  cout << "min(three,two) : " << min("three"s,"two"s) << '\n'; // works
  cout << "min(1,1.1) : " << min(1,1.1) << '\n'; 
}