#ifndef _VECTOR_HW6_H_
#define _VECTOR_HW6_H_

#include <cstddef>	// Implementation of "GTUVector" class
#include <memory>
#include <exception>
#include "cont_base_hw6.h"	// You are advised to check implementations from "set_hw6.h" header since it has higher function count
#include "itr_base_hw6.h"	// most of the explanations are provided there

using std::shared_ptr;

namespace GTU{

template<class T>
class GTUVector : public Iterable<T>{
private:
	shared_ptr<T[]> seq;
	size_t elements = 0;
	size_t capacity = 0;
public:
	GTUVector(){ seq = nullptr; }

	GTUVector(GTUVector &other){
		
		for (int i = 0; i < other.size(); ++i)
			add( other[i] );
	}

	GTUVector(GTUVector&& other){

		clear();
		capacity = other.capacity;
		elements = other.elements;
		seq = other.seq;
		other.seq = nullptr;
    }

	bool empty() const{
		if (size() == 0)
			return true;

		return false;
	}

	size_t size() const{

		return elements;
	}

	void erase( const GTUIterator<T> toerase ){

		size_t erase;

		for (auto i = 0; i < size(); ++i)
			if( seq.get()[i] == (*toerase) ) erase = i;

		for (auto i = erase; i < size()-1; ++i)
			seq.get()[i] = seq.get()[i+1];

		if (elements != 0) --elements;
	}

	void clear(){

		seq = nullptr;
		capacity = elements = 0;
	};

	GTUIterator<T> begin() { return GTUIterator<T>( seq.get() ); }
	GTUIterator<T> end() { return GTUIterator<T>( seq.get() + elements ); }
	const GTUIteratorConst<T> cbegin() const { return GTUIteratorConst<T>( seq.get() ); }
	const GTUIteratorConst<T> cend() const { return GTUIteratorConst<T>( seq.get() + elements ); }

	void add( T toadd ){

		if ( capacity == 0 ){					// Initialize if "capacity" is 0

		shared_ptr<T[]> temp(new T[1]);
		temp.get()[0] = toadd; seq = temp;
		++elements; ++capacity;
		}
		else if ( capacity == elements ){		// no more capacity left so new elements now can hold double the amount of elements
	
			capacity *= 2;
			shared_ptr<T[]> temp(new T[capacity]);
	
			for (auto i = 0; i < size(); ++i)
				temp.get()[i] = seq.get()[i];	// Copying older elements
	
			seq = temp;
			seq.get()[elements++] = toadd;
		}
		else 
			seq.get()[elements++] = toadd;		// Array has appropiate place for new element so just add it
	}
	
	T& operator [] ( unsigned int index ) const{
	
		if (index >= size() || index < 0){
			std::cerr << "\nThe element you are trying to access is out of bounds!\n";
			throw "std::out_of_range";
		}
		return seq.get()[index];
	}

	void operator = (GTUVector const &other){
		clear();
		for (int i = 0; i < other.size(); ++i)
			add( other[i] );
	}

	GTUVector& operator = ( GTUVector&& other ){

      if (&other != this){
		capacity = other.capacity;
		elements = other.elements;
        seq = other.seq;
        other.seq = nullptr;
      }

      return *this;
    }
    T* returnData() { return seq.get(); }
};
}

#endif