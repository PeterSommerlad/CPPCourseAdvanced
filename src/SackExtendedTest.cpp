#include "SackExt.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <deque>
#include <set>
#include <list>



void creationWithCurlyBracesFavorsInitializerList() {
  Sack asack { 10, 3 }; // favors initializer_list ctor
  ASSERT_EQUAL(2, asack.size());
}
void creationAllowsTwoDifferentArgumentTypes(){
  Sack<std::string> asack(10u, "hello");
  ASSERT_EQUAL(10, asack.size());
  ASSERT_EQUAL("hello", asack.getOut());
}

void creationFromIteratorsCanDeduceElementType(){
  std::vector<std::string> v(2,"Hello");
  Sack asack(begin(v),end(v));
  ASSERT_EQUAL("Hello",asack.getOut());
}
void creationFromStringLiteralsSelectsWrongSackType(){
  // Sack("A","B") -> Sack<char> because of deduction guide
  static_assert(std::is_same_v<Sack<char>,decltype(Sack("A","B"))>);
}
void deductionFromInitializerList(){
  Sack anIntSack{1,2,3,4,5};
  ASSERT_EQUAL(5,anIntSack.size());
}
void defaultConstructorStillWorks() {
  Sack<char> defaultctorstillworks { };
  ASSERT_EQUAL(0, defaultctorstillworks.size());
}
void constructionFromIteratorPair() {
  std::vector<int> v{3,1,4,1,5,9,2,6};
  Sack<int> asack{v.begin(),v.end()};
  ASSERT_EQUAL(v.size(),asack.size());
}

void constructionFromIteratorPairWithDeduction() {
  std::vector v{3,1,4,1,5,9,2,6};
  Sack asack(v.begin(),v.end());
  ASSERT_EQUAL(v.size(),asack.size());
  static_assert(std::is_same_v<Sack<int>,decltype(asack)>);
}


Sack<int> sackForTest() {
  Sack<int> asack;
  asack.putInto(3);
  asack.putInto(2);
  asack.putInto(1);
  return asack;
}

void extractAVectorFromSack() {
  Sack<int> asack = sackForTest();
  auto v=static_cast<std::vector<unsigned>>(asack);
  ASSERT_EQUAL(asack.size(),v.size());
  while (!asack.empty()){
    auto val=asack.getOut();
    auto it=find(begin(v),end(v),val);
    ASSERT(it != end(v));
    v.erase(it);
  }
  ASSERT(v.empty());
  std::vector<double> vd{asack};
  ASSERT_EQUAL(asack.size(),vd.size());
}
void asVectorTest(){
  Sack<int> asack = sackForTest();
  auto v=asack.asVector();
  auto vd=asack.asVector<double>();
  ASSERT_EQUAL(asack.size(),v.size());
  ASSERT(equal(v.begin(),v.end(),vd.begin()));
}

void createSackFromInitializerList(){
  Sack csack{'a','b','c'};
  ASSERT_EQUAL(3,csack.size());
  static_assert(std::is_same_v<Sack<char>,decltype(csack)>);
}


void makeSackFromInitializerList(){
  auto asack=makeSack({1,2,3,4});
  asack.putInto(5);
  ASSERT_EQUAL(5,asack.size());
}
void makeSackFromHeterogeneousInitializerFails(){
//  auto failstoCompile=makeSack({1,2.0});
}

void makeSackWithLoop(){
  auto asack=makeSack1({'a','b','c'});
  ASSERT_EQUAL(3,asack.size());
}
void makeASackFromAList(){
  Sack<int,std::list> listsack{1,2,3,4,5};
  std::ignore=listsack.getOut();
  listsack.putInto(42);
  ASSERT_EQUAL(5,listsack.size());
}
void makeOtherSackWithContainer(){
  auto othersack=makeOtherSack<std::deque>({1,2,3});
  ASSERT_EQUAL(3,othersack.size());
  auto setsack=makeOtherSack<std::set>({'a','b','c','c'});
  ASSERT_EQUAL(3,setsack.size());
}

