#include "demangle.h"

#include <cstdlib>
#include <cxxabi.h>
#include <memory>

std::string demangle(std::string const & name) {
  auto cleanup = [] (char * ptr){
    free(ptr);
  };

  std::unique_ptr<char, decltype(cleanup)> toBeFreed {
    __cxxabiv1::__cxa_demangle(name.c_str(), 0, 0, 0),
    cleanup
  };

  std::string result(toBeFreed.get());
  return result;
}
