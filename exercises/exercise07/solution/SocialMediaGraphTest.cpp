#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <algorithm>

#include <iterator>

#include <memory>
#include <sstream>
#include <string>

using PersonPtr = std::shared_ptr<struct Person>;
using WeakPersonPtr = std::weak_ptr<struct Person>;
using Persons = std::vector<WeakPersonPtr>;
struct Person : std::enable_shared_from_this<Person> {
  Person(std::string name):name{name}{};
  std::string name{};
  Persons follows{};
  Persons followers{};
  static std::ostream & 
  printPersons(std::ostream & out, std::string description, Persons const &list){
    out << description;
    for( auto const &wp : list){
      auto pp = wp.lock();
      if (pp)
        out << pp->name << ", ";
    }
    return out;
  }
  friend std::ostream & operator<<(std::ostream &out, Person const & p){
    out << p.name <<  "\n  ";
    printPersons(out," follows    : ", p.follows) << "\n  ";
    printPersons(out," followedBy : ", p.followers) << "\n\n";
    return out;
  }
  void follow(PersonPtr other){
    if (other){
      follows.push_back(other);
      other->followers.push_back(this->shared_from_this());
    }
  }
  template<typename ...Pptr>
  void follow(PersonPtr first, Pptr...pp){
    follow(first);
    if constexpr(sizeof...(pp)) follow(pp...);
  }
  void unfollow(PersonPtr other){
    if (other){
      follows.erase(find_if(begin(follows),end(follows),[other](auto pp){
        return pp.lock() == other;
       }));
      other->followers.erase(find_if(begin(other->followers),end(other->followers),
          [this](auto pp) {
        return pp.lock() == this->shared_from_this();
      }));
    }
  }
  void block(PersonPtr other){
    if (other){
      other->unfollow(this->shared_from_this());
      this->unfollow(other);
    }
  }
};

struct Registry {
  std::vector<PersonPtr> allPersons{};
void printPersons(std::ostream & out) const {
    for (auto pp: allPersons){
      if (pp){
        out << *pp  ;
      }
      else {
        out << "(nullptr) person found\n";
      }
    }
  }
  PersonPtr findOrRegister(std::string name){
    auto it = find_if(begin(allPersons),end(allPersons),[name](auto pp){
        if (pp){
          return pp->name == name;
        } else { 
          return false; // may be throw
        }
    });
    if (it != end(allPersons)){
      return *it;
    } else {
      allPersons.push_back(std::make_shared<Person>(name));
      return allPersons.back();
    }
  }
  void ban(std::string name){
    auto toban = findOrRegister(name);
    for(auto follower: toban->followers){
      if (! follower.expired()) follower.lock()->unfollow(toban);
    }
    for (auto followed: toban->follows){
      toban->unfollow(followed.lock());
    }
    allPersons.erase(find(begin(allPersons),end(allPersons),toban));
  }
};
std::ostream & operator<<(std::ostream & out, PersonPtr const &pp){
  if (pp){
    out << *pp;
  } else {
    out << "nullptr\n";
  }
  return out;
}


void thisIsATest() {
  auto const ppeter = std::make_shared<Person>("Peter");
  std::ostringstream out{};
  out << *ppeter;
  ASSERT_EQUAL(
R"(Peter
   follows    : 
   followedBy : 

)",out.str());
}

void registerSinglePerson(){
  std::ostringstream out{};
	Registry r{};
	r.findOrRegister("Peter");
	r.printPersons(out);
	ASSERT_EQUAL(
R"(Peter
   follows    : 
   followedBy : 

)",out.str());
}

void registerTwoPersons(){
  std::ostringstream out{};
  Registry r{};
  r.findOrRegister("Peter");
  r.findOrRegister("Andrea");
  r.printPersons(out);
  ASSERT_EQUAL(
R"(Peter
   follows    : 
   followedBy : 

Andrea
   follows    : 
   followedBy : 

)",out.str());
}