template<template<typename ...> class container,typename T>
using SomeSack = Sack<T,container>;

SomeSack<std::list,int> xx{1,2,3,4};
//SomeSack<std::list> xz{1,2,3,4}; // not same as function template argument deduction




void createOtherSack() {
  auto intsack=makeSack({1,2,3});
  ASSERT_EQUAL(3,intsack.size());
  ASSERT((std::is_same<int,decltype(intsack.getOut())>::value));
  Sack<int,std::deque> anothersack{};
  auto othersack=makeOtherSack<std::deque>({1,2,3});
  ASSERT_EQUAL(3,othersack.size());
  auto setsack=makeOtherSack<std::set>({'a','b','c','c'});
  ASSERT_EQUAL(3,setsack.size());
}


void makeSetSackFromInitList(){
  auto setsack { makeSetSack({1,2,3,4})};
  static_assert(std::is_same_v<Sack<int,std::set>,decltype(setsack)>);
  ASSERT_EQUAL(4, setsack.size());
  ASSERT_EQUAL((std::vector{1,2,3,4}),setsack.asVector());
}

void makeSetSackFromIterators(){
  std::vector v{1,2,3,4};
  auto setsack(makeSetSack(begin(v),end(v)));
  static_assert(std::is_same_v<Sack<int,std::set>,decltype(setsack)>);
  ASSERT_EQUAL(4, setsack.size());
  ASSERT_EQUAL((std::vector{1,2,3,4}),setsack.asVector());
}

void SetSackAliasCTAD(){
  SetSack<int> setsack{{1,2,3,4,5}}; // implicit deduction guide OK?
  static_assert(std::is_same_v<Sack<int,std::set>,decltype(setsack)>);
  ASSERT_EQUAL(5, setsack.size());
  ASSERT_EQUAL((std::vector{1,2,3,4,5}),setsack.asVector());
}

void SetSackAliasCTADFromIteratorsDoesNotWork(){
  std::vector v{1,2,3,4};
  SetSack<int> setsack(begin(v),end(v)); // must specify template argument
  static_assert(std::is_same_v<Sack<int,std::set>,decltype(setsack)>);
  ASSERT_EQUAL(4, setsack.size());
  ASSERT_EQUAL((std::vector{1,2,3,4}),setsack.asVector());
}



void runAllTests(int argc, char const *argv[]){
  cute::suite s;
  //TODO add your test here
  s.push_back(CUTE(constructionFromIteratorPair));
  s.push_back(CUTE(defaultConstructorStillWorks));
  s.push_back(CUTE(extractAVectorFromSack));
  s.push_back(CUTE(asVectorTest));
  s.push_back(CUTE(createSackFromInitializerList));
  s.push_back(CUTE(makeSackFromInitializerList));
  s.push_back(CUTE(makeSackFromHeterogeneousInitializerFails));
  s.push_back(CUTE(makeSackWithLoop));
  s.push_back(CUTE(creationWithCurlyBracesFavorsInitializerList));
  s.push_back(CUTE(creationAllowsTwoDifferentArgumentTypes));
  s.push_back(CUTE(makeASackFromAList));
  s.push_back(CUTE(createOtherSack));
  s.push_back(CUTE(creationFromIteratorsCanDeduceElementType));
  s.push_back(CUTE(creationFromStringLiteralsSelectsWrongSackType));
	s.push_back(CUTE(constructionFromIteratorPairWithDeduction));
	s.push_back(CUTE(makeOtherSackWithContainer));
	s.push_back(CUTE(deductionFromInitializerList));
	s.push_back(CUTE(makeSetSackFromInitList));
	s.push_back(CUTE(makeSetSackFromIterators));
	s.push_back(CUTE(SetSackAliasCTAD));
	s.push_back(CUTE(SetSackAliasCTADFromIteratorsDoesNotWork));
  cute::xml_file_opener xmlfile(argc,argv);
  cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
  cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}

