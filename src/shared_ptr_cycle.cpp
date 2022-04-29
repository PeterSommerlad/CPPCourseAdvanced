#include <string>
#include <vector>
#include <iostream>
#include <memory>
using HalfElfPtr = std::shared_ptr<struct HalfElf>;
struct HalfElf {
  explicit HalfElf(std::string name) : name{name}{}
  std::string name{};
  std::vector<HalfElfPtr> siblings{};
  // demo only:
  ~HalfElf(){ std::cout << name << " killed\n"; }
};
void middleEarth() {
  auto elrond = std::make_shared<HalfElf>("Elrond");
  auto elros = std::make_shared<HalfElf>("Elros");
  elrond->siblings.push_back(elros);
  elros->siblings.push_back(elrond);
}

int main(){
  std::cout << "creating middleEarth()\n";
  middleEarth();
  std::cout << "anybody dead?\n";
}

// https://godbolt.org/z/Ms8n6vssM
