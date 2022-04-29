#ifndef SACK_H_
#define SACK_H_


#include <initializer_list>
#include <iterator>
#include <vector> // implementation detail, might change...
#include <random>
#include <stdexcept>
template <typename T>
class Sack
{
  using SackType=std::vector<T>;
  SackType theSack{};

  using size_type=typename SackType::size_type;
  inline static std::mt19937 randengine{}; // not thread safe
  using rand=std::uniform_int_distribution<size_type>;
public:
  bool empty() const { return theSack.empty() ; }
  size_type size() const { return theSack.size();}
  void putInto(T const &item) { theSack.push_back(item);}
  T getOut() &;
  template <typename Elt = T>
  explicit operator std::vector<Elt>() const {
    return std::vector<Elt>(theSack.begin(),theSack.end());
              // () to avoid initializer_list ctor
  }
#if __cplusplus >= 201703L
  explicit Sack(std::initializer_list<T> l):theSack{l}{}
  Sack() = default;
#endif
  //...
};
template <typename T>
T Sack<T>::getOut() & {
  using difference_type=typename SackType::difference_type;
    if (empty()) throw std::logic_error{"empty Sack"};
    size_t const index = rand{0u,size() - 1}(randengine);
    T retval{theSack.at(index)};
    theSack.erase(std::next(theSack.begin(),
        static_cast<difference_type>(index)));
    return retval;
}
template <typename T>
Sack<T> makeSack(std::initializer_list<T> list){
  Sack<T> sack{};
  for (auto const elt : list){
    sack.putInto(elt);
  }
  return sack;
}
#endif /*SACK_H_*/
