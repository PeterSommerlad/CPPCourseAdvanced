#ifndef MYMIN_H_
#define MYMIN_H_
namespace MyMin{
template <typename T>
T min(T a, T b){
	return (a < b)? a : b ;
}
}
#endif