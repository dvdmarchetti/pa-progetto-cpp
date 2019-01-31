#include <iostream>
#include "set.hpp"

struct voce {
  std::string nome;
  std::string telefono;

  voce(std::string n, std::string tel) : nome(n), telefono(tel)
  {
    //
  }
};

struct voce_equals {
  bool operator()(const voce &v1, const voce &v2) const {
    return v1.telefono == v2.telefono;
  }
};

std::ostream &operator<<(std::ostream &stream, const voce &voce) {
  stream << "[" << voce.nome << ": " << voce.telefono << "]";
  return stream;
};

struct is_even {
  bool operator()(const int x) {
    return x % 2 == 0;
  }
};

struct is_odd {
  bool operator()(const int x) {
    return x % 2 == 1;
  }
};

void test_fondamentali() {
  set<int> s;

  // Add
  std::cout << "# Adding elements to set #" << std::endl;
  s.add(5);
  s.add(3);
  s.add(10);
  s.add(11);

  // Count + ostream<<
  std::cout << "S1 = " << s << " // Count: " << s.count() << std::endl;
  assert(s.count() == 4);

  std::cout << std::endl;

  // Copy constructor
  std::cout << "# Copying s1 to s2 with copy constructor #" << std::endl;
  set<int> s2(s), s3;
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;

  std::cout << std::endl;

  // Remove
  std::cout << "# Removing element '10' to s2 #" << std::endl;
  s2.remove(10);
  assert(s2.count() == 3);
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;

  std::cout << std::endl;

  // Operator =
  s3 = s2;
  std::cout << "# Cloning object with operator= into s3 #" << std::endl;
  assert(s3.count() == 3);
  std::cout << "S3 = " << s3 << " // Count: " << s3.count() << std::endl;

  std::cout << std::endl;

  // Operator[]
  std::cout << "# Printing the value at index 1 from a set with operator[] #" << std::endl;
  std::cout << "S3[1] = " << s3[1] << std::endl;

  std::cout << std::endl;

  // Contains
  std::cout << "# Contains method #" << std::endl;
  std::cout << "S1 = " << s << " // Count: " << s.count() << std::endl;
  std::cout << "Does S1 contain value 4? " << s.contains(4) << std::endl;

  std::cout << std::endl;

  std::cout << "# Adding value 4 to set #" << std::endl;
  s.add(4);
  std::cout << "S1 = " << s << " // Count: " << s.count() << std::endl;
  std::cout << "Does S1 contain value 4? " << s.contains(4) << std::endl;

  std::cout << std::endl;

  // Removing all the elements
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;
  std::cout << "# Removing all the elements one by one from the set s2 #" << std::endl;
  s2.remove(11);
  s2.remove(5);
  s2.remove(3);
  assert(s2.count() == 0);
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;

  std::cout << std::endl;

  // Clear
  std::cout << "# Clearing out the set S3 #" << std::endl;
  s3.clear();
  std::cout << "S3 = " << s3 << " // Count: " << s3.count() << std::endl;

  std::cout << std::endl;

  // Filter out
  std::cout << "# Calling filter_out global function on S1 #" << std::endl;
  set<int> even = filter_out(s, is_even());
  std::cout << "EVEN = " << even << std::endl;
  set<int> odd = filter_out(s, is_odd());
  std::cout << "ODD = " << odd << std::endl;

  std::cout << std::endl;

  // Concatenate sets
  std::cout << "# Concatenate two sets (even and odds) #" << std::endl;
  std::cout << "EVEN + ODD = " << even + odd << std::endl;
}

void test_struct() {
  set<voce, voce_equals> s;

  // Add
  std::cout << "# Adding elements to set #" << std::endl;
  s.add(voce("Marco", "1234567890"));
  s.add(voce("Giovanni", "123456789"));
  s.add(voce("Marco", "9876543210"));

  std::cout << s;
}

int main() {
  std::cout << "!! Test fondamentali !!" << std::endl;
  test_fondamentali();
  std::cout << std::endl;

  std::cout << "!! Test struct !!" << std::endl;
  test_struct();
}
