#include <iostream>
#include "set.hpp"

/**
 * @brief Struct functor for filter_out function testing
 */
struct is_even {
  bool operator()(const int x) {
    return x % 2 == 0;
  }
};

/**
 * @brief Struct functor for filter_out function testing
 */
struct is_odd {
  bool operator()(const int x) {
    return x % 2 == 1;
  }
};

/**
 * @brief Voce struct with basic string fields.
 */
struct voce {
  std::string nome;
  std::string telefono;

  /**
   * @brief Construct a new voce object with parameters
   *
   * @param n contact name
   * @param tel phone number
   */
  voce(std::string n, std::string tel)
    : nome(n), telefono(tel) { }
};

std::ostream &operator<<(std::ostream &stream, const voce &voce) {
  stream << "[" << voce.nome << ": " << voce.telefono << "]";
  return stream;
};

/**
 * @brief Struct functor used in set to check when two voce
 * objects are equal.
 */
struct voce_equals {
  bool operator()(const voce &v1, const voce &v2) const {
    return v1.nome == v2.nome && v1.telefono == v2.telefono;
  }
};

/**
 * @brief Struct functor for filter_out function testing.
 */
struct voce_name_lower_than_M {
  bool operator()(const voce &voce) {
    return voce.nome[0] < 'M';
  }
};

/**
 * @brief Struct functor for filter_out function testing.
 */
struct voce_name_greater_than_M {
  bool operator()(const voce &voce) {
    return voce.nome[0] >= 'M';
  }
};

struct set_equal {
  bool operator()(const set<int> &set1, const set<int> &set2) const {
    set<int>::const_iterator begin1, end1, begin2, end2;
    begin1 = set1.begin(); end1 = set1.end();
    begin2 = set2.begin(); end2 = set2.end();

    while (begin1 != end1 && begin2 != end2) {
      if (*begin1 != *begin2) {
        return false;
      }

      ++begin1;
      ++begin2;
    }

    return begin1 == end1 && begin2 == end2;
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
  s.add(voce("Marco", "1231231231"));
  s.add(voce("Anna", "4564564564"));
  s.add(voce("Paolo", "7897897897"));

  // Count + ostream<<
  std::cout << "S1 = " << s << " // Count: " << s.count() << std::endl;
  assert(s.count() == 3);

  std::cout << std::endl;

  // Copy constructor
  std::cout << "# Copying s1 to s2 with copy constructor #" << std::endl;
  set<voce, voce_equals> s2(s), s3;
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;

  std::cout << std::endl;

  // Remove
  std::cout << "# Removing [Marco: 1231231231] to s2 #" << std::endl;
  s2.remove(voce("Marco", "1231231231"));
  assert(s2.count() == 2);
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;

  std::cout << std::endl;

  // Operator =
  s3 = s2;
  std::cout << "# Cloning object with operator= into s3 #" << std::endl;
  assert(s3.count() == 2);
  std::cout << "S3 = " << s3 << " // Count: " << s3.count() << std::endl;

  std::cout << std::endl;

  // Operator[]
  std::cout << "# Printing the value at index 1 from a set with operator[] #" << std::endl;
  std::cout << "S3[1] = " << s3[1] << std::endl;

  std::cout << std::endl;

  // Contains
  voce contact = voce("Pietro", "1093827643");

  std::cout << "# Contains method #" << std::endl;
  std::cout << "S1 = " << s << " // Count: " << s.count() << std::endl;
  std::cout << "Does S1 contain value [\"Pietro\", \"1093827643\"]? " << s.contains(contact) << std::endl;

  std::cout << std::endl;

  std::cout << "# Adding value 4 to set #" << std::endl;
  s.add(contact);
  std::cout << "S1 = " << s << " // Count: " << s.count() << std::endl;
  std::cout << "Does S1 contain value 4? " << s.contains(contact) << std::endl;

  std::cout << std::endl;

  // Removing all the elements
  std::cout << "S2 = " << s2 << " // Count: " << s2.count() << std::endl;
  std::cout << "# Removing all the elements one by one from the set s2 #" << std::endl;
  s2.remove(voce("Anna", "4564564564"));
  s2.remove(voce("Paolo", "7897897897"));
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
  set<voce, voce_equals> names_lower_than_m = filter_out(s, voce_name_lower_than_M());
  std::cout << "NAMES_LOWER = " << names_lower_than_m << std::endl;
  set<voce, voce_equals> names_greater_than_m = filter_out(s, voce_name_greater_than_M());
  std::cout << "NAMES_GREATER = " << names_greater_than_m << std::endl;

  std::cout << std::endl;

  // Concatenate sets
  std::cout << "# Concatenate two sets (even and odds) #" << std::endl;
  std::cout << "NAMES_GREATER + NAMES_LOWER = " << names_greater_than_m + names_lower_than_m << std::endl;
}

void test_dynamic_memory() {
  set<set<int>, set_equal> multi_set;

  // Add
  std::cout << "# Adding elements to multi set #" << std::endl;

  set<int> s1;
  s1.add(5);
  s1.add(10);
  s1.add(15);
  s1.add(20);

  set<int> s2;
  s2.add(4);
  s2.add(8);
  s2.add(12);
  s2.add(16);

  multi_set.add(s1);
  multi_set.add(s2);

  // Count + ostream<<
  std::cout << "MS1 = " << multi_set << " // Count: " << multi_set.count() << std::endl;
  assert(multi_set.count() == 2);

  std::cout << std::endl;

  // Copy constructor
  std::cout << "# Copying s1 to s2 with copy constructor #" << std::endl;
  set<set<int>, set_equal> cc_multi_set(multi_set);
  std::cout << "MS2 = " << cc_multi_set << " // Count: " << cc_multi_set.count() << std::endl;

  std::cout << std::endl;
}

int main() {
  std::cout << "!! Test fondamentali !!" << std::endl;
  test_fondamentali();
  std::cout << std::endl;

  std::cout << "!! Test struct !!" << std::endl;
  test_struct();
  std::cout << std::endl;

  std::cout << "!! Test dynamic memory !!" << std::endl;
  test_dynamic_memory();
}
