#ifndef TRACER_H_
#define TRACER_H_


#include <functional>
#include <ostream>
#include <string>
struct Tracer{
  explicit Tracer(std::string name, std::ostream &os)
  :name{name}, out{os}{
    out.get() << "Tracer created: " << name << '\n';
  }
  ~Tracer(){
    out.get() << "Tracer destroyed: " << name << '\n';
  }
  Tracer(Tracer const& other)
  :name{other.name+" copy"},out{other.out}{
    out.get() << "Tracer copied: " << name << '\n';
  }
  Tracer& operator=(Tracer const& other) &
  {
    out.get() << "Tracer copy=: " << name << '\n';
    name = other.name + " copy= ";
    out = other.out;
    out.get() << "Tracer now : " << name << '\n';
    return *this;
  }
  Tracer(Tracer && other)
  :name{other.name}// normally std::move(other.name), could empty string
  , out{other.out}{
    other.name+=" moved from"; // simulate "emptying" moved from value
    out.get() << "Tracer moved: "
          << name << '\n';
  }
  Tracer& operator=(Tracer && other) &
  {
    out.get() << "Tracer move=: " << name << '\n';
    name = other.name + " moved= was " + name;
    other.name = other.name + " moved from";
    std::swap(out,other.out); // typical trick
    out.get() << "Tracer now : " << name << '\n';
    return *this;
  }

  void show() const {
    out.get() << "Tracer: " << name << '\n';
  }
  std::string name{};
  std::reference_wrapper<std::ostream> out;
};


#endif /* TRACER_H_ */
