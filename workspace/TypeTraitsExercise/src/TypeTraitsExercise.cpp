// godbolt : https://godbolt.org/z/4rYdqhzo1

#include <type_traits>
#include <iostream>
#include <string>
#include <cxxabi.h> // __cxa_demangle
#include <memory>

struct C_deleter{
  template<typename T>
  void operator()(T *p){
    ::free(const_cast<std::remove_const_t<T>*>(p));
  }
};
template<typename T>
using unique_C_ptr = std::unique_ptr<T, C_deleter>;

std::string demangle(char const *name){
  using namespace std; // OK locally
  std::unique_ptr<char const> toBeFreed { __cxxabiv1::__cxa_demangle(name,0,0,0)};
  std::string result(toBeFreed.get());

  ///... exception or return --> leak
  //::free(toBeFreed);
  return result;
}


template<typename TEST,template<typename>typename TRAIT, typename ...REST>
void output_trait(std::ostream &out, TRAIT<TEST> trait, REST...args){
  out << demangle(typeid(TEST).name()) << "'s trait "
      << demangle(typeid(TRAIT<TEST>).name()) << " is "
      << std::boolalpha
      << trait
      << '\n';
  if constexpr(sizeof...(REST)){
    output_trait(out,args...);
  }
}

template<typename TEST, template<typename>typename ...TRAITS>
void output_all_traits(std::ostream &out){
  output_trait(out,TRAITS<TEST>{}...);
}

template<typename TEST>
void output_traits(std::ostream &out){
  using namespace std; // OK locally
  output_all_traits<TEST,
    is_null_pointer, is_floating_point, is_array, is_enum, is_union, is_class, is_function, is_pointer,
    is_lvalue_reference, is_rvalue_reference, is_member_object_pointer, is_member_function_pointer,
    is_fundamental, is_arithmetic, is_scalar, is_object, is_compound, is_reference, is_member_pointer,
    is_const, is_volatile, is_trivial, is_trivially_copyable, is_standard_layout, is_empty,
    is_polymorphic, is_abstract, is_final, is_aggregate, is_signed, is_unsigned
    >(out);
}

template<typename TEST, typename ... REST>
void output_traits_for_types(std::ostream &out){
  output_traits<TEST>(out);
  out << "---------------------------------------------------\n";
  if constexpr (sizeof...(REST)){
    output_traits_for_types<REST...>(out);
  }

}


int main() {
  struct Base{ virtual ~Base()=0;};
  output_traits_for_types<bool>(std::cout);
 // output_traits_for_types<bool,int, int&, int const &, int *, void, void *, std::string, Base>(std::cout);
  std::cout << "---------------------------------------------------\n";
}