auto createFollowship(){
  Registry r{};
  auto peter = r.findOrRegister("Peter");
  auto fred = r.findOrRegister("Fred");
  auto steve = r.findOrRegister("Steve");
  auto amy = r.findOrRegister("Amy");
  auto tom = r.findOrRegister("Tom");
  auto bibi = r.findOrRegister("Bibi");
  peter->follow(fred,steve,bibi);
  fred->follow(peter,steve,amy);
  steve->follow(peter,fred);
  amy->follow(bibi);
  tom->follow(bibi);
  return r;
}
void checkFollowship(){
  auto r = createFollowship();
  std::ostringstream out{};
  r.printPersons(out);
  ASSERT_EQUAL(
R"(Peter
   follows    : Fred, Steve, Bibi, 
   followedBy : Fred, Steve, 

Fred
   follows    : Peter, Steve, Amy, 
   followedBy : Peter, Steve, 

Steve
   follows    : Peter, Fred, 
   followedBy : Peter, Fred, 

Amy
   follows    : Bibi, 
   followedBy : Fred, 

Tom
   follows    : Bibi, 
   followedBy : 

Bibi
   follows    : 
   followedBy : Peter, Amy, Tom, 

)",out.str());


}

void steveBlocksFred(){
  auto r = createFollowship();
  std::ostringstream out{};
  auto steve = r.findOrRegister("Steve");
  auto fred = r.findOrRegister("Fred");
  steve->block(fred);
  r.printPersons(out);
  ASSERT_EQUAL(
R"(Peter
   follows    : Fred, Steve, Bibi, 
   followedBy : Fred, Steve, 

Fred
   follows    : Peter, Amy, 
   followedBy : Peter, 

Steve
   follows    : Peter, 
   followedBy : Peter, 

Amy
   follows    : Bibi, 
   followedBy : Fred, 

Tom
   follows    : Bibi, 
   followedBy : 

Bibi
   follows    : 
   followedBy : Peter, Amy, Tom, 

)",out.str());

}

void PeterUnfollowsFred(){
  auto r = createFollowship();
  std::ostringstream out{};
  auto steve = r.findOrRegister("Steve");
  auto fred = r.findOrRegister("Fred");
  steve->block(fred);
  auto peter = r.findOrRegister("Peter");
  peter->unfollow(fred);
  r.printPersons(out);
  ASSERT_EQUAL(
R"(Peter
   follows    : Steve, Bibi, 
   followedBy : Fred, Steve, 

Fred
   follows    : Peter, Amy, 
   followedBy : 

Steve
   follows    : Peter, 
   followedBy : Peter, 

Amy
   follows    : Bibi, 
   followedBy : Fred, 

Tom
   follows    : Bibi, 
   followedBy : 

Bibi
   follows    : 
   followedBy : Peter, Amy, Tom, 

)",out.str());

}

void testBanningBibi(){

  auto r = createFollowship();
  std::ostringstream out{};
  auto steve = r.findOrRegister("Steve");
  auto fred = r.findOrRegister("Fred");
  steve->block(fred);
  auto peter = r.findOrRegister("Peter");
  peter->unfollow(fred);
  r.ban("Bibi");
  r.printPersons(out);
  ASSERT_EQUAL(
R"(Peter
   follows    : Steve, 
   followedBy : Fred, Steve, 

Fred
   follows    : Peter, Amy, 
   followedBy : 

Steve
   follows    : Peter, 
   followedBy : Peter, 

Amy
   follows    : 
   followedBy : Fred, 

Tom
   follows    : 
   followedBy : 

)",out.str());
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(registerSinglePerson));
	s.push_back(CUTE(registerTwoPersons));
	s.push_back(CUTE(checkFollowship));
	s.push_back(CUTE(steveBlocksFred));
	s.push_back(CUTE(PeterUnfollowsFred));
	s.push_back(CUTE(testBanningBibi));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
