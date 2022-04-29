#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

template<typename T>
constexpr bool isPointer { false };
template<typename T>
constexpr bool isPointer<T*> { true };
template<>
constexpr bool isPointer<void*> { false };

static_assert(not isPointer<int>);
static_assert(isPointer<int*>);
static_assert(isPointer<int const *>);
static_assert(not isPointer<void*>);
static_assert(isPointer<void const *>); // oops specialization must match exactly

#include <concepts>
namespace cpp20traits {
template<typename T>
constexpr bool
isDereferencable {
  requires(T t){  *t; }
};
template<>
constexpr bool
isDereferencable<void *> { false };
template<>
constexpr bool
isDereferencable<void const *> { false };

static_assert(not isDereferencable<int>);
static_assert(    isDereferencable<int *>);
static_assert(    isDereferencable<int (*)()>); // function pointer
static_assert(not isDereferencable<void *>);
static_assert(not isDereferencable<void const*>);
}
namespace cpp20bettertraits {
template<typename T>
concept IsObject =
    std::is_object_v<std::remove_reference_t<T>>;

static_assert(IsObject<int>);
static_assert(not IsObject<void>);
static_assert(not IsObject<int(&)()>);


template<typename T>
constexpr bool
isDereferencable {
  requires(T t){
    { *t } -> IsObject;
  }
};
static_assert(not isDereferencable<int>);
static_assert( isDereferencable<int *>);
static_assert(not isDereferencable<int (*)()>); // function pointer not OK
static_assert(not isDereferencable<void *>);
static_assert(not isDereferencable<void const*>);
static_assert(not isDereferencable<void volatile*>);
}


void testAssignment() {
  ASSERTM("start writing tests", true);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testAssignment));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
