#ifndef LIMITNUMBEROFINSTANCES_H_
#define LIMITNUMBEROFINSTANCES_H_

#include <stdexcept>
#include <atomic>
template<typename TOBELIMITED, size_t maxNumberOfInstances>
class LimitNofInstances {
  static inline std::atomic<size_t> counter;
protected:
  void checkNofInstances() {
    if (counter == maxNumberOfInstances)
      throw std::logic_error("too many instances");
  }
  LimitNofInstances() {
    checkNofInstances();
    ++counter;
  }
  ~LimitNofInstances() {
    --counter;
  }
  LimitNofInstances(const LimitNofInstances&) {
    checkNofInstances();
    ++counter;
  }
  // no need to count, works without definition:
  //LimitNofInstances& operator=(LimitNofInstances const &) & = default;
  //no need to define move operations, copy is OK
};
// C++17 inline static defines correctly, no need:
//template <typename TOBELIMITED, unsigned int maxNumberOfInstances>
//std::atomic<size_t>
//LimitNofInstances<TOBELIMITED,maxNumberOfInstances>::counter{0};
#endif /* LIMITNUMBEROFINSTANCES_H_ */
