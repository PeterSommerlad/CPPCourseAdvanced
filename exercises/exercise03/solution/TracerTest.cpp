#include "Tracer.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testCtor(){
  std::ostringstream out{};
  Tracer t{"t",out};
  ASSERT_EQUAL(
R"(Tracer created: t
)"
      ,out.str());
// destruction after test
}

void testDtor(){
  std::ostringstream out{};
  {
    Tracer t{"t",out};
  }
  ASSERT_EQUAL(
R"(Tracer created: t
Tracer destroyed: t
)"
      ,out.str());
}

void testAssignment() {
  std::ostringstream out{};
  {
    Tracer first{"1", out};
    Tracer second{"2",out};
    first = second;
  }
  ASSERT_EQUAL(
R"(Tracer created: 1
Tracer created: 2
Tracer copy=: 1
Tracer now : 2 copy= 
Tracer destroyed: 2
Tracer destroyed: 2 copy= 
)"
      ,out.str());
}
void testMoveAssignment() {
  std::ostringstream out{};
  {
    Tracer first{"1", out};
    Tracer second{"2",out};
    first = std::move(second);
    second.show();
    first.show();
  }
  ASSERT_EQUAL(
R"(Tracer created: 1
Tracer created: 2
Tracer move=: 1
Tracer now : 2 moved= was 1
Tracer: 2 moved from
Tracer: 2 moved= was 1
Tracer destroyed: 2 moved from
Tracer destroyed: 2 moved= was 1
)"
      ,out.str());
}

Tracer withNRVO(std::ostream &out){
  Tracer t{"nrvo",out};
  t.show();
  return t;
}

Tracer withoutNRVO(std::ostream &out){
  Tracer t{"no-nrvo",out};
  t.show();
  return {t}; // (t) does not seem to trigger copy
}
Tracer returnFromTemp(std::ostream &out){
  return Tracer{"tmp",out};
}
void testWithNRVO(){
	std::ostringstream out{};
	{
	  auto t = withNRVO(out);
	}
	ASSERT_EQUAL(
R"(Tracer created: nrvo
Tracer: nrvo
Tracer destroyed: nrvo
)",
	    out.str());
}

void testWithoutNRVO(){
  std::ostringstream out{};
  {
    auto t = withoutNRVO(out);
    t.show();
  }
  ASSERT_EQUAL(
R"(Tracer created: no-nrvo
Tracer: no-nrvo
Tracer copied: no-nrvo copy
Tracer destroyed: no-nrvo
Tracer: no-nrvo copy
Tracer destroyed: no-nrvo copy
)",
      out.str());
}

void testReturnFromTmp(){
  std::ostringstream out{};
  {
    auto t = returnFromTemp(out);
    t.show();
  }
  ASSERT_EQUAL(
R"(Tracer created: tmp
Tracer: tmp
Tracer destroyed: tmp
)",
      out.str());
}



void testCopyConstruction(){
  std::ostringstream out{};
  {
    Tracer t1{"1",out};
    Tracer tcopy{t1};
    t1.show();
    tcopy.show();
  }
  ASSERT_EQUAL(
R"(Tracer created: 1
Tracer copied: 1 copy
Tracer: 1
Tracer: 1 copy
Tracer destroyed: 1 copy
Tracer destroyed: 1
)",
      out.str());
}

void testMoveConstruction(){
  std::ostringstream out{};
  {
    Tracer t1{"1",out};
    Tracer tmove{std::move(t1)};
    t1.show();
    tmove.show();
  }
  ASSERT_EQUAL(
R"(Tracer created: 1
Tracer moved: 1
Tracer: 1 moved from
Tracer: 1
Tracer destroyed: 1
Tracer destroyed: 1 moved from
)",
      out.str());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testCtor));
	s.push_back(CUTE(testDtor));
	s.push_back(CUTE(testCopyConstruction));
	s.push_back(CUTE(testMoveConstruction));
	s.push_back(CUTE(testWithNRVO));
	s.push_back(CUTE(testWithoutNRVO));
	s.push_back(CUTE(testReturnFromTmp));
	s.push_back(CUTE(testAssignment));
	s.push_back(CUTE(testMoveAssignment));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
