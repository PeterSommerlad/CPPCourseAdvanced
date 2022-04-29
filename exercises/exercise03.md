# Exercise 03: Class Special Member Functions

Goal is to understand object lifetime and observe it via a Tracer class. In general, it is advisable to write classes in a way that the compiler-provided special member functions just work.

## Observe Tracer

Look at [https://godbolt.org/z/v58E71Tfd](https://godbolt.org/z/v58E71Tfd) and try to explain the differences in output between MSVC and gcc, if any.

## Observe TracerMove

look at [https://godbolt.org/z/37W8KoefG](https://godbolt.org/z/37W8KoefG) and try to explain the differences in output between MSVC and gcc, if any.

Why is the output for both compilers the same, if you put parentheses around the return value in function `bar()`:

[https://godbolt.org/z/s48r3Wscf](https://godbolt.org/z/s48r3Wscf)

## Test Cases for Tracer.h

Copy the following header into a new CUTE test project and write test cases for that Tracer class.

```C++
#ifndef TRACER_H_
#define TRACER_H_

#include <ostream>
#include <string>
struct Tracer{
  explicit Tracer(std::string name, std::ostream &out)
  :name{name}, out{out}{
    out << "Tracer created: " << name << '\n';
  }
  ~Tracer(){
    out << "Tracer destroyed: " << name << '\n';
  }
  Tracer(Tracer const& other)
  :name{other.name+" copy"},out{other.out}{
    out << "Tracer copied: " << name << '\n';
  }
  void show() const {
    out << "Tracer: " << name << '\n';
  }
  std::string name{};
  std::ostream &out;
};


#endif /* TRACER_H_ */
```

What happens if you try to assign to an existing Tracer object?

```C++
void testAssignment() {
  std::ostringstream out{};
  {
    Tracer first{"1", out};
    Tracer second{"2",out};
    first = second;
  }
  ASSERT_EQUAL(
R"(Tracer created: 1
Tracer created: 2
Tracer copy=: 1
Tracer now : 2 copy= 
Tracer destroyed: 2
Tracer destroyed: 2 copy= 
)"
      ,out.str());
}
```

Tip: try replacing the reference member of the tracer class with a member variable of type `std::reference_wrapper<std::ostream>`. This also requires explicit obtaining the stored reference by using the .get() member function, because the overloaded shift operators cannot trigger the implicit conversion.


## Test Cases for full Tracer

Extend the `class Tracer` to include all special member functions: copy-assignment, move-constructor, move-assignment and create corresponding test cases that demonstrate how the operations influence the output.

Write test cases for each of the individual operations and those that demonstrate if named-return-value optimization actually happens. 

Example list of test cases:

```C++
  s.push_back(CUTE(testCtor));
  s.push_back(CUTE(testDtor));
  s.push_back(CUTE(testCopyConstruction));
  s.push_back(CUTE(testMoveConstruction));
  s.push_back(CUTE(testWithNRVO));
  s.push_back(CUTE(testWithoutNRVO));
  s.push_back(CUTE(testReturnFromTmp));
  s.push_back(CUTE(testAssignment));
  s.push_back(CUTE(testMoveAssignment));
```