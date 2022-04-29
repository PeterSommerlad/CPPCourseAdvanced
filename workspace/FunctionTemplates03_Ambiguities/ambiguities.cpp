template <typename T>
T min(T left, T right) {
  return left < right ? left : right;
}


int main() {
	min<int>(1, 1.0);
}
