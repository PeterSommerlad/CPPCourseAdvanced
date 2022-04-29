#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <optional>
#include <variant>

int div1(int divident, int divisor, int errorreturn = std::numeric_limits<int>::max()){
  if (divisor == 0) return errorreturn;
  return divident/divisor;
}
int div2(int divident, int divisor){
  if (divisor == 0) return std::numeric_limits<int>::max();
  return divident/divisor;
}
std::optional<int> div2a(int divident, int divisor){
  if (divisor == 0) return {};
  return divident/divisor;
}
enum class error_code { div_ok, div_by_zero };
using expected=std::variant<int,error_code>;

expected div2b(int divident, int divisor){
  if (divisor == 0) return error_code::div_by_zero;
  return divident/divisor;
}
int div3(int divident, int divisor, error_code &error){
  if (divisor == 0) {
    error= error_code::div_by_zero;
    return 0;
  }
  return divident/divisor;
}
struct div_by_zero{};
int div4(int divident, int divisor){
  if (divisor == 0) throw div_by_zero{} ;
  return divident/divisor;
}


void testDiv1IsOk(){
	  ASSERT_EQUAL(3, div1(10,3));
}

void testForDiv1WithDefaultErrorResult(){
  auto result = div1(10,0);
  ASSERT_EQUAL(std::numeric_limits<int>::max(),result);
}
void testForDiv1WithSpecialErrorResult(){
  auto result = div1(10,0,-1);
  ASSERT_EQUAL(-1,result);
}
void testDiv2IsOk(){
    ASSERT_EQUAL(3, div2(20,6));
}
void testForDiv2WithDefaultErrorResult(){
  auto result = div2(10,0);
  ASSERT_EQUAL(std::numeric_limits<int>::max(),result);
}

void testDiv2aIsOk(){
    ASSERT_EQUAL(3, div2a(20,6).value());
}
void testForDiv2aToReturnEmptyOptional(){
  auto result = div2a(10,0);
  ASSERT(not result.has_value());
}
void testDiv2aValueThrowsIfInvalid(){
  ASSERT_THROWS(div2a(20,0).value(), std::bad_optional_access);
}


void testDiv2bIsOk(){
    ASSERT_EQUAL(3, std::get<int>(div2b(20,6)));
}
void testForDiv2bForErrorCodeReturn(){
  auto result = div2b(10,0);
  ASSERT_EQUAL(1,result.index());
}
void testDiv2bValueThrowsIfErrorCode(){
  ASSERT_THROWS(std::get<int>(div2b(20,0)), std::bad_variant_access);
}

void testDiv3IsOk(){
  error_code error{};
    ASSERT_EQUAL(2, div3(16,6, error));
    ASSERT_EQUAL(error_code::div_ok,error);
}
void testForDiv3WithDefaultErrorResult(){
  error_code error{};
  std::ignore = div3(10,0,error);
  ASSERT_EQUAL(error_code::div_by_zero,error);
}

void testDiv4IsOk(){
    ASSERT_EQUAL(4, div4(16,4));
}
void testForDiv4WithDefaultErrorResult(){
  ASSERT_THROWS(div4(10,0),div_by_zero);
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testForDiv1WithDefaultErrorResult));
	s.push_back(CUTE(testDiv1IsOk));
	s.push_back(CUTE(testForDiv1WithSpecialErrorResult));
	s.push_back(CUTE(testDiv2IsOk));
	s.push_back(CUTE(testForDiv2WithDefaultErrorResult));
	s.push_back(CUTE(testDiv2aIsOk));
	s.push_back(CUTE(testForDiv2aToReturnEmptyOptional));
	s.push_back(CUTE(testDiv2aValueThrowsIfInvalid));
	s.push_back(CUTE(testDiv2bIsOk));
	s.push_back(CUTE(testForDiv2bForErrorCodeReturn));
	s.push_back(CUTE(testDiv2bValueThrowsIfErrorCode));
	s.push_back(CUTE(testDiv3IsOk));
	s.push_back(CUTE(testForDiv3WithDefaultErrorResult));
	s.push_back(CUTE(testDiv4IsOk));
	s.push_back(CUTE(testForDiv4WithDefaultErrorResult));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
