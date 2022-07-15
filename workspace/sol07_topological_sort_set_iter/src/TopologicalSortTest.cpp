#include "ModuleNode.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>
#include <fstream>
#include <chrono>

void testNewModuleIsReady(){
  ModuleNode m{"Math"};
  ASSERT(m.isReady(1));
  ASSERT_EQUAL(m,m);
  ASSERT_LESS(m,ModuleNode{"OO"});
}


void testAddRequiredModule(){
  ModuleNode::AllModules theModules{};
  auto math { theModules.insert("Math") };
  auto ad1  { theModules.insert("AD1") };
  ad1->addRequired("Math", theModules);
  ASSERT(not ad1->isReady(1u));
  ASSERT(math->isReady(1u));
  ASSERT(math->schedule(1u));
  ASSERT(ad1->isReady(2u));
}

std::string const input {
R"(
DB1 OO
DB2 DB1
Math
OO
AD1 OO
CPI OO Math
Thesis DB2 SE2 UI2
SE1 AD1 CPI DB1
SE2 DB1 SE1 UI1
UI1 AD1
UI2 UI1
)"
};


void testinput(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  ASSERT_EQUAL(11,theModules.all.size());
}


void testScheduleAll(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  auto result = theModules.scheduleAll();
  ASSERT_EQUAL(5u,result.size());
}

void testCyclicDependencyThrows(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  auto math = theModules.find("Math");
  math->addRequired("Thesis", theModules);
  ASSERT_THROWS(theModules.scheduleAll(),cyclic_dependency);
}



void testOutputOfSchedule(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  std::ostringstream out{};
  theModules.printSchedule(out);
  ASSERT_EQUAL(
      R"(1 : Math, OO, 
2 : AD1, CPI, DB1, 
3 : DB2, SE1, UI1, 
4 : SE2, UI2, 
5 : Thesis, 
)"
      , out.str());

}

void testPrintFromInput(){
  std::istringstream is{input};
  std::ostringstream out{};
  print_semester_topological(is, out);

  ASSERT_EQUAL(
      R"(1 : Math, OO, 
2 : AD1, CPI, DB1, 
3 : DB2, SE1, UI1, 
4 : SE2, UI2, 
5 : Thesis, 
)"
      , out.str());

}


void testTimingWithLargeCataolgue(){
  using namespace std::literals::chrono_literals;
  std::ostringstream out{};
  auto start=std::chrono::system_clock::now();
  // do your stuff
  std::ifstream input{"LargeCatalogue.txt"};
  print_semester_topological(input,out);
  std::chrono::duration<double> delta=std::chrono::system_clock::now()-start;
  ASSERT_LESS(delta,  500ms);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testNewModuleIsReady));
	s.push_back(CUTE(testAddRequiredModule));
	s.push_back(CUTE(testinput));
	s.push_back(CUTE(testScheduleAll));
	s.push_back(CUTE(testOutputOfSchedule));
//	s.push_back(CUTE(testCyclicDependencyThrows));
	s.push_back(CUTE(testPrintFromInput));
	s.push_back(CUTE(testTimingWithLargeCataolgue));
	s.push_back(CUTE(testCyclicDependencyThrows));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
