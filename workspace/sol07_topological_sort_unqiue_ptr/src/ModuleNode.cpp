#include "ModuleNode.h"
#include <sstream>


ModuleNode::AllModules::AllModules(std::istream &input) {
  std::string line{};
  while (std::getline(input, line)) {
    std::istringstream is { line };
    std::string name;
    if (is >> name) {
      auto current = insert(name);
      while (is >> name) {
        current.get().addRequired(name, *this);
      }
    }
  }
  sort(begin(all),end(all));
}

ModuleNodeRef ModuleNode::AllModules::insert(std::string modulename) & {
  auto iter = this->find(modulename);
  if (iter != end(all)) {
    return **iter; // already there
  }
  auto newmodule = std::make_unique<ModuleNode>(modulename);
  ModuleNodeRef result{*newmodule};
  all.push_back(std::move(newmodule));
  return result;
}

void ModuleNode::AllModules::printSchedule(std::ostream &out) const {
  unsigned semester{0u};
  auto last = begin(all);
  while(last != end(all)){
    ++semester;
    out << semester << " : ";
    auto const next = partition_point(last,end(all),[semester](auto const &mp){ return mp && mp->semester == semester;});
    for_each(last,next,[&out](auto const &mp){ if (mp) out << mp->name << ", ";});
    out << '\n';
    last = next;
  }
}

void print_semester_topological(std::istream &in, std::ostream & out){
  ModuleNode::AllModules theModules{in};
  theModules.scheduleAll();
  theModules.printSchedule(out);
}

