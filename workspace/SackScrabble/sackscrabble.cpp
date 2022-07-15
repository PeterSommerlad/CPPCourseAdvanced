#include "Sack.h"
#include <iterator>
#include <iostream>

int main(){
	Sack<char> scrabble{};
	for (char c='A'; c <= 'Z'; ++c)
		scrabble.putInto(c);
	auto values{scrabble.asVector<int>()};
	copy(values.begin(),values.end(),std::ostream_iterator<int>{std::cout,"; "});
	std::cout << '\n';
	while (!scrabble.empty()){
		std::cout << "play letter: " << scrabble.getOut() << '\n';
	}
}
