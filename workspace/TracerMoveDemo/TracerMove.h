#ifndef TRACERMOVE_H_
#define TRACERMOVE_H_

#include <ostream>

#include <string>
struct Tracer{
  explicit Tracer(std::string name, std::ostream &out)
  :name{name}, out{out}{
    out << "Tracer created: "
          << name << '\n';
  }
  ~Tracer(){
    out << "Tracer destroyed: "
          << name << '\n';
  }
  Tracer(Tracer && other)
  :name{other.name}// normally std::move(other.name), could empty string
  , out{other.out}{
    other.name+=" moved from"; // simulate "emptying" moved from value
    out << "Tracer moved: "
          << name << '\n';
  }
  void show() const {
    out << "Tracer: "
          << name << '\n';
  }
  std::string name{};
  std::ostream &out;

};


#endif /* TRACERMOVE_H_ */
