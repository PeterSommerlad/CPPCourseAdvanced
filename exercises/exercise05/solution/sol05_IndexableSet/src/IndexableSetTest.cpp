#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

// could be separate header for actual use:
//----- indexableSet.h
#include <set>
#include <stdexcept>
#include <iterator>


template<typename T,typename CMP=std::less<>> class indexableSet {
  using SetType=std::set<T,CMP>;
  using size_type=typename SetType::size_type;
  SetType s;
public:
  using iterator=typename SetType::iterator;
  using const_iterator=typename SetType::const_iterator;
  using reverse_iterator=typename SetType::reverse_iterator;
  using const_reverse_iterator=typename SetType::const_reverse_iterator;
  indexableSet()=default;
  indexableSet(std::initializer_list<T> li, CMP cmp=CMP{}):s{li, cmp}{}
  template <typename ITER>
  indexableSet(ITER b, ITER e, CMP cmp=CMP{}):s(b,e,cmp){}
  size_type size() const {
    return s.size();
  }
  bool empty() const {
    return s.empty();
  }
  // make all reference/iterator returning member lvalue-ref qualified
  // to avoid lifetime issues with temporary objects
  auto insert(T const& i) & {
    return s.insert(i);
  }
  auto erase(T const& i) & {
    return s.erase(i);
  }
  auto find(T const & i) const & {
    return s.find(i);
  }
  size_type count(T const & i) const & {
    return s.count(i);
  }
  auto equal_range(T const & i) const & {
    return s.equal_range(i);
  }
  auto lower_bound(T const & i) const & {
    return s.lower_bound(i);
  }
  auto upper_bound(T const & i) const & {
    return s.upper_bound(i);
  }
  T const & operator[](size_type index) const & {
    return at(index);
  }
  T const & at(size_type index) const & {
    if (index >= size()) throw std::out_of_range{"indexableSet::operator[] out of range"};
    auto iter=s.begin();
    std::advance(iter,index);
    return *iter;
  }
  const_iterator begin() const & { return s.begin(); }
  const_iterator cbegin() const & { return s.cbegin(); }
  const_iterator end() const & { return s.end(); }
  const_iterator cend() const & { return s.cend(); }
  const_reverse_iterator rbegin() const & { return s.rbegin(); }
  const_reverse_iterator crbegin() const & { return s.crbegin(); }
  const_reverse_iterator rend() const & { return s.rend(); }
  const_reverse_iterator crend() const & { return s.crend(); }
};
template<typename ITER>
indexableSet(ITER b, ITER e) -> indexableSet<typename std::iterator_traits<ITER>::value_type>;

template <typename ITER, typename CMP>
indexableSet(ITER b, ITER e, CMP cmp) -> indexableSet<typename std::iterator_traits<ITER>::value_type, CMP>;



template <typename T,typename CMP=std::less<>>
indexableSet<T,CMP> makeIndexableSet(std::initializer_list<T> li,CMP compare=CMP{}){
  return indexableSet<T,CMP>{li};
}
template <typename ITER, typename CMP=std::less<>>
auto makeIndexableSetIter(ITER b, ITER e, CMP compare=CMP{})
-> indexableSet<typename std::iterator_traits<ITER>::value_type, CMP> {
  return indexableSet<typename std::iterator_traits<ITER>::value_type, CMP>(b,e);
}

// -------------- ^^^ indexableSet.h

void constructIndexableSet(){
  indexableSet<int> is{};
  ASSERT_EQUAL(0,is.size());
  ASSERT(is.empty());
}
void insertIntoIndexableSetAndIndexIt(){
  indexableSet<int> is{};
  is.insert(42);
  ASSERT_EQUAL(1,is.size());
  ASSERT_EQUAL(42,is[0]);
  ASSERT_EQUAL(42,is.at(0));
  ASSERT_THROWS(is[1],std::out_of_range);
}
void constructIndexableSetFromInitializerList(){
  indexableSet<char> is{'s','a','n','t','a'};
  ASSERT_EQUAL(4,is.size());
  ASSERT_EQUAL('a',is[0]);
  ASSERT_EQUAL('t',is[3]);
}
void constructIndexableSetFromRange(){
  std::string const s{"claus"};
  indexableSet<char> is(s.begin(),s.end());
  std::string t(is.begin(),is.end());
  ASSERT_EQUAL("aclsu",t);
  ASSERT_EQUAL(s.size(),is.size());
  ASSERT_EQUAL('u',is.at(s.size()-1));
  ASSERT_EQUAL('a',is.at(0));
}
void IndexableSetIterators(){
  indexableSet<int> const is{5,4,3,2,1};
  ASSERT_EQUAL(1,*is.cbegin());
  auto it=is.cbegin();
  for (int i{1}; it != is.cend(); ++it, ++i){
    ASSERT_EQUAL(i,*it);
  }
}
void ReverseIteratorsIndexableSet(){
  indexableSet<char> is{'x','m','a','s'};
  ASSERT_EQUAL('x',*is.rbegin());
  std::string s(is.rbegin(),is.rend());
  ASSERT_EQUAL("xsma",s);
  std::string s2{is.crbegin(),is.crend()};
  ASSERT_EQUAL("xsma",s2);
}

