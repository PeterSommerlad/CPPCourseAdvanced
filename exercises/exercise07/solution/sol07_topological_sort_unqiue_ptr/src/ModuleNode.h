#ifndef MODULENODE_H_
#define MODULENODE_H_


#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <memory>
#include <iosfwd>
#include <functional>

using ModuleNodePtr = std::unique_ptr<struct ModuleNode>;
using ModuleNodeRef = std::reference_wrapper<struct ModuleNode>;
struct cyclic_dependency{};
struct ModuleNode {
  std::string name{};
  std::vector<ModuleNodeRef> required{};
  unsigned semester{unknown_semester};
  struct AllModules {
    std::vector<ModuleNodePtr> all{};
    AllModules() = default;
    AllModules(std::istream &in);

    auto find(std::string modulename) const {
      return find_if(cbegin(all), cend(all), [modulename](auto const & nodeptr){
        return nodeptr && nodeptr->name == modulename;
      });
    }
    auto schedule(unsigned semester) & {
      auto res = stable_partition(begin(all),end(all),[semester](auto const & m){ return m && m->isReady(semester);});
      for_each(begin(all),res,[semester](auto const& m){ if (m && m->semester == unknown_semester) m->semester = semester;});
      return res;
    }
    ModuleNodeRef insert(std::string modulename) &;
    void scheduleAll() & {
      unsigned semester{0u};
      auto last = begin(all);
      while(last != end(all)){
        auto const next = schedule(++semester);
        if (next == last) throw cyclic_dependency{};
        last = next;
      }
    }
    void printSchedule(std::ostream&) const;
  };

  ModuleNode(std::string modulename)
  : name{modulename}{}
  bool isReady(unsigned semester){
    return all_of(begin(required),end(required),[semester](auto const &noderef){
      return noderef.get().semester < semester;
    });
  }
  auto operator<=>(ModuleNode const &other) const  {
    return name <=> other.name;
  }
  bool operator==(ModuleNode const &other) const  {
    return name == other.name;
  }
  void addRequired(std::string modulename, ModuleNode::AllModules &theModules) & {
    required.push_back(theModules.insert(modulename));
  }
  bool schedule(unsigned semester) & {
    if (semester >0 && isReady(semester-1)) {
      this->semester = semester;
      return true;
    } else {
      return false;
    }
  }
  constexpr static unsigned unknown_semester = -1; // really big
};

inline
bool operator==(ModuleNodePtr const &p, std::string const &name){
  return p && *p == name;
}

inline
auto operator<=>(ModuleNodePtr const &p, std::string const &name){
  if (p) return *p <=> name;
  return std::strong_ordering::less;
}
inline
bool operator==(ModuleNodePtr const &p, ModuleNodePtr const &r){
  return p && r && p->name == r->name;
}
inline
auto operator<=>(ModuleNodePtr const &p, ModuleNodePtr const &r){
  if (p && r) return p->name <=> r->name;
  return std::strong_ordering::less;
}
void print_semester_topological(std::istream &in, std::ostream & out);


#endif /* MODULENODE_H_ */
