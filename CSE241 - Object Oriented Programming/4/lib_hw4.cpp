#include <iostream>
#include <vector>
#include "lib_hw4.h"

namespace GTUSET{

int DayofYearSet::totaldays = 0;

void DayofYearSet::DayofYear::setDate(int D, int M){

	if ( isValid(D, M) ){
		day = D; month = M;
	}
	else
		std::cerr << "\nInvalid input.\n";
}

void DayofYearSet::DayofYear::getDate() const{

	std::cout << "\nDay: " << day << " Month: " << month << std::endl;
}

void DayofYearSet::add(int D, int M){

	DayofYear test(D, M);

	if ( test.isValid(D, M) )													// The value is valid
	if ( isPresent( test ) ) std::cerr << "\nDuplicates are not allowed.\n";	// and it is not a duplicate too
	else																		// then it is ok to "add"
	if ( capacity == 0 ){					// Initialize if "capacity" is 0
		days[elements].setDate(D, M);
		++elements; ++capacity; ++totaldays;
	}
	else if ( capacity == elements ){		// no more capacity left so new "days" now can hold double the amount of elements

		DayofYear* temp = days;				// "temp" holds older array
		days = new DayofYear[capacity*2];
		capacity *= 2;

		for (int i = 0; i < size(); ++i)
			days[i].setDate( temp[i].getDay(), temp[i].getMonth() );	// Copying older elements

		delete [] temp;
		days[elements++].setDate(D, M); ++totaldays;
	}
	else {days[elements++].setDate(D, M); ++totaldays;}		// Array has appropiate place for new element so just add it
}

void DayofYearSet::remove(){

	DayofYear* temp = days; --elements; --totaldays;

	days = new DayofYear[capacity];
	
	for (int i = 0; i < elements; ++i)
		days[i].setDate( temp[i].getDay(), temp[i].getMonth() );

	delete [] temp;
}

bool DayofYearSet::isPresent(const DayofYear& D) const{

		for (int i = 0; i < size(); ++i)		// Iterate through the set and look if day is present in it
			if ( (*this)[i] == D ) return true;
	
	return false;
}

DayofYearSet::DayofYear& DayofYearSet::operator [] (int index) const{

	if (index >= size() || index < 0)
		std::cerr << "\nThe element you are trying to access is out of bounds!\n";

	return days[index];
}

std::ostream & operator << (std::ostream &out, const DayofYearSet &S){

	for (int i = 0; i < S.size(); ++i)
		S[i].getDate();					// Prints the days
	
	return out;
}

bool DayofYearSet::operator == (const DayofYearSet& S) const{

	if (size() != S.size()) return false;

	for (int i = 0; i < size(); ++i)
		if ( !( isPresent(S[i]) ) ) return false;

	return true;
}

DayofYearSet DayofYearSet::operator ! (){

	DayofYearSet complement; bool add;

	for (int m = 0; m < 12; ++m)
		for (int d = 1; d <= months[m]; ++d){		// If the set doesn't contain the element then add it to the complementary set

			add = true;
			for (int i = 0; i < size(); ++i) 
				if ( days[i].getDay() == d && days[i].getMonth() == m+1 ) add = false;

			if ( add ) complement.add(d, m+1);
		}

	return complement;
}

DayofYearSet DayofYearSet::operator + (const DayofYearSet& S){

	DayofYearSet U = (*this);	// First set is added right away

	for (int i = 0; i < S.size(); ++i)
		if ( !( U.isPresent(S[i]) ) ) U.add( S[i].getDay(), S[i].getMonth() );	// If first set has the elements of the second set don't add it!
	
	return U;
}

DayofYearSet DayofYearSet::operator - (const DayofYearSet& S){

	DayofYearSet D;

	for (int i = 0; i < S.size(); ++i)										// If second set doesn't have the element of the first set add it!
		if ( !( (*this).isPresent(S[i]) ) ) D.add( (*this)[i].getDay(), (*this)[i].getMonth() );
	
	return D;
}

DayofYearSet DayofYearSet::operator ^ (const DayofYearSet& S){

	DayofYearSet IS;

	for (int i = 0; i < S.size(); ++i)
		if ( ( (*this).isPresent(S[i]) ) )				// Add it if and only if both sets have the element
			IS.add( S[i].getDay(), S[i].getMonth() );
	
	return IS;
}

DayofYearSet::~DayofYearSet(){
	totaldays -= size();
	delete [] days;
}
}