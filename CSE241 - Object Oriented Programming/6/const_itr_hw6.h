#ifndef _CONST_ITR_HW6_H_
#define _CONST_ITR_HW6_H_

#include <iostream>
#include <iterator>
#include <cstddef>
#include "itr_base_hw6.h"	// see "itr_hw6.h" for explanations

namespace GTU {

template<class T>
class GTUIteratorConst : public IteratorBase<T>{
public:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

	GTUIteratorConst() { ptr = nullptr; }
	GTUIteratorConst(T* ptr) : ptr(ptr) {}
	T& operator*() const { return *ptr; }
	T* operator->() { return ptr; }
	friend bool operator== (const GTUIteratorConst& F, const GTUIteratorConst& S) { return F.ptr == S.ptr; };
	friend bool operator!= (const GTUIteratorConst& F, const GTUIteratorConst& S) { return F.ptr != S.ptr; };  
private:
        T* ptr;
    };
}

#endif