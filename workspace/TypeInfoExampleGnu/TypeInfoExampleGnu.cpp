#include <typeinfo>
#include <iostream>
#include <string>
#include <cxxabi.h> // __cxa_demangle

std::string demangle(char const *name){
	char *toBeFreed = __cxxabiv1::__cxa_demangle(name,0,0,0);
	std::string result(toBeFreed);
	::free(toBeFreed);
	return result;
}

template <typename T>
void printIdRef(std::ostream &out, T const & t) {
	out << "printIdRef(T const &t): " << demangle(typeid(t).name()) <<'\n';
}
template <typename T>
void printIdVal(std::ostream &out, T t) {
	out << "printIdVal(T t): " << demangle(typeid(t).name()) << '\n';
}

struct Double { double d;};

int main(){
	printIdRef(std::cout, "hello");
	printIdVal(std::cout, "hello");
	printIdRef(std::cout, Double{});
	printIdVal(std::cout, Double{});
}
