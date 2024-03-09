#ifndef _ITR_HW6_H_
#define _ITR_HW6_H_

#include <iostream>
#include <iterator>
#include <cstddef>
#include "itr_base_hw6.h"	// a standard iterator implementation

namespace GTU {

template<class T>
class GTUIterator : public IteratorBase<T>{
public:
	typedef T value_type;	// lines 14-18 are to create compatibility for <algorithm> functions
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

	GTUIterator() { ptr = nullptr; }	// constructors
	GTUIterator(T* ptr) : ptr(ptr) {}
	T& operator * () const { return *ptr; }	// overloads
	T* operator -> () { return ptr; }
	GTUIterator& operator ++ () { ptr++; return *this; }  
	GTUIterator operator ++ (int) { GTUIterator temp = *this; ++(*this); return temp; }
	GTUIterator& operator -- () { ptr--; return *this; }  
	GTUIterator operator -- (int) { GTUIterator temp = *this; --(*this); return temp; }
	GTUIterator operator + (size_t X) { ptr += X; return *this; }  
	GTUIterator operator - (size_t X) { ptr -= X; return *this; }  
	friend bool operator== (const GTUIterator& F, const GTUIterator& S) { return F.ptr == S.ptr; };
	friend bool operator!= (const GTUIterator& F, const GTUIterator& S) { return F.ptr != S.ptr; };  
private:
        T* ptr;
};
}

#endif