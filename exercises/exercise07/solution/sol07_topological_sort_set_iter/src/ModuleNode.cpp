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
        current->addRequired(name, *this);
      }
    }
  }
}

ModuleNodeRef ModuleNode::AllModules::insert(std::string modulename) & {
  return all.insert(ModuleNode{modulename}).first;
}

void ModuleNode::AllModules::printSchedule(std::ostream &out) const {
  unsigned semester{0u};
  auto allschedules = scheduleAll();
  for (auto semesterschedule : allschedules) {
    ++semester;
    out << semester << " : ";
    for_each(begin(semesterschedule),end(semesterschedule),[&out](auto const mp){  out << mp->name << ", ";});
    out << '\n';
  }
}

void print_semester_topological(std::istream &in, std::ostream & out){
  ModuleNode::AllModules theModules{in};
  theModules.printSchedule(out);
}

