#ifndef TRACER_H_
#define TRACER_H_

#include <ostream>
#include <string>
struct Tracer{
  explicit Tracer(std::string name, std::ostream &out)
  :name{name}, out{out}{
    out << "Tracer created: " << name << '\n';
  }
  ~Tracer(){
    out << "Tracer destroyed: " << name << '\n';
  }
  Tracer(Tracer const& other)
  :name{other.name+" copy"},out{other.out}{
    out << "Tracer copied: " << name << '\n';
  }
  void show() const {
    out << "Tracer: " << name << '\n';
  }
  std::string name{};
  std::ostream &out;
};


#endif /* TRACER_H_ */
