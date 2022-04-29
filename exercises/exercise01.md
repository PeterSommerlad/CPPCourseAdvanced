# Exercise 01 - Error Handling Strategies

Take the following function:

```{.cpp }
int divide(int divident, int divisor) { 
  return divident / divisor;
}
```

and create versions of it for all the discussed error handling strategies (`div1, div2, div2a, div2b, div3`{.cpp} - with an additional reference parameter, `div4, div4a`{.cpp})

Detect division by zero for those that provide error detection and change the function signature and body accordingly.

Write CUTE test cases for each of the functions demonstrating the successful case as well as at least one error case.

For the functions `div4a`{.cpp} use the following compiler explorer environment for your experiments, since they can cause undefined behavior or program termination.
The successful execution can be checked by using the `assert()`{.cpp} macro from the header `#include<cassert>`{.cpp}.
  
[https://godbolt.org/z/vTKns9xP4](https://godbolt.org/z/vTKns9xP4)

You can just create a single CUTE project in Cevelop and create the test functions and division functions within its generated Test.cpp file.

Don't forget to `#include`{.cpp} `<optional>`{.cpp} and `<variant>`{.cpp} when creating `div2a`{.cpp} and `div2b`{.cpp}. 
  
What would be a good value of type `int`{.cpp} to use as error return for `div2`{.cpp}?

What is your favorite error handling strategy from a usage side as shown in the test cases?

Which of the error-handling strategies allows to specify the function as a wide contract function (marked with `noexcept`{.cpp })?
