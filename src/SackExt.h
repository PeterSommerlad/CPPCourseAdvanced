#ifndef SACKEXT_H_
#define SACKEXT_H_
#include <vector>
#include <random>
#include <stdexcept>
#include <initializer_list>
#include <iterator>

template<typename T, template<typename ...> typename container=std::vector>
class Sack
{
  using SackType=container<T>;
  SackType theSack {};
  using size_type=typename SackType::size_type;
  using difference_type=typename SackType::difference_type;
  inline static std::mt19937 randengine {std::random_device {}()};
  using rand=std::uniform_int_distribution<difference_type>;

public:
  Sack()=default;
  template <typename ITER>
  Sack(ITER b, ITER e):theSack(b,e) {}
  Sack(std::initializer_list<T> il):theSack(il) {}
  Sack(size_type n, T elt):theSack(n,elt) {}
  bool empty() const {return theSack.empty();}
  size_type size() const {return theSack.size();}
  void putInto(T const &item) {theSack.insert(theSack.end(),item);}
  T getOut() {
    if (empty()) throw std::logic_error {"empty Sack"};
    difference_type index = rand {0,static_cast<difference_type>(size()-1)}(randengine);
    auto iter=std::next(begin(theSack),index);
    T retval {*iter};
    theSack.erase(iter);
    return retval;
  }
  template <typename Elt=T>
  std::vector<Elt> asVector() const {
    return std::vector<Elt>{begin(theSack),end(theSack)};
  }
  template <typename Elt>
  explicit operator std::vector<Elt>() const {
    return std::vector<Elt>{begin(theSack),end(theSack)};
  }
};


template<typename ITER, template<typename ...> typename container=std::vector>
Sack(ITER,ITER)->Sack<std::iter_value_t<ITER>, container>;
//pre C++20: ->Sack<typename std::iterator_traits<ITER>::value_type, container>

template<typename T>
Sack<T> makeSack(std::initializer_list<T> list) {
  return Sack<T> { list };
}
template<typename T>
Sack<T> makeSack1(std::initializer_list<T> list) {
  Sack<T> sack { };
  for (auto it = list.begin(); it != list.end(); ++it)
    sack.putInto(*it);
  return sack;
}
template<typename T>
Sack<T> makeSack2(std::initializer_list<T> list) {
  Sack<T> sack { };
  for (auto const &elt : list)
    sack.putInto(elt);
  return sack;
}
template<typename T>
Sack<T> makeSack3(std::initializer_list<T> list) {
  return Sack<T>(list.begin(), list.end());
}
template<template<typename ...> class container,typename T>
Sack<T,container> makeOtherSack(std::initializer_list<T> list) {
  return Sack<T,container> {list};
}
#include <set>

template<typename T>
auto makeSetSack(std::initializer_list<T> list) {
  return Sack<T, std::set>(begin(list), end(list));
}
template<typename ITER>
auto makeSetSack(ITER b, ITER e) {
  return Sack<typename std::iterator_traits<ITER>::value_type, std::set>(b, e);
}

template<typename T>
using SetSack = Sack<T,std::set>;


#endif /*SACK_H_*/