void checkFactorySimple(){
  auto is=makeIndexableSet({3,2,1,2,3});
  ASSERT_EQUAL(3,is.size());
  ASSERT_EQUAL(1,*is.begin());
}
void checkFactoryGreaterSort(){
  auto is=makeIndexableSet({1,2,3,2,1},std::greater<int>{});
  ASSERT_EQUAL(3,is.size());
  ASSERT_EQUAL(3,*is.begin());
}
void checkFactoryFromIterators(){
  std::string s{"santaclaus"};
  auto is=makeIndexableSetIter(s.cbegin(),s.cend());
  ASSERT_EQUAL("aclnstu",std::string(is.begin(),is.end()));
}
void checkFactoryFromIteratorsGreater(){
  std::string s{"santaclaus"};
  auto is=makeIndexableSetIter(s.cbegin(),s.cend(), std::greater{});
  ASSERT_EQUAL("utsnlca",std::string(is.begin(),is.end()));
}
void checkCTADSimple(){
  auto is=indexableSet({3,2,1,2,3});
  ASSERT_EQUAL(3,is.size());
  ASSERT_EQUAL(1,*is.begin());
}
void checkCTADGreaterSort(){
  auto is=indexableSet({1,2,3,2,1},std::greater<int>{});
  ASSERT_EQUAL(3,is.size());
  ASSERT_EQUAL(3,*is.begin());
}
void checkCTADFromIterators(){
  std::string s{"santaclaus"};
  auto is=indexableSet(s.cbegin(),s.cend());
  ASSERT_EQUAL("aclnstu",std::string(is.begin(),is.end()));
}
void checkCTADFromIteratorsGreater(){
  std::string s{"santaclaus"};
  auto is=indexableSet(s.cbegin(),s.cend(),std::greater{});
  ASSERT_EQUAL("utsnlca",std::string(is.begin(),is.end()));
}

void insertAndEraseElements(){
  auto is=makeIndexableSet({4,2,3,1});
  ASSERT_EQUAL(4,is.size());
  is.insert(5);
  ASSERT_EQUAL(5,is.size());
  is.insert(5);
  ASSERT_EQUAL(5,is.size());
  is.erase(1);
  ASSERT_EQUAL(4,is.size());
}
void findAndCount(){
  auto is=makeIndexableSet({4,2,3,1});
  ASSERT_EQUAL(is.end(),is.find(42));
  ASSERT_EQUAL(is.begin(),is.find(1));
  ASSERT_EQUAL(0,is.count(42));
  ASSERT_EQUAL(1,is.count(2));
}

void bounds_functions(){
  auto is=makeIndexableSet({4,2,3,1});
  auto p=is.equal_range(3);
  ASSERT_EQUAL(p.first,is.lower_bound(3));
  ASSERT_EQUAL(p.second,is.upper_bound(3));
  ASSERT_EQUAL(3,*p.first);
  ASSERT_EQUAL(4,*p.second);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(constructIndexableSet));
	s.push_back(CUTE(insertIntoIndexableSetAndIndexIt));
	s.push_back(CUTE(constructIndexableSetFromInitializerList));
	s.push_back(CUTE(constructIndexableSetFromRange));
	s.push_back(CUTE(IndexableSetIterators));
	s.push_back(CUTE(ReverseIteratorsIndexableSet));
	s.push_back(CUTE(checkFactorySimple));
	s.push_back(CUTE(checkFactoryGreaterSort));
	s.push_back(CUTE(checkFactoryFromIterators));
	s.push_back(CUTE(insertAndEraseElements));
	s.push_back(CUTE(findAndCount));
	s.push_back(CUTE(bounds_functions));
	s.push_back(CUTE(checkCTADSimple));
	s.push_back(CUTE(checkCTADGreaterSort));
	s.push_back(CUTE(checkCTADFromIterators));
	s.push_back(CUTE(checkCTADFromIteratorsGreater));
	s.push_back(CUTE(checkFactoryFromIteratorsGreater));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
