#include "Sack.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

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



void testmakeSackInt(){
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






void runAllTests(int argc, char const *argv[]){
  cute::suite s;
  //TODO add your test here
  s.push_back(CUTE(testInstantiationPossibilities));
  s.push_back(CUTE(testmakeSackInt));
  s.push_back(CUTE(testmakeSackCharPtr));
  s.push_back(CUTE(testSackWithPointersShouldntCompile));
  cute::xml_file_opener xmlfile(argc,argv);
  cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
  cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



