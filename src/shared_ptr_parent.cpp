#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <memory>
#include <string>
#include <vector>

namespace simple {
struct Person {
  std::shared_ptr<Person> child{};
  std::weak_ptr<Person> parent{};
  std::string name{};
  Person(std::string n):name{n}{}
  friend
  std::ostream &operator<<(std::ostream &os, Person const &p){
    return os<<p.name;
  }
  void acquireMoney(std::ostream &out){
    if (auto realparent = parent.lock()){
      out << "borrow from parent " << *realparent << "\n";
    } else {
      out << "go to bank instead\n";
    }
  }
  auto spawn(std::string name){
    child = std::make_shared<Person>(name);
    // how to set myself as parent?
    return child;
  }
};

void createStarWarsRelatives(){
  {
    auto anakin = std::make_shared<Person>("darth vader");
    auto luke = std::make_shared<Person>("luke skywalker");
    anakin->child = luke;
    luke->parent = anakin;

    anakin.reset();
    ASSERT(luke->parent.expired());
    ASSERT_EQUAL(1,luke.use_count());
  } // no leak here!
}

void demoWeakPtrAccess(){
  auto anakin = std::make_shared<Person>("darth vader");
  auto luke = std::make_shared<Person>("luke skywalker");
  anakin->child = luke;
  luke->parent = anakin;
  std::ostringstream os{};
  luke->acquireMoney(os);
  ASSERT_EQUAL("borrow from parent darth vader\n",os.str());
  anakin.reset(); // kill creditor
  os.str(""); // reset tracks
  luke->acquireMoney(os);
  ASSERT_EQUAL("go to bank instead\n",os.str());
}

}

namespace spawn {

struct Person : std::enable_shared_from_this<Person> {
  std::shared_ptr<Person> child{};
  std::weak_ptr<Person> parent{};
  std::string name{};

  friend
  std::ostream &operator<<(std::ostream &os, Person const &p){
    return os<<p.name;
  }
  Person(std::string n):name{n}{}
  auto spawn(std::string name){
    child = std::make_shared<Person>(name);
    child->parent = this->weak_from_this();
    return child;
  }
};
void createStarWarsRelatives(){
  {
    auto anakin = std::make_shared<Person>("darth vader");
    auto luke = anakin->spawn("luke skywalker");
    ASSERT_EQUAL(luke,anakin->child);
    anakin.reset();
    ASSERT(luke->parent.expired());
    ASSERT_EQUAL(1,luke.use_count());
  } // no leak here!
}
void NonHeapObjectHasNullptrWeakFromThis(){
  Person p{"notOnHeap"};
  ASSERT_EQUAL(0,p.weak_from_this().use_count());
  ASSERT(p.weak_from_this().expired());
  ASSERT_THROWS(p.shared_from_this(), std::bad_weak_ptr);
}

}
namespace multiple {
using PersonPtr=std::shared_ptr<struct Person>;
struct Person : std::enable_shared_from_this<Person> {
  std::string name{};
  std::vector<PersonPtr> children{};
  std::weak_ptr<Person> parent{};

  friend
  std::ostream &operator<<(std::ostream &os, Person const &p){
    return os<<p.name;
  }
  Person(std::string n):name{n}{}
  auto spawn(std::string name){
    auto child = std::make_shared<Person>(name);
    child->parent = this->weak_from_this();
    children.push_back(child);
    return child;
  }
  bool isChildOf(PersonPtr person) const {
    auto myparent = parent.lock();
    if (myparent && person){
      if (myparent->name == person->name){
        // candidate:
        auto me = this->shared_from_this();
        return std::any_of(begin(person->children)
               , end(person->children)
               , [me](PersonPtr child){
          return me && child && (child == me);
               });
      }
    }
    return false;
  }
};
void createStarWarsRelatives(){
  {
    auto anakin = std::make_shared<Person>("darth vader");
    auto luke = anakin->spawn("luke skywalker");
    auto leia = anakin->spawn("leia organa");

    anakin.reset();
    ASSERT(leia->parent.expired());
    ASSERT_EQUAL(1,luke.use_count());
  } // no leak here!
}

void testIfChildOfWorks(){
  auto anakin = std::make_shared<Person>("darth vader");
  auto luke = anakin->spawn("luke skywalker");
  auto leia = anakin->spawn("leia organa");
  ASSERT(luke->isChildOf(anakin));
  ASSERT(leia->isChildOf(anakin));
  leia->parent.reset();
  ASSERT(!leia->isChildOf(anakin));
  ASSERT(luke->isChildOf(anakin));
  anakin.reset();
  ASSERT(!leia->isChildOf(anakin));
  ASSERT(!luke->isChildOf(anakin));
}

}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(simple::createStarWarsRelatives));
	s.push_back(CUTE(simple::demoWeakPtrAccess));
	s.push_back(CUTE(spawn::createStarWarsRelatives));
	s.push_back(CUTE(multiple::createStarWarsRelatives));
	s.push_back(CUTE(multiple::testIfChildOfWorks));
	s.push_back(CUTE(spawn::NonHeapObjectHasNullptrWeakFromThis));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
