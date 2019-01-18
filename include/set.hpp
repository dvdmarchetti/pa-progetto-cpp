#ifndef SET_HPP_
#define SET_HPP_

#include <ostream>
#include <algorithm>
#include <cassert>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

class value_already_exists {};
class value_does_not_exists {};

template <typename T, typename Equal = std::equal_to<T>>
class set {
private:
  struct node {
    T value;
    node* next;

    node() : next(0) {}
    node(const T &v, node *n = 0) : value(v), next(n) {}
  };

  node *_head;
  unsigned int _count;
  Equal _equal;

public:
  set() : _head(0), _count(0) {
    //
  }

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

  set &operator=(const set &other) {
    if (this == &other) {
      return *this;
    }

    set tmp(other);
    std::swap(_head, tmp._head);
    std::swap(_count, tmp._count);

    return *this;
  }

  ~set() {
    clear();
  }

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

  T operator[](int index) {
    assert(_count >= index);

    int items = 0;
    node *tmp = _head;

    while (tmp != 0 && items < index) {
      tmp = tmp->next;
      items++;
    }

    // TODO: Checks
    return tmp->value;
  }

  void add(const T &value) {
    if (contains(value)) {
      throw new value_already_exists();
    }

    node *n = new node(value);

    n->next = _head;
    _head = n;
    _count++;
  }

  void remove(const T &value) {
    if (! contains(value)) {
      throw new value_does_not_exists();
    }

    node *tmp = _head, *prev = _head;
    while (tmp != 0 && ! _equal(tmp->value, value)) {
      prev = tmp;
      tmp = tmp->next;
    }

    prev->next = tmp->next;
    delete tmp;
    _count--;
  }

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

  void clear() {
    node *tmp = _head;

    while (tmp != 0) {
      node *next = tmp->next;
      delete tmp;
      tmp = next;
    }

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

  class const_iterator {
	private:
    const node *_current;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

		const_iterator()
      : _current(0) {
			//
		}

		const_iterator(const const_iterator &other)
      : _current(other._current) {
			//
		}

		const_iterator& operator=(const const_iterator &other) {
			_current = other._current;
      return *this;
		}

		~const_iterator() {
			//
		}

		reference operator*() const {
			return _current->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(_current->value);
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
      _current = _current->next;
      return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			_current = _current->next;
      return _current;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return _current == other._current;
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return _current != other._current;
		}

	private:
		friend class set;

		const_iterator(const node *p) : _current(p) {
			//
		}
	};

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_head);
	}

	const_iterator end() const {
		return const_iterator(0);
	}
};

template <typename T, typename E>
std::ostream &operator<<(std::ostream &stream, const set<T, E> &set) {
  typename set<T, E>::const_iterator begin, end;

  begin = set.begin();
  end = set.end();

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
#endif // SET_HPP_
