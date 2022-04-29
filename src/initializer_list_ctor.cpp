#include <initializer_list> // for std::initializer_list
#include <vector>
#include <ostream>
struct lottery_numbers {
  lottery_numbers(std::initializer_list<int> li):theNumbers{li}{}
  lottery_numbers(int first, int second):theNumbers{first,second}{}
  explicit lottery_numbers(int first):theNumbers(first){} 
  friend std::ostream &operator<<(std::ostream& out,lottery_numbers const& numbers){
    for (auto num:numbers.theNumbers) {
      out << num << ", ";
    }
    return out << "- end\n";
  }
  private:
    std::vector<int> theNumbers{};
};

#include <iostream>

int main(){
  lottery_numbers list1{1,2,3,4,5,6}; // braces
  lottery_numbers two{42,43}; // braces
  lottery_numbers one(0); // round ()
  
  std::cout << list1 << two << one;
  
}
