#include <iostream>
#include "set.hpp"

template <typename T, typename E, typename F>
set<T, E> filter_out(const set<T, E> s1, const set<T, E> s2, F pred) {
  set<T, E> tmp = new set<T, E>();
  typename set<T, E>::const_iterator begin, end;

  for (begin = s1.begin(), end = s1.end(); begin != end; begin++) {
    if (pred(*begin)) {
      tmp.add(*begin);
    }
  }

  for (begin = s2.begin(), end = s2.end(); begin != end; begin++) {
    if (pred(*begin)) {
      tmp.add(*begin);
    }
  }
}

void test_fondamentali() {
  set<int> s;

  s.add(5);
  s.add(3);
  s.add(10);
  s.add(11);

  std::cout << "Count: " << s.count() << std::endl;
  std::cout << s << std::endl;
  assert(s.count() == 4);

  s.remove(10);
  std::cout << "Count: " << s.count() << std::endl;
  std::cout << s << std::endl;
  assert(s.count() == 3);
}

int main() {
  test_fondamentali();
}
