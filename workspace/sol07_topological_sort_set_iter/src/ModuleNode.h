#ifndef MODULENODE_H_
#define MODULENODE_H_


#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <iosfwd>
#include <functional>

// constexpr variable is not implicitly inline
constexpr inline auto ModuleStringLess { [] (auto const &l, auto const &r){
  if constexpr (std::is_same_v<decltype(l),decltype(r)>){
      return l < r;
  } else if constexpr(std::is_same_v<std::string const &, decltype (r)>){
    return l.name < r;
  } else {
    return l < r.name;
  }
}};
using ModuleSet = std::set<struct ModuleNode, decltype(ModuleStringLess) >;
using ModuleNodeRef = typename ModuleSet::const_iterator;
using ModuleRefs = std::vector<ModuleNodeRef>;
struct cyclic_dependency{};
struct ModuleNode {
  std::string name{}; // only data member used for identity
  mutable ModuleRefs required{};
  mutable unsigned semester{unknown_semester};
  struct AllModules {
    ModuleSet all{};
    AllModules() = default;
    explicit AllModules(std::istream &in);

    auto find(std::string modulename) const {
      return all.find(modulename);
    }
    auto schedule(unsigned semester) const & {
      ModuleRefs semesterschedule{};
      for(auto module = begin(all); module != end(all); ++module){
        if (module->isReady(semester) && module->semester == unknown_semester){
          module->semester= semester;
          semesterschedule.push_back(module);
        }
      }
      return semesterschedule;
    }
    ModuleNodeRef insert(std::string modulename) &;
    auto scheduleAll() const & {
      unsigned semester{0u};
      std::vector<ModuleRefs> result{};
      do {
        auto semesterschedule = schedule(++semester);
        if (semesterschedule.size()) result.push_back(semesterschedule);
        else break;
      } while (true);
      if (any_of(begin(all),end(all),[](auto const &module){ return module.semester == unknown_semester;})){
        throw cyclic_dependency{};
      }
      return result;
    }
    void printSchedule(std::ostream&) const;
  };

  ModuleNode(std::string modulename)
  : name{modulename}{}
  bool isReady(unsigned semester) const {
    return all_of(begin(required),end(required),[semester](auto const &nodeiter){
      return nodeiter->semester < semester;
    });
  }
  auto operator<=>(ModuleNode const &other) const  {
    return name <=> other.name;
  }
  bool operator==(ModuleNode const &other) const  {
    return name == other.name;
  }
  void addRequired(std::string modulename, ModuleNode::AllModules &theModules) const & {
    required.push_back(theModules.insert(modulename));
  }
  bool schedule(unsigned semester) const  & {
    if (semester >0 && isReady(semester-1)) {
      this->semester = semester;
      return true;
    } else {
      return false;
    }
  }
  constexpr static unsigned unknown_semester = -1; // really big
};


void print_semester_topological(std::istream &in, std::ostream & out);


#endif /* MODULENODE_H_ */
