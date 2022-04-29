

char min(char left, char right) {
  return left < right ? left : right;
}

short min(short left, short right) {
  return left < right ? left : right;
}

int min(int left, int right) {
  return left < right ? left : right;
}

long min(long left, long right) {
  return left < right ? left : right;
}

long long min(long long left, long long right) {
  return left < right ? left : right;
}

unsigned char min(unsigned char left, unsigned char right) {
  return left < right ? left : right;
}

unsigned short min(unsigned short left, unsigned short right) {
  return left < right ? left : right;
}

unsigned min(unsigned left, unsigned right) {
  return left < right ? left : right;
}

unsigned long min(unsigned long left, unsigned long right) {
  return left < right ? left : right;
}

unsigned long long min(unsigned long long left, unsigned long long right) {
  return left < right ? left : right;
}

float min(float left, float right) {
  return left < right ? left : right;
}

double min(double left, double right) {
  return left < right ? left : right;
}

long double min(long double left, long double right) {
  return left < right ? left : right;
}


namespace MyMin{
inline int min(int a, int b){
	return (a < b)? a : b ;
}
inline double min(double a, double b){
	return (a < b)? a : b ;
}}


int main() {
	using MyMin::min;
	return min(0,1.f);
}
