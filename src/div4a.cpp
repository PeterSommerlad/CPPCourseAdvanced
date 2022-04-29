#include <cassert>
#include <iostream>
struct DivByZero{};

int div4a(int divident, int divisor) noexcept { 
    if (divisor == 0) throw DivByZero{};
  return divident / divisor;
}

int main(){
    std::cout<<"normal case\n";
    assert(2 == div4a(5,2));
    std::cout << "input 0 to trigger error case:\n";
    int maybezero{};
    std::cin >> maybezero;
    auto res =  div4a(42,maybezero);
    std::cout << res << " done\n";
}