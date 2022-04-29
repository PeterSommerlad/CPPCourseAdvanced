// taken from https://github.com/PeterSommerlad/PSRangeCounter
#ifndef RANGE_COUNTER_H_
#define RANGE_COUNTER_H_

#include <iterator>    // for iterator_traits



namespace ps_counter {
enum class range:size_t{};
enum class iterator:size_t{};
enum class reverse_range:size_t{};
enum class reverse_iterator:size_t{};


constexpr auto
begin(range){
  return iterator{};
}
constexpr auto
end(range const r){
  return iterator(r);
}

constexpr auto
rbegin(range const r){
  return reverse_iterator(r);
}
constexpr auto
rend(range ){
  return reverse_iterator{};
}

constexpr auto
operator*(iterator const it){
  return static_cast<size_t>(it);
}
constexpr auto&
operator++(iterator &it){
  return it = iterator{*it+1};
}
constexpr auto
operator++(iterator &it,int){
  auto res=it;
  ++it;
  return res;
}


constexpr auto
begin(reverse_range const r){
  return reverse_iterator(r);
}
constexpr auto
end(reverse_range){
  return reverse_iterator{};
}

constexpr auto
rbegin(reverse_range){
  return iterator{};
}
constexpr auto
rend(reverse_range  const r){
  return iterator(r);
}

constexpr auto
operator*(reverse_iterator const it){
  return static_cast<size_t>(it)-1;
}
constexpr auto&
operator++(reverse_iterator &it){
  return it = reverse_iterator{*it};
}
constexpr auto
operator++(reverse_iterator &it,int){
  auto res=it;
  ++it;
  return res;
}

constexpr auto reverse(range r){
  return reverse_range{*end(r)};
}
constexpr auto reverse(reverse_range r){
  return range{1 + *begin(r)};
}

inline namespace literals {

#ifdef __cpp_consteval
#define CONSTEVAL consteval
# else
#define CONSTEVAL constexpr
#endif

CONSTEVAL auto
operator"" _times(unsigned long long const count){
  return range{count};
}
CONSTEVAL auto
operator"" _up_to(unsigned long long const count){
  return range{count};
}
CONSTEVAL auto
operator"" _down_from(unsigned long long const count){
  return reverse_range{count};
}
#undef CONSTEVAL
}
}
namespace std{
template<>
struct iterator_traits<ps_counter::iterator>{
  using iterator_category=input_iterator_tag;
  using value_type=decltype(*ps_counter::iterator{});
  using difference_type=ptrdiff_t;
  using pointer = value_type const *;
  using reference = value_type const &;
};
template<>
struct iterator_traits<ps_counter::reverse_iterator>{
  using iterator_category=input_iterator_tag;
  using value_type=decltype(*ps_counter::reverse_iterator{});
  using difference_type=ptrdiff_t;
  using pointer = value_type const *;
  using reference = value_type const &;
};
}


#endif /* RANGE_COUNTER_H_ */

