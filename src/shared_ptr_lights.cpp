#include <ostream>
#include <iostream>
#include <memory>

struct Light {
  Light(std::ostream & out) : out{out} {
    out << "Turn on\n";  }
  ~Light() { out << "Turn off\n"; }
  std::ostream & out;
};
int main() {
  auto light{std::make_shared<Light>(std::cout)};
  auto same{light};
  auto last{same}; // 3
  light.reset();   // 2
  same.reset();    // 1
  last.reset();    // deleted
}

int main1() {
  auto light{ std::make_shared<Light>(std::cout) } ;
  std::cout << "- created the original 'Light' shared_ptr..."<< light.use_count()<<"\n";
  auto same { light } ;
  std::cout << "- created the first 'Light' shared_ptr copy..."<< light.use_count()<<"\n";
  auto last { same } ;
  std::cout << "- created the second 'Light' shared_ptr copy..."<< light.use_count()<<"\n";

  light.reset();
  std::cout << "- reset() the original 'Light' shared_ptr..."<< last.use_count()<<"\n";
  same.reset();
  std::cout << "- reset() the first 'Light' shared_ptr copy..."<< last.use_count()<<"\n";
  last.reset();
  std::cout << "- reset() the last 'Light' shared_ptr copy..."<< last.use_count()<<"\n";
}
