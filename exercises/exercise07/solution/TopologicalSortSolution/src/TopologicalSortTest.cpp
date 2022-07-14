#include "ModuleNode.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>

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
  ASSERT(is_sorted(begin(theModules.all),end(theModules.all), [](auto const &l, auto const &r){ return l->name < r->name;}));
}

void testPartitionLevel1(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  auto it = theModules.schedule(1u);
  ASSERT_EQUAL(2,distance(begin(theModules.all),it));
  ASSERT(all_of(begin(theModules.all),it,[](auto mp){ return mp && mp->semester==1u;}));
  std::vector<std::string> firstSemester{"Math", "OO"};
  ASSERT(equal(begin(theModules.all),it,begin(firstSemester),end(firstSemester), [](auto const & l, auto const& r){ return l == r;}));
}

void testPartitionLevel2(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  auto it1 = theModules.schedule(1u);
  auto it2 = theModules.schedule(2u);
  ASSERT_EQUAL(3,distance(it1,it2));
  ASSERT(all_of(it1,it2,[](auto mp){ return mp && mp->semester==2u;}));
  std::vector<std::string> secondSemester{"AD1", "CPI", "DB1"};
  ASSERT(equal(it1,it2,begin(secondSemester),end(secondSemester), [](auto l, std::string r){ return l->name == r;}));
}

void testPartitionLevel3(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  std::ignore = theModules.schedule(1u);
  auto it2 = theModules.schedule(2u);
  auto it3 = theModules.schedule(3u);
  ASSERT_EQUAL(3,distance(it2,it3));
  ASSERT(all_of(it2,it3,[](auto mp){ return mp && mp->semester==3u;}));
  std::vector<std::string> secondSemester{"DB2", "SE1", "UI1"};
  ASSERT(equal(it2,it3,begin(secondSemester),end(secondSemester), [](auto l, std::string r){ return l->name == r;}));
}
void testPartitionLevel4(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  std::ignore = theModules.schedule(1u);
  std::ignore = theModules.schedule(2u);
  auto it3 = theModules.schedule(3u);
  auto it4 = theModules.schedule(4u);
  ASSERT_EQUAL(2,distance(it3,it4));
  ASSERT(all_of(it3,it4,[](auto mp){ return mp && mp->semester==4u;}));
  std::vector<std::string> secondSemester{"SE2",  "UI2"};
  ASSERT(equal(it3,it4,begin(secondSemester),end(secondSemester), [](auto l, std::string r){ return l->name == r;}));
}

void testPartitionLevel5(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  std::ignore = theModules.schedule(1u);
  std::ignore = theModules.schedule(2u);
  std::ignore = theModules.schedule(3u);
  std::ignore = theModules.schedule(4u);
  auto it5 = theModules.schedule(5u);
  ASSERT_EQUAL(end(theModules.all),it5);
}
void testScheduleAll(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  theModules.scheduleAll();
  ASSERT_EQUAL(5u,theModules.all.back()->semester);
}

void testCyclicDependencyThrows(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  auto math = theModules.find("Math");
  (*math)->addRequired("Thesis", theModules);
  ASSERT_THROWS(theModules.scheduleAll(),cyclic_dependency);
}



void testOutputOfSchedule(){
  std::istringstream is{input};
  ModuleNode::AllModules theModules{is};
  theModules.scheduleAll();
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




bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testNewModuleIsReady));
	s.push_back(CUTE(testAddRequiredModule));
	s.push_back(CUTE(testinput));
	s.push_back(CUTE(testPartitionLevel1));
	s.push_back(CUTE(testPartitionLevel2));
	s.push_back(CUTE(testPartitionLevel3));
	s.push_back(CUTE(testPartitionLevel4));
	s.push_back(CUTE(testPartitionLevel5));
	s.push_back(CUTE(testScheduleAll));
	s.push_back(CUTE(testOutputOfSchedule));
	s.push_back(CUTE(testCyclicDependencyThrows));
	s.push_back(CUTE(testPrintFromInput));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
