#ifndef SET_HPP_
#define SET_HPP_

#include <ostream>
#include <algorithm>
#include <cassert>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

/**
 * @brief Exception raised when a value is trying to be added
 * but it already exists
 */
class value_already_exists {};

/**
 * @brief Exception raised when a value is trying to be removed
 * but it hasn't been found in the set.
 */
class value_does_not_exist {};

/**
 * @brief Set data structure implementation with no duplicated data allowed
 *
 * @tparam T value type
 * @tparam std::equal_to<T> equal functor for items comparsion
 */
template <typename T, typename Equal = std::equal_to<T>>
class set {
private:
  /**
   * @brief Node structs for dynamic list implementation.
   * Each node holds reference to the next element in the
   * list or null(0).
   */
  struct node {
    /**
     * @brief Templated value data.
     */
    T value;
    /**
     * @brief Next list item pointer
     */
    node* next;

    node() : next(0) {}
    node(const T &v, node *n = 0) : value(v), next(n) {}
  };

  node *_head;
  unsigned int _count;
  Equal _equal;

public:
  /**
   * @brief Default empty constructor
   *
   * @return
   */
  set() : _head(0), _count(0) {
    //
  }

  /**
   * @brief Copy constructor
   *
   * @param other object from where we're copying the values
   * @return
   */
  set(const set &other) : _head(0), _count(0) {
    node *tmp = other._head;

    try {
      while (tmp != 0) {
        add(tmp->value);
        tmp = tmp->next;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  /**
   * @brief Assign values from another set
   *
   * @param other object from where we're copying the values
   * @return
   */
  set &operator=(const set &other) {
    if (this == &other) {
      return *this;
    }

    set tmp(other);
    std::swap(_head, tmp._head);
    std::swap(_count, tmp._count);

    return *this;
  }

  /**
   * @brief Clean up nodes
   *
   * @return
   */
  ~set() {
    clear();
  }

  /**
   * @brief Initialize a new set from a pair of iterators (begin/end)
   * of any type (generic class).
   *
   * @param begin Iterator pointing at the starting point
   * @param end Iterator pointing to the end
   * @return
   */
  template <typename I>
  set(I begin, I end) : _head(0), _count(0) {
    try {
      while (begin != end) {
        add(static_cast<T>(*begin));
        begin++;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  /**
   * @brief Read-only array style access to the set's data
   *
   * @param index Index of the element to be read
   * @return element at index's position
   */
  T operator[](int index) const {
    assert(index < _count && index >= 0);

    int items = 0;
    node *tmp = _head;

    while (tmp != 0 && items < index) {
      tmp = tmp->next;
      items++;
    }

    return tmp->value;
  }

  /**
   * @brief Insert a new value to the end of the set
   *
   * @param value Value to be inserted
   * @return
   * @throws value_already_exists
   */
  void add(const T &value) {
    if (contains(value)) {
      throw new value_already_exists();
    }

    node *n = new node(value);
    n->next = 0;

    if (_head == 0) {
      _head = n;
      _count++;
      return;
    }

    node *tmp = _head;
    while (tmp->next != 0) {
      tmp = tmp->next;
    }

    tmp->next = n;
    _count++;
  }

  /**
   * @brief Remove an element from the list by value
   *
   * @param value The value to be removed
   * @return
   * @throws value_does_not_exist
   */
  void remove(const T &value) {
    if (! contains(value)) {
      throw new value_does_not_exist();
    }

    node *tmp = _head, *prev = _head;
    while (tmp != 0 && ! _equal(tmp->value, value)) {
      prev = tmp;
      tmp = tmp->next;
    }

    if (tmp == prev) {
      _head = tmp->next;
    } else {
      prev->next = tmp->next;
    }

    delete tmp;
    tmp = 0;
    _count--;
  }

  /**
   * @brief Check if the value is present into the set
   *
   * @param value The value to be checked
   * @return true if present | false otherwise
   */
  bool contains(const T &value) const {
    node *tmp = _head;
    while (tmp != 0) {
      if (_equal(tmp->value, value)) {
        return true;
      }

      tmp = tmp->next;
    }

    return false;
  }

  /**
   * @brief Remove all the elements from the set, freeing up memory
   *
   * @return
   */
  void clear() {
    node *tmp = _head;

    while (tmp != 0) {
      node *next = tmp->next;

      delete tmp;
      tmp = 0;

      tmp = next;
    }

    _head = 0;
    _count = 0;
  }

  /**
   * @brief Conteggio degli elementi
   *
   * @return unsigned int
   */
  unsigned int count() const {
    return _count;
  }

  /**
   * @brief Const iterator implementation
   */
  class const_iterator {
	private:
    /**
     * @brief Pointer to the current element of the set
     */
    const node *_current;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

    /**
     * @brief Construct const_iterator pointing to null
     *
     * @return
     */
		const_iterator()
      : _current(0) { }

    /**
     * @brief Construct const iterator as a copy of another one
     *
     * @param other The reference const_iterator
     * @return
     */
		const_iterator(const const_iterator &other)
      : _current(other._current) { }

    /**
     * @brief Assignment operator
     *
     * @param other The reference const_iterator
     * @return
     */
		const_iterator& operator=(const const_iterator &other) {
			_current = other._current;
      return *this;
		}

    /**
     * @brief Destructor
     *
     * @return
     */
		~const_iterator() {
			//
		}

    /**
     * @brief Return the current value while dereferencing a pointer
     *
     * @return Value of the current pointed element
     */
		reference operator*() const {
			return _current->value;
		}

		/**
     * @brief Return the address of the pointed element's value.
     *
     * @return Address of the current pointed value
     */
		pointer operator->() const {
			return &(_current->value);
		}

		// Operatore di iterazione post-incremento
    /**
     * @brief Post-increment operator
     *
     * @return The current element as a cloned const_iterator
     */
		const_iterator operator++(int) {
			const_iterator tmp(*this);
      _current = _current->next;
      return tmp;
		}

		// Operatore di iterazione pre-incremento
    /**
     * @brief Pre-increment operator
     *
     * @return A reference to the next element in the set as a const_iterator
     */
		const_iterator &operator++() {
			_current = _current->next;
      return *this;
		}

		// Uguaglianza
    /**
     * @brief Compare two const_iterators for equality
     *
     * @return true if pointing to the same element | false otherwise
     */
		bool operator==(const const_iterator &other) const {
			return _current == other._current;
		}

		// Diversita'
    /**
     * @brief Compare two const_iterator for inequality
     *
     * @return true if pointing to different elements | false otherwise
     */
		bool operator!=(const const_iterator &other) const {
			return _current != other._current;
		}

	private:
		friend class set;

		const_iterator(const node *p)
      : _current(p) { }
	};

	/**
   * @brief Create a begin const_iterator
   *
   * @return A const_iterator pointing to the _head of the set's data
   */
	const_iterator begin() const {
		return const_iterator(_head);
	}

  /**
   * @brief Create an end const_iterator
   *
   * @return A const_iterator pointing to the _end of the set's data
   */
	const_iterator end() const {
		return const_iterator(0);
	}
};

/**
 * @brief Print operator for a generic set
 *
 * @param stream the output stream to print on
 * @param s the set to be printed
 * @return the output stream
 */
template <typename T, typename E>
std::ostream &operator<<(std::ostream &stream, const set<T, E> &s) {
  typename set<T, E>::const_iterator begin, end;

  begin = s.begin();
  end = s.end();

  stream << "{";
  while (begin != end) {
    stream << *begin;
    begin++;

    if (begin != end) {
      stream << ", ";
    }
  }
  stream << "}";

  return stream;
}

/**
 * @brief Return a new set with elements which doesn't
 * satisfy the condition
 *
 * @param s the set to filter
 * @param condition filtering condition
 * @return the new set with elements not matching the condition
 */
template <typename T, typename E, typename P>
set<T, E> filter_out(const set<T, E> &s, P condition) {
  set<T, E> tmp;
  typename set<T, E>::const_iterator begin, end;

  for (begin = s.begin(), end = s.end(); begin != end; begin++) {
    if (! condition(*begin)) {
      tmp.add(*begin);
    }
  }

  return tmp;
}

/**
 * @brief Concatenate two sets and return a new one
 *
 * @param s1 the first set
 * @param s2 the second set
 * @return the new set containing all the elements from the given ones
 */
template <typename T, typename E>
set<T, E> operator+(const set<T, E> &s1, const set<T, E> &s2) {
  set<T, E> tmp(s1);
  typename set<T, E>::const_iterator begin, end;

  for (begin = s2.begin(), end = s2.end(); begin != end; begin++) {
    tmp.add(*begin);
  }

  return tmp;
}

#endif // SET_HPP_
