#ifndef SACKSPECIALIZATIONS_H_
#define SACKSPECIALIZATIONS_H_


template <typename T> class Sack; // forward declaration

template <typename T>
struct Sack<T*>
{
  ~Sack()=delete;
};
//-----
#include <string>
#include "Sack.h"
template <>
struct Sack<char const *>
: Sack<std::string> {
  using Sack<std::string>::Sack;
};
//
//	using SackType = std::vector<std::string>;
//	using size_type = SackType::size_type;
//	SackType theSack;
//public:
//	// no explicit ctor/dtor required
//	bool empty() const {
//		return theSack.empty();
//	}
//	size_type size() const {
//		return theSack.size();
//	}
//	void putInto(char const *item) { theSack.push_back(item);}
//	std::string getOut() {
//		if (empty()) throw std::logic_error{"empty Sack"};
//		std::string result=theSack.back();
//		theSack.pop_back();
//		return result;
//	}
//};
#endif /*SACKSPECIALIZATIONS_H_*/
