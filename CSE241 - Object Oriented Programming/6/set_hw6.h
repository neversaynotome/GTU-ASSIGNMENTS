#ifndef _SET_HW6_H_
#define _SET_HW6_H_

#include <cstddef>	// Implementation of "GTUSet" class
#include <memory>
#include <exception>
#include "cont_base_hw6.h"
#include "itr_base_hw6.h"

using std::shared_ptr;

namespace GTU{

template<class T>
class GTUSet : public Iterable<T>{
private:
	shared_ptr<T[]> seq;	// shared_ptr for data keeping
	size_t elements = 0;
	size_t capacity = 0;
public:
	GTUSet(){
		seq = nullptr;
	};

	GTUSet(GTUSet &other){	// copy constructor
		
		for (int i = 0; i < other.size(); ++i)
			add( other.seq.get()[i] );
	}

	GTUSet(GTUSet&& other){	// move constructor
		
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

	void erase( GTUIterator<T> toerase ){

		size_t erase;

		for (auto i = 0; i < size(); ++i)				// using iterator, index of the element that is going to be deleted is found
			if( seq.get()[i] == (*toerase) ) erase = i;

		for (auto i = erase; i < size()-1; ++i)
			seq.get()[i] = seq.get()[i+1];				// set is shrunk by overwriting that element

		if (elements != 0) --elements;
	}

	void clear(){

		seq = nullptr;
		capacity = elements = 0;
	};

	GTUIterator<T> begin() { return GTUIterator<T>( seq.get() ); }				// returning expected iterators according to pdf 
	GTUIterator<T> end() { return GTUIterator<T>( seq.get() + elements ); }
	const GTUIteratorConst<T> cbegin() const { return GTUIteratorConst<T>( seq.get() ); }
	const GTUIteratorConst<T> cend() const { return GTUIteratorConst<T>( seq.get() + elements ); }

	bool isPresent(const T& toadd) const{	// Looks if an element is present in the set
		for (auto i = 0; i < size(); ++i)
			if ( seq.get()[i] == toadd ) return true;
		return false;
	}

	void add( T toadd ){

		if ( isPresent( toadd ) ) std::cerr << "\nThe value you are trying to add already exists!\n";
		else
		if ( capacity == 0 ){					// Initialize if "capacity" is 0

		shared_ptr<T[]> temp(new T[1]);
		temp.get()[0] = toadd; seq = temp;
		++elements; ++capacity;
		}
		else if ( capacity == elements ){		// no more capacity left so new "seq" now can hold double the amount of elements
	
			capacity *= 2;
			shared_ptr<T[]> temp(new T[capacity]());
	
			for (auto i = 0; i < size(); ++i)
				temp.get()[i] = seq.get()[i];	// Copying older elements
	
			seq = temp;
			seq.get()[elements++] = toadd;
		}
		else
			seq.get()[elements++] = toadd;		// "seq" has appropiate place for new element so just add it

		std::sort( returnData(), returnData() + size() );	// "std::sort" is used to keep set sorted
	}

	void delete_member( T todelete ) {

		GTUIterator<int> ptr;

		for (auto i = 0; i < size(); ++i)		// After elment that is going to be deleted is found an iterator pointing it is sent to "erase"
			if( seq.get()[i] == todelete ) erase( GTUIterator<T>( seq.get() + i ) );
	}

	bool search( T find ) {

		for (auto i = 0; i < size(); ++i)
			if( seq.get()[i] == find ) return true;

		return false;
	} 

	void operator = (GTUSet const &other){	// assignment operator
		clear();
		for (int i = 0; i < other.size(); ++i)
			add( other.seq.get()[i] );
	}

	GTUSet& operator = ( GTUSet&& other ){	// move assignment

      if (&other != this){
		capacity = other.capacity;
		elements = other.elements;
        seq = other.seq;
        other.seq = nullptr;
      }

      return *this;
    }

	GTUSet operator + (const GTUSet& other){

	GTUSet U(*this);					// First set is added right away

	for (int i = 0; i < other.size(); ++i)
		if ( !( U.isPresent( other.seq.get()[i] ) ) )
			U.add( other.seq.get()[i] );				// If first set has the elements of the second set don't add it!
	
	return U;
	}

	GTUSet operator ^ (const GTUSet& other){

	GTUSet IS;

	for (int i = 0; i < other.size(); ++i)
		if ( ( (*this).isPresent( other.seq.get()[i] ) ) )				// Add it if and only if both sets have the element
			IS.add( other.seq.get()[i] );
	
	return IS;
	}
    T* returnData() { return seq.get(); }	// for "std::sort"
};
}

#endif