# Variable Templates and Type Traits

## Familiarize with existing <type_traits>

Check out the information on [https://en.cppreference.com/w/cpp/meta](https://en.cppreference.com/w/cpp/meta) to get an overview on the type traits provided by the C++ standard library. Chose the traits provided in the "primary type categories" and "composite type categories", if eager, also the "type properties"

Write a test program that checks all of these traits and outputs the result of the checks for the following types:

* `bool`
* `int`
* `void`
* `void *`
* `std::string`
* `struct Base { virtual ~Base() = 0; };`

Note: instead of copy-paste you can employ your knowledge on templates and template template parameters. Instead of using the bool variable templates, like `std::is_integral_v`, you can pass the corresponding class template (without `_v`) to your output function. `typeid(param).name()` can be used to get an approximation of the trait's name. ([https://en.cppreference.com/w/cpp/language/typeid](https://en.cppreference.com/w/cpp/language/typeid))

If the output is unpleasing, because of the compiler's name mangling, you can use the following function to generate a nicer looking name from `type_info::name()`'s output:

```C++
#include <cxxabi.h> // __cxa_demangle

std::string demangle(char const *name){
	char *toBeFreed = __cxxabiv1::__cxa_demangle(name,0,0,0);
	std::string result(toBeFreed);
	::free(toBeFreed);
	return result;
}
```

The traits to consider (assuming `using namespace std;` in local scope) 

```C++
    is_null_pointer, is_floating_point, is_array, is_enum, is_union, is_class, is_function, is_pointer,
    is_lvalue_reference, is_rvalue_reference, is_member_object_pointer, is_member_function_pointer,
    is_fundamental, is_arithmetic, is_scalar, is_object, is_compound, is_reference, is_member_pointer,
    is_const, is_volatile, is_trivial, is_trivially_copyable, is_standard_layout, is_empty,
    is_polymorphic, is_abstract, is_final, is_aggregate, is_signed, is_unsigned
```

A possible main function can look like:

```C++
int main() {
  struct Base{ virtual ~Base()=0;};
  output_traits_for_types<bool,int, int&, int const &, int *, void, void *, std::string, Base>(std::cout);
}
```

but don't sweat it, it requires some indirection, since pack expansion is only possible on the level of expressions (or base classes) and one needs to instantiate each trait and create a default value and pass that list of values to another variadic function that then disects them again.