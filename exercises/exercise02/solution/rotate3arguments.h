#ifndef ROTATE3ARGUMENTS_H_
#define ROTATE3ARGUMENTS_H_

#include <utility>

template<typename T>
void rotate3arguments(T &a, T& b, T& c) {
  using std::swap; // allow for type-specific ADL pickup of swap overload
	swap(a, b); // using swap avoids unnecessary copying and temporaries
	swap(b, c);
}

#endif /* ROTATE3ARGUMENTS_H_ */
