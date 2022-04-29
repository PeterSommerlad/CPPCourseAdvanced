#ifndef MIN_H_
#define MIN_H_

namespace MyMin {
template <typename T>
T min(T left, T right) {
  return left < right ? left : right;
}
}

#endif /* MIN_H_ */
