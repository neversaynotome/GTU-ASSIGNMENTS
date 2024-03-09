#ifndef _ARRAY_HW6_H_
#define _ARRAY_HW6_H_

#include <cstddef>	// Implementation of "GTUArray" class
#include <memory>
#include <exception>
#include "cont_base_hw6.h"	// You are advised to check implementations from "set_hw6.h" header since it has higher function count
#include "itr_base_hw6.h"	// most of the explanations are provided there

namespace GTU {

template<class T, size_t capacity>
class GTUArray : public Iterable<T>{
private:
	shared_ptr<T[]> seq;
public:
	GTUArray(const GTUArray &other){
		
		for (int i = 0; i < other.size(); ++i)
			(*this)[i] = other[i]; 
	}

	GTUArray(){

		shared_ptr<T[]> temp( new T[capacity] );
		seq = temp;
	}

	GTUArray(GTUArray&& other){

		if ( size() != other.size() ) throw;
		capacity = other.capacity;
		seq = other.seq;
		other.seq = nullptr;
    }

	bool empty() const{
		if ( size() == 0 )
			return true;

		return false;
	}

	size_t size() const{

		return capacity;
	}

	void erase( GTUIterator<T> toerase ){}	// "erase" in GTUArray makes no sense so it is not implemented

	void clear(){

		seq = nullptr;
	};

	GTUIterator<T> begin() { return GTUIterator<T>( seq.get() ); }
	GTUIterator<T> end() { return GTUIterator<T>( seq.get() + capacity ); }
	const GTUIteratorConst<T> cbegin() const { return GTUIteratorConst<T>( seq.get() ); }
	const GTUIteratorConst<T> cend() const { return GTUIteratorConst<T>( seq.get() + capacity ); }
	
	T& operator [] ( unsigned int index ) const{
	
		if (index >= size() || index < 0){
			std::cerr << "\nThe element you are trying to access is out of bounds!\n\n";
			throw "std::out_of_range";
		}
		return seq.get()[index];
	}

	GTUArray& operator = ( const GTUArray &other ){

		for (int i = 0; i < other.size(); ++i)
			(*this)[i] = other[i];

		return *this;
	}

	GTUArray& operator = ( GTUArray&& other ){

      if (&other != this){
        seq = other.seq;
        other.seq = nullptr;
      }

      return *this;
    }
    T* returnData() { return seq.get(); }
};
}

#endif