#include <fstream>
#include <memory>
#include <ostream>
#include <sstream>

std::shared_ptr<std::ostream> os_factory(std::string filename) {
  using namespace std;

  if (filename.size()) {
    return make_shared<ofstream>(filename);
  } else {
    return make_shared<ostringstream>();
  }
}

int main(){
  auto out = os_factory("");
  if (out) {
    (*out) << "Hello world\n";
  }

  auto fileout = os_factory("hello.txt");
  if (fileout) {
    (*fileout) << "Hello, world!\n";
  }
}
