#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>

auto printLnSeparated = [](std::ostream &out,auto const &... args){
  bool first{true};
  (out << ... <<
      (out << (first?(first=false), "" : ", ")
       , args)
   ) << "\n";
};

void testAssignment() {
  std::ostringstream out{};
  printLnSeparated(out, 1,"3.14",'a', "Peter");
  ASSERT_EQUAL("1, 3.14, a, Peter\n",out.str());
}
void testWitJustNewline(){
  std::ostringstream out{};
  printLnSeparated(out);
  ASSERT_EQUAL("\n",out.str());
}
void testSingleElementNoComma(){
  std::ostringstream out{};
  printLnSeparated(out, 1);
  ASSERT_EQUAL("1\n",out.str());
}

void testTwoElementsSeparatedByComma(){
  std::ostringstream out{};
  printLnSeparated(out, 1, "two");
  ASSERT_EQUAL("1, two\n",out.str());
}




bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testAssignment));
	s.push_back(CUTE(testWitJustNewline));
	s.push_back(CUTE(testSingleElementNoComma));
	s.push_back(CUTE(testTwoElementsSeparatedByComma));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
