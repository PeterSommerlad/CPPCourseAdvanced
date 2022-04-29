#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <string>
#include <cstdlib>
#include <memory>
#include <cxxabi.h> // __cxa_demangle


std::string demangle(std::string name){
  if (name.size() > 0 ){
    constexpr auto freemem{ [](char *toBeFreed){
	  std::free(toBeFreed);
    }};
    std::unique_ptr<char ,decltype(freemem)> freeit {
    	abi::__cxa_demangle(name.c_str(),0,0,0),
    	freemem };
	std::string result{freeit.get()};
	return result;
  } else {
	return "unknown";
  }
}
void how_cute_demangle_should_be_test() {
	ASSERT_EQUAL("i",typeid(int).name());
	ASSERT_EQUAL("int", demangle(typeid(int).name()));
}
struct free_deleter {
  template<typename T>
  void operator()(T * p) const {
    std::free(const_cast<std::remove_const_t<T> *>(p));
  }
};
template<typename T>
using unique_C_ptr = std::unique_ptr<T, free_deleter>;
std::string plain_demangle(char const * name) {
  unique_C_ptr<char const> toBeFreed{__cxxabiv1::__cxa_demangle(name, 0, 0, 0)};
  std::string result(toBeFreed.get());
  return result;
}

void test_plain_demangle(){
	ASSERT_EQUAL("unsigned long", plain_demangle(typeid(size_t).name()));
}

#include <cstdio>

struct FILE_ptr_closer {
  void operator()(FILE * p) const {
    if (p) std::fclose(p);
  }
};


using unique_FILE_ptr = std::unique_ptr<FILE,FILE_ptr_closer>;

auto openFile(std::string const& name, std::string mode="r"){
	return unique_FILE_ptr{fopen(name.c_str(),mode.c_str())};
}

constexpr auto filename{"test.txt"};

void create_file_for_test(){
	std::ofstream file{filename};
	file.put('A');
}

void testFilePtrCloser(){
	create_file_for_test();
	auto legacy_file{openFile(filename)};
	if (legacy_file){
		auto ch {std::fgetc(legacy_file.get())};
		ASSERT_EQUAL('A',ch);
	} else {
		FAILM("could not read or create test.txt" );
	}
}




bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(how_cute_demangle_should_be_test));
	s.push_back(CUTE(test_plain_demangle));
	s.push_back(CUTE(testFilePtrCloser));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
