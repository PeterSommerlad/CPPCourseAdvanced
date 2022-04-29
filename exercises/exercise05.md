# Exercises Class Templates

##  Introductory Questions
### Static or Dynamic Errors?
When will a template be instantiated? 
*  At compile-time
*  At run-time
*  It depends, if the template is specified as **static** it is instantiated at compile-time otherwise at run-time

### Template Definition
Where do you define a class template and its members?
*  In the header file?
*  In the source file?
*  In both the header and the source file?

### Dependent Types
If you have a member type of another type depending on a template parameter, how do you have to refer to that type?

### Inheritance
How do you refer to members inherited from a dependent type within a class template?

### Template Specialization
Is it neccessary for a (partial) specialization of a class template to provide the same interface (same member functions) as the unspecialized template?


## Examine and Test `Sack<T>`
  
Take the example code including unit tests of the class template Sack

* Can you invent more and better test cases for Sack?
* `std::string_view` has similar problems than `char const *` and can lead to dangling of the content of `Sack<std::string_view>`. Implement a template specialization for that case as we did for `char const *`. Try a variant with implementing the body yourself and a variation where you inherit from `Sack<std::string>`.
* examine the use of the base template and its specializations by using either Cevelop's template information view (need to select -std=c++14) from the test cases or by using CppInsights.
  [https://cppinsights.io/s/634dea53](https://cppinsights.io/s/634dea53)
* What other standard library relationship types might give you similar dangling problems than pointers?


## A vector with backward indexing using negative indices

The goal is to a) get familiar with the standard library's container interface and b) to exercise writing a template class.

Many scripting languages allow dynamic arrays to be indexed with negative indices where `a[-1] ` denotes the last element in the array`a[size-1] `  and `a[-size] ` the first element `a[0] `.

Create a template class dynArray<T> that uses a std::vector<T> as a member (not as a super class) for its implementation. Implement the indexing member functions similar to std::vector for dynArray in a way that negative indices are allowed and every index access is actually bounds checked (use std::vector's facility for that).

*  Provide constructors for the following initializations, as it would be with std::vector (ignore allocator argument versions of std::vector) :
```
dynArray<char> a1{};
dynArray<int> a2{1,2,3,4,5}; // initializer_list
dynArray<std::string> a3(std::istream_iterator<std::string>{std::cin},std::istream_iterator<std::string>{}); // any iterator type!
```

*  Provide a Factory Function template `makedynArray()` that takes an `initializer_list<T>` and returns a dynArray<T> filled with the elements from the initializer list. Create an overload for accepting two iterators as well.
   or provide deduction guides, initialize a dynarray without needing to specify the template argument.


*  Create Unit Tests for all of your template class' behaviors. Best, one or more tests for a feature, before you implement it.
  *  Use different element types for your template class in the tests to prove that it works with different instantiations
  *  you must implement your class in a header file (dynArray.h) in the unit test project, a separate library won't work easily, because a template class lacks a .cpp file with content the linker is happy with.

The following functions of std::vector you **should not implement**:
*  allocator template parameter and functions using it
*  `getallocator()`
*  `reserve()`,`max_size()`
*  `operator=()` -- automatically provided one should be OK
*  `assign()`
*  `data()`
*  `shrink_to_fit()`
*  `emplace()`, `emplace_back()`, `insert()`
*  `swap`
*  `comparison operators`
*  all rvalue-reference overloads (unless you want to)

But you must implement all other members of std::vector by delegating to the corresponding member functions of your template class' data member of type std::vector.


## indexableSet class template (optional)

Create a class template `indexableSet<typename T, typename COMPARE=std::less<T>>` that **inherits** from `std::set<T,COMPARE>` and allows indexing its content like you could do with a `std::vector<T>`. Negative indices should index from the "end" of the set. Provide also member functions `front()` and `back()` that correspond to those of vector.

Write Test cases and implementation code for `indexableSet` for the following aspects:
*  All constructors available for `std::set` have to work identically for `indexableSet`
*  Index access (with `operator[]` and `at()`) should reveal the stored values in sorted order
*  Negative indices should index the set from the end, so that `s![-1]` is the last available (the greatest) element in the set and `s[-s.size()] == s![0] `
*  Provide member functions `front()` and `back()`
*  All of your operations that might result in undefined behavior, because an index is out of range, or no elements exist should throw a corresponding standard exception (`std::out_of_range`).
*  Allow instantiating `indexableSet` with a different compare functor. Demonstrate that with a test case with your own `caselessCompare` functor for `std::string`. (`indexableSet<std::string, caselessCompare>`)

**Note:**
*  Implement the template class `indexableSet` as header-only (`indexableSet.h`) within your CUTE test project.
*  Remember the rules for class templates inheriting from a class that also depends on a template parameter! Otherwise interesting effects for name lookup might happen. Omitting that will cause you to fail!
*  When inheriting constructors from a base class, you will not inherit the deduction guides. Therefore, you will not be able to omit the class template arguments when using `indexableSet` in your tests.



## Optional: Extra Exercise (ACCU Student Code Critique 97)

Can you help the following student with his C++ template problems?

> I have a simple template class that holds a collection of values but sometimes code using the class crashes. I've written as simple test for the class, which works, but I do get a warning about a signed/unsigned mismatch on the for loop. I though using auto would stop that. Is that anything to do with the crash? I've commented out all the other methods apart from add and remove.

--- values.h ---
```cpp
#include <utility>
#include <vector>

#pragma once

// An unordered collection of values
template <typename T>
class Values
{
public:
  void add(T t);
  bool remove(T t);
  std::vector<T> const & values() const
  { return v; }
private:
  std::vector<T> v;
};

// Add a new item
template <typename T>
void Values<T>::add(T t)
{
   v.push_back(t);
}

// Remove an item
// Returns true if removed, false if not present
template <typename T>
bool Values<T>::remove(T t)
{
  bool found(false);

  for (auto i = 0; i != v.size(); ++i)
  {
    if (v[i] == t)
    {
      v[i] = std::move(v.back());
      v.pop_back();
      found = true;
    }
  }
  return found;
}
```
-- test.cpp --
```cpp
#include <iostream>
#include "values.h"

void test()
{
  Values<int> vi;
  for (int i = 0; i != 10; ++i)
  {
    vi.add(i);
  }

  if (!vi.remove(1))
  {
     std::cout << "Can't remove 1\n";
  }

  if (vi.remove(1))
  {
     std::cout << "Can remove 1 twice\n";
  }

  if (!vi.remove(9))
  {
    std::cout << "Can't remove 9\n";
  }
  std::cout << "size: " << vi.values().size()
    << std::endl;
}

int main()
{
  test();
}

```
