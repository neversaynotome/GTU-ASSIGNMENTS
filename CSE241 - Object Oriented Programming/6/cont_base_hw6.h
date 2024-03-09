#ifndef _CONT_BASE_HW6_H_
#define _CONT_BASE_HW6_H_

#include <cstddef>		// Base "Iterable" class

namespace GTU {

template<class T>
class Iterable{
public:
	virtual bool empty() const = 0;
	virtual size_t size() const = 0;
	virtual void erase( GTUIterator<T> ) = 0;
	virtual void clear() = 0;
	virtual GTUIterator<T> begin() = 0;
	virtual GTUIterator<T> end() = 0;
	virtual const GTUIteratorConst<T> cbegin() const = 0;
	virtual const GTUIteratorConst<T> cend() const = 0;
};
}

#endif