#ifndef MIN_WITH_CONCEPT_H_
#define MIN_WITH_CONCEPT_H_
#ifdef __cpp_concepts
#include <concepts>
#endif
namespace MyMin {

template <typename T>
#ifdef __cpp_concepts
requires std::copy_constructible<T> && requires (T a) {
	a < a ;
	{ a < a } -> std::convertible_to<bool>;
}
#endif
T min(T left, T right) {
  return left < right ? left : right;
}

#ifdef __cpp_concepts
template <typename T>
concept LessThanComparable = requires (T a) {
	a < a ;
	{ a < a } -> std::convertible_to<bool>;
};
#endif


template <typename T>
#ifdef __cpp_concepts
requires LessThanComparable<T> && std::copy_constructible<T>
#endif
T max(T left, T right) {
  return !(left < right) ? left : right;
}

#ifdef __cpp_concepts
template <LessThanComparable T>
T const& max_short(T const &l, T const &r) {
  return !(l < r) ? l : r;
}

auto max_shortest(LessThanComparable auto l, LessThanComparable auto r)
requires std::same_as<decltype(l),decltype(r)>
{
  return !(l < r) ? l : r;
}


bool equivalent(LessThanComparable auto left, LessThanComparable auto right)
requires std::same_as<decltype(left),decltype(right)>
{
  return ! ( left < right ) && ! ( right < left );
}
#endif



}

#endif /* MIN_WITH_CONCEPT_H_ */
