#include "templatewithstaticmember.h"
#include "setToDummy.h"
#include <iostream>
int main(){
	std::cout << staticmember<double>::dummy << '\n';
	std::cout << staticmember<int>::dummy << '\n';
	std::cout << foo() << '\n';
	std::cout << staticmember<int>::dummy << '\n';
}
