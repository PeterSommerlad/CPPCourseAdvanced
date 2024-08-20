#ifndef VALUES_H_
#define VALUES_H_

#include <utility>
#include <vector>
#include <algorithm>

// An unordered collection of values
template <typename T>
class Values
{
public:
  void add(T t) &;
  bool remove(T t) &;
  std::vector<T> const & values() const &
  { return v; }
private:
  std::vector<T> v;
};

// Add a new item
template <typename T>
void Values<T>::add(T t) &
{
   v.push_back(t);
}

// Remove an item
// Returns true if removed, false if not present
template <typename T>
bool Values<T>::remove(T t) &
{
#if 1
  bool found{false};
  for (auto i = 0u; i != v.size(); ++i)
  {
    if (v[i] == t)
    {
      v[i] = std::move(v.back());
      v.pop_back();
      found = true;
    }
  }
  return found;
#else
  // better
  auto old_end = end(v);
  auto found_it = v.erase(std::remove(begin(v),end(v),t),end(v));
  return  found_it != old_end;
#endif
}




#endif /* VALUES_H_ */
