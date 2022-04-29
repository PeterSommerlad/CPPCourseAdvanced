#include "plain_demangle.h"

#include <cstdlib>
#include <cxxabi.h>
#include <memory>

struct free_deleter {
  template<typename T>
  void operator()(T * p) const {
    free(const_cast<std::remove_const_t<T> *>(p));
  }
};

template<typename T>
using unique_C_ptr = std::unique_ptr<T, free_deleter>;

std::string plain_demangle(char const * name) {
  unique_C_ptr<char> toBeFreed{__cxxabiv1::__cxa_demangle(name, 0, 0, 0)};
  std::string result(toBeFreed.get());
  return result;
}
