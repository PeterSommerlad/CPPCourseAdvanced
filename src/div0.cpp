#include <cassert>
#include <iostream>
#include <cfenv>

int div0(int divident, int divisor) { 
  return divident / divisor;
}

int main(){
    feenableexcept(FE_DIVBYZERO);
    std::cout<<"normal case\n";
    assert(2 == div0(5,2));
    std::cout << "input 0 to trigger error case - ignored\n";
    int maybezero{};
    std::cin >> maybezero;
    auto res =  div0(0,maybezero);
    std::cout << res << " done\n";
}