#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <string>
#include <sstream>




template<typename T>
struct parent {
  int foo() const {
    return 42;
  }
  static int const bar { 43 };
};
int foo() {
  return 1;
}
double const bar { 3.14 };
template<typename T>
struct gotchas: parent<T> {
  std::string demo() const {
    std::ostringstream result { };
    result << bar << " bar \n";
    result << this->bar << " this->bar \n";
    result << gotchas::bar << " gotchas::bar\n";
    result << foo() << " foo() \n";
    result << this->foo() << " this->foo() \n";
    return result.str();
  }
};

void constructionFromIteratorPair() {
  gotchas<int> demo { };
  ASSERT_EQUAL("3.14 bar \n"
      "43 this->bar \n"
      "43 gotchas::bar\n"
      "1 foo() \n"
      "42 this->foo() \n", demo.demo());

}

void runSuite() {
  cute::suite s;
  //TODO add your test here
  s.push_back(CUTE(constructionFromIteratorPair));
  cute::ide_listener lis;
  cute::makeRunner(lis)(s, "The Suite");
}

int main() {
  runSuite();
  return 0;
}

