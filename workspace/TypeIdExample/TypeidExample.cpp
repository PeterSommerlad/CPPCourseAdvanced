#include <iostream>
#include <string>
#include <cxxabi.h> // __cxa_demangle

void setDummyTo42(){}
struct bar{
	void operator()(){}
};

void match(bool b){
	std::cout << (b?"":"no ") << "match"<<std::endl;
}

std::string demangle(char const *name){
	char *toBeFreed = __cxxabiv1::__cxa_demangle(name,0,0,0);
	std::string result(toBeFreed);
	::free(toBeFreed);
	return result;
}

int main(){
  std::cout << demangle(typeid(&setDummyTo42).name()) << '\n';
  std::cout << demangle(typeid(bar()).name()) << '\n';
  std::cout << demangle(typeid((bar())).name()) << '\n';
	match (typeid(setDummyTo42) == typeid(void()));
	match(typeid(setDummyTo42) == typeid((bar())()));
}
