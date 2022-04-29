#include "TracerMove.h"
#include <iostream>
void foo(Tracer t){
	Tracer trace("foo", t.out);
	t.show();
}
Tracer bar(Tracer const &t){
	Tracer trace("bar", t.out);
	t.show();
	return trace;
}
Tracer rvo(Tracer const &t){
  Tracer trace("rvo-func",t.out);
  t.show();
  return Tracer("rvo",t.out);
}

int main(){
	Tracer m("main",std::cout);
	{
		Tracer inner("inner", std::cout);
		foo(std::move(inner));
		auto trace=bar(inner);
		trace.show();
		inner.show();
    auto rvotrace=rvo(trace);
    rvotrace.show();
	}
	foo(Tracer("temp",std::cout));
	m.show();
}
