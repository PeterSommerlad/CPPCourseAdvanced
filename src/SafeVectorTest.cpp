#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

template<typename T>
struct safeVector:std::vector<T> {
using std::vector<T>::vector;
using size_type=typename std::vector<T>::size_type;
decltype(auto) operator[](size_type i) & { // or T&
	return this->at(i);
}
decltype(auto) operator[](size_type i) const & { // or T const &
	return this->at(i);
}
T& front() & {
  return this->at(0);
}
T const & front() const & {
  return this->at(0);
}
T& back() & {
  return this->at(this->size()-1);
}
T const & back() const & {
  return this->at(this->size()-1);
}
};
// needs deduction guide
template<typename ITER>
safeVector(ITER,ITER) -> safeVector<typename std::iterator_traits<ITER>::value_type>;
template<typename T>
safeVector(std::initializer_list<T>) -> safeVector<T>;
template<typename T>
safeVector(typename safeVector<T>::size_type,T) -> safeVector<T>;

void constructSafeVector() {
	safeVector<int> sv{};
	ASSERT_EQUAL(0,sv.size());
}
void constructFromInitializerList(){
	safeVector<std::string> sv{"eins","zwo","dry"};
	ASSERT_EQUAL(3,sv.size());
}
void constructFromIterators(){
	std::string s{"hello"};
	safeVector sv(begin(s),end(s));
	ASSERT_EQUAL(s.size(),sv.size());
}

void throwsWithLargeIndex(){
	safeVector sv(10u,1);
	ASSERT_EQUAL(10,sv.size());
	ASSERT_THROWS(sv[sv.size()],std::out_of_range);
}
void throwsWhenEmpty(){
	safeVector<bool> sv{};
	ASSERT_THROWS(sv[0],std::out_of_range);
}




void canChangeWithIndex(){
	safeVector<unsigned> sv{3,4,5};
	ASSERT_EQUAL(4,sv[1]);
	sv[1]++;
	ASSERT_EQUAL(5,sv[1]);
}
void cantChangeWithConstVector(){
	safeVector<std::string> const sv{"eins","zwo","dry"};
	ASSERT_EQUAL("dry",sv.back());
	//sv[2]=""; // shouldn't compile
}

void FrontWorksWithLValue(){
  safeVector v{1,2,3};
  ASSERT_EQUAL(1,v.front());
}
void FrontOnEmptyThrows(){
  safeVector v{1,2,3};
  v.clear();
  ASSERT_THROWS(v.front(),std::out_of_range);
}

void BackWorksWithLValue(){
  safeVector v{1,2,3};
  ASSERT_EQUAL(3,v.back());
}
void BacktOnEmptyThrows(){
  safeVector v{1,2,3};
  v.clear();
  ASSERT_THROWS(v.back(),std::out_of_range);
}



void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(constructSafeVector));
	s.push_back(CUTE(constructFromInitializerList));
	s.push_back(CUTE(constructFromIterators));
	s.push_back(CUTE(throwsWithLargeIndex));
	s.push_back(CUTE(canChangeWithIndex));
	s.push_back(CUTE(cantChangeWithConstVector));
	s.push_back(CUTE(throwsWhenEmpty));
	s.push_back(CUTE(FrontWorksWithLValue));
	s.push_back(CUTE(FrontOnEmptyThrows));
	s.push_back(CUTE(BackWorksWithLValue));
	s.push_back(CUTE(BacktOnEmptyThrows));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



