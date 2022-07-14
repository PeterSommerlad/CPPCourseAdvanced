# Solution to Exercise 03

## Role Determination


Take a look at the some classes from the standard library and decide which of the class roles (value, relation, polymorphic, scoped manager, unique manager, general manager) they fulfil. Discuss. Consult https://cppreference.com to look at the interface provided. If in doubt, you can even write a small test program, ideally on https://godbolt.org for easy sharing. Note that an individual class(template) can actually fulfil multiple roles according to our categorization.

* [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string)
  * value, general manager
* [`std::vector<int>`](https://en.cppreference.com/w/cpp/container/vector)
  * value, general manager
* [`std::ios_base`](https://en.cppreference.com/w/cpp/io/ios_base)
  * polymorphic base class 
* [`std::fstream`](https://en.cppreference.com/w/cpp/io/basic_fstream)
  * unique manager as leaf in polymorphic hierarchy
* [`std::ostringstream`](https://en.cppreference.com/w/cpp/io/basic_ostringstream)
  * unique manager as leaf in polymorphic hierarchy
* [`std::domain_error`](https://en.cppreference.com/w/cpp/error/domain_error)
  * general manager as leaf in polymorphic hierarchy
* [`std::pair<int,int>`](https://en.cppreference.com/w/cpp/utility/pair)
  * value, depends on template arguments
* [`std::basic_syncbuf`](https://en.cppreference.com/w/cpp/io/basic_syncbuf/basic_syncbuf)
  * unique manager
* [`std::lock_guard`](https://en.cppreference.com/w/cpp/thread/lock_guard)
  * scoped manager
 
Not in this list are relation types, but we mentioned all the obvious ones from the standard library: `std::string_view, std::span, std::reference_wrapper`