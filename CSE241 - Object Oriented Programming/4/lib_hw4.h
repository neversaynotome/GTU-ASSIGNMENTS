#ifndef LIB_HW4_H
#define LIB_HW4_H

#include <iostream>
#include <vector>

namespace GTUSET{

const std::vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class DayofYearSet{
public:
	class DayofYear{
	public:
		friend DayofYearSet;
		DayofYear(int D, int M) { setDate(D, M); } // Constructors of "DayofYear"
		DayofYear(const DayofYear &other) { day = other.day; month = other.month; }
		DayofYear() { }
		void getDate() const;						// Prints day and month
		inline int getDay() const { return day; }
		inline int getMonth() const { return month; }
		bool operator == (const DayofYear& D) { return (D.day == day) && (D.month == month); }	
	private:
		void setDate(int D, int M);
		inline bool isValid(int D, int M) { if ( ((D < 1) || (D > months[M-1])) || ((M < 1) || (M > 12)) ) return false; return true; }
		int day = 0;
		int month = 0;
	};

	DayofYearSet(std::vector<DayofYearSet::DayofYear> vec) { for (int i = 0; i < vec.size(); ++i) 
																add( vec[i].getDay(), vec[i].getMonth() );} 
																// Vector constructor, iterates through elemts and copies the values
	DayofYearSet (const DayofYearSet &S) {	for (int i = 0; i < S.size(); ++i)
												add( S[i].getDay(), S[i].getMonth() );}	// Copy constructor, operates like constructor with vector argument
	DayofYearSet() {}
	void add(int D, int M); 		// Adds new element
	void remove(); 					// Removes the last element
	inline int size() const { return elements; }
	inline int getCapacity() const { return capacity; }
	bool isPresent(const DayofYear& D) const;	// Looks if a day is present in a set
	DayofYear& operator [] (int index) const;
	friend std::ostream & operator << (std::ostream &out, const DayofYearSet &S);	// Prints set elements by overloading
	DayofYearSet operator ! ();							// Operators perform as how PDF asked
	bool operator == (const DayofYearSet& S) const;
	bool operator != (const DayofYearSet& S) const { return !( (*this) == S ); }
	DayofYearSet operator + (const DayofYearSet& S);
	DayofYearSet operator - (const DayofYearSet& S);
	DayofYearSet operator ^ (const DayofYearSet& S);
	static int getTotalDays() { return totaldays; }
	~DayofYearSet();
private:
	DayofYear* days = new DayofYear;
	int capacity = 0;
	decltype(capacity) elements = 0;
	static int totaldays;
};
}

#endif