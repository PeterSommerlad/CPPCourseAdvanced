#include <fstream>
#include <memory>
#include <ostream>
#include <sstream>

std::unique_ptr<std::ostream>
os_factory(std::string const filename) {
  using namespace std; // for shorter code
  if (filename.size()) {
    return make_unique<ofstream>(filename);
  } else {
    return make_unique<ostringstream>();
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
