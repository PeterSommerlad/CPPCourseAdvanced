#include "SackSpecializations.h"
#include "Sack.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"











// template must start on line 20
namespace SimpleSack {
template <typename T>
class Sack
{
  using SackType=std::vector<T>;
  SackType theSack{};
  using size_type=typename SackType::size_type;
  inline static std::mt19937 randengine{};
  using rand=std::uniform_int_distribution<size_type>;
public:
  bool empty() const { return theSack.empty() ; }
  size_type size() const { return theSack.size();}
  void putInto(T item) & { theSack.push_back(std::move(item));}
  template <typename Elt = T>
  auto asVector() const {
    return std::vector<Elt>(theSack.begin(),theSack.end());
              // () to avoid initializer_list ctor
  }

//...
  T getOut() & {
    using difference_type=typename SackType::difference_type;
      if (empty()) throw std::logic_error{"empty Sack"};
      size_t const index = rand{0u,size() - 1}(randengine);
      T retval{theSack.at(index)};
      theSack.erase(std::next(theSack.begin(),
          static_cast<difference_type>(index)));
      return retval;
  }
};

template <typename T>
struct Sack<T*>; // declare but don't define prohibits use



//-----
template <>
struct Sack<char const *> : Sack<std::string>{
  using Sack<std::string>::Sack;
};
template <typename T>
Sack<T> makeSack(std::initializer_list<T> list){
  Sack<T> sack{};
  for (auto const elt : list){
    sack.putInto(elt);
  }
  return sack;
}

void testmakeSackInt(){
  auto sack{makeSack({1,2,3,4,5,6})};
  ASSERT_EQUAL(6,sack.size());
}


void testmakeSackCharPtr(){
  auto sack{makeSack({"Hello",",","World","!"})};
  ASSERT_EQUAL(4,sack.size());
  std::set<std::string> content{};
  std::set<std::string> expected{"Hello",",","World","!"};
  while(!sack.empty()){
    content.insert(sack.getOut());
  }
  ASSERT_EQUAL(expected,content);
  ASSERT_THROWS(sack.getOut(),std::logic_error);
}

}
void testmakeSackInt(){ // must be line 88!
#if __cplusplus < 201703L
  auto sack{makeSack({1,2,3,4,5,6})};
#else
  Sack sack{1,2,3,4,5,6};
#endif
  ASSERT_EQUAL(6,sack.size());
}
void testmakeSackCharPtr(){
#if __cplusplus < 201703L
  auto sack{makeSack({"Hello",",","World","!"})};
#else
  Sack sack{"Hello",",","World","!"};
#endif
  ASSERT_EQUAL(4,sack.size());
  std::set<std::string> content{};
  std::set<std::string> expected{"Hello",",","World","!"};
  while(!sack.empty()){
    content.insert(sack.getOut());
  }
  ASSERT_EQUAL(expected,content);
  ASSERT_THROWS(sack.getOut(),std::logic_error);
}



namespace SackSpecialSpecialization {
template <typename T>
class Sack
{
  using SackType=std::vector<T>;
  SackType theSack{};
  using size_type=typename SackType::size_type;
  inline static std::mt19937 randengine{};
  using rand=std::uniform_int_distribution<size_type>;
public:
  bool empty() const { return theSack.empty() ; }
  size_type size() const { return theSack.size();}
  void putInto(T const &item) { theSack.push_back(item);}
  template <typename Elt = T>
  explicit operator std::vector<Elt>() const {
    return std::vector<Elt>(theSack.begin(),theSack.end());
              // () to avoid initializer_list ctor
  }

//...
  T getOut() & {
    using difference_type=typename SackType::difference_type;
      if (empty()) throw std::logic_error{"empty Sack"};
      size_t const index = rand{0u,size() - 1}(randengine);
      T retval{theSack.at(index)};
      theSack.erase(std::next(theSack.begin(),
          static_cast<difference_type>(index)));
      return retval;
  }
};

template <>
struct Sack<char const *> {
  using SackType = std::vector<std::string>;
  using size_type = SackType::size_type;
  SackType theSack;
public:
  bool empty() const {
    return theSack.empty();
  }
  size_type size() const {
    return theSack.size();
  }
  void putInto(char const *item) { theSack.push_back(item);}
  std::string getOut() {
    if (empty()) throw std::logic_error{"empty Sack"};
    std::string result=theSack.back();
    theSack.pop_back();
    return result;
  }
};

template <typename T>
Sack<T> makeSack(std::initializer_list<T> list){
  Sack<T> sack{};
  for (auto const elt : list){
    sack.putInto(elt);
  }
  return sack;
}


void testmakeSackCharPtr(){
  auto sack{makeSack({"Hello",",","World","!"})};
  static_assert(std::is_same_v<std::vector<std::string>,decltype(sack)::SackType>);
  static_assert(std::is_same_v<Sack<char const *>,decltype(sack)>);
  ASSERT_EQUAL(4,sack.size());
  std::set<std::string> content{};
  std::set<std::string> expected{"Hello",",","World","!"};
  while(!sack.empty()){
    content.insert(sack.getOut());
  }
  ASSERT_EQUAL(expected,content);
  ASSERT_THROWS(sack.getOut(),std::logic_error);
}

}

void testInstantiationPossibilities() {
  Sack<char> scrabble{};
  //Sack<int*> shouldntcompile{};
  Sack<char const *> sackforstringliterals{};
  ASSERTM("only compilation tested",true);
}

void testSackWithPointersShouldntCompile(){
  //Sack<int *> shouldNotCompile;
  Sack<char const *> shouldkeepStrings;
}
void testSackFromIter(){
  std::vector v{1,3,4,5};
  Sack s(std::begin(v),std::end(v));
  ASSERT_EQUAL(std::size(v),s.size());
}
void testSackWith2ValuesThatAreNotIterators(){
   Sack<int> s(10,2);
   ASSERT_EQUAL(10,s.size());
}
void testSackWithSizeAndValueDeduces(){
  Sack s(5u,std::string("Hello"));
  ASSERT_EQUAL(5,s.size());
  ASSERT_EQUAL("Hello", s.getOut());
}

void runAllTests(int argc, char const *argv[]){
  cute::suite s;
  //TODO add your test here
  s.push_back(CUTE(testInstantiationPossibilities));
  s.push_back(CUTE(testmakeSackInt));
  s.push_back(CUTE(testmakeSackCharPtr));
  s.push_back(CUTE(testSackWithPointersShouldntCompile));
  s.push_back(CUTE(SimpleSack::testmakeSackInt));
  s.push_back(CUTE(SimpleSack::testmakeSackCharPtr));
  s.push_back(CUTE(SackSpecialSpecialization::testmakeSackCharPtr));
  s.push_back(CUTE(testSackFromIter));
  s.push_back(CUTE(testSackWith2ValuesThatAreNotIterators));
  s.push_back(CUTE(testSackWithSizeAndValueDeduces));
  cute::xml_file_opener xmlfile(argc,argv);
  cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
  cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



