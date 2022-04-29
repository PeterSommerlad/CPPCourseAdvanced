# Exercise 02 -  Function Templates

## Function Template `median()`

* Write a function template `median(a, b, c)` taking three arguments of the same type and returning the one in the middle, i.e., neither min/max.
  ASSERT_EQUAL(2, median(1,2,3));
* Provide more useful unit tests for your function template with different types.
* **Hint:** You can implement the function in a header file within your CUTE test project.

## Function Template `rotate3arguments()`

* Write a function template `rotate3arguments` taking three variables of the same type as arguments and exchanging the values, so that a obtains the value of `b`, `b` of `c`, and `c` of `a`.
* Provide useful unit tests for your function with different argument types, i.e., `int`{.cpp}, `std::string`{.cpp}, `std::vector<int>`{.cpp}
* What is the "concept" of your template argument? 
* **Hint:** You can implement the function in a header file within your CUTE test project.
* **Hint:** employ the `std::swap()` function to exchange the content of two variables

## Variadic Function Template `readln(std::istream&, ...)`

* Write a variadic function template `readln(std::istream&, ...)` that takes a variable number of reference arguments and uses `operator>>` to read in successive values from a line read from the `std::istream`.
* Create useful unit tests for your function(s). Consider the cases with 0, 1, 2, or more arguments.
* What is the "concept" of your template arguments?
* **Hint:** you might need to create a second function that takes an `std::istream` and reads all values from it, whereas `readln` just reads a line and passes that line as an `std::istringstream` to the second function.


## (extra) `printLnSeparated` as lambda

* create a variadic lambda named `printLnSeparated`{.cpp} that uses fold expressions to create the output separated with a comma and a space each, but only between elements.

```C++
 std::ostringstream out{};
 printLnSeparated(out, 1,"3.14",'a', "Peter");
 ASSERT_EQUAL("1, 3.14, a, Peter\n",out.str());
```

Tip: You need to make use of the comma operator and may be a `bool`{.cpp} flag to sneak in an outputting subexpression.

Useful starting test cases:

```C++
void testWitJustNewline(){
  std::ostringstream out{};
  printLnSeparated(out);
  ASSERT_EQUAL("\n",out.str());
}
void testSingleElementNoComma(){
  std::ostringstream out{};
  printLnSeparated(out, 1);
  ASSERT_EQUAL("1\n",out.str());
}

void testTwoElementsSeparatedByComma(){
  std::ostringstream out{};
  printLnSeparated(out, 1, "two");
  ASSERT_EQUAL("1, two\n",out.str());
}
```
