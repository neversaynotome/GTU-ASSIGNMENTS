#include "lib_hw4.h"
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace GTUSET;

void testIt();

int main( int argc, char const *argv[] ){

	testIt();
	return 0;
}

void testIt(){

	DayofYearSet::DayofYear d1(1,5), d2(2,11), d3(10,5);	// Creating a vector to call the constructor that takes a vector
	std::vector<DayofYearSet::DayofYear> V = {d1, d2, d3};
	
	DayofYearSet s1, s2, s3(V), s4;	// "s3" is that vector

	s1.add(3,3);	// "add" function on the go
	s1.add(4,4);
	s1.add(5,5);

	s2.add(5,5);
	s2.add(6,6);
	s2.add(7,7);
	s2.add(7,7);	// Duplication is not allowed
	s2.add(7,22);	// Invalid input is detected

	s4.add(5,5);

	if ( (!(s1 + s2) == (!s1 ^ !s2)) ) std::cout << "\nDe Morgan law holds for s1 and s2.\n";
	
	std::cout << "\nNumber of days alive: " << s2.getTotalDays() << std::endl;


	std::cout << "\nUnion of s1 and s2:\n" << s1 + s2;
	std::cout << "\ns1's difference from s2:\n" << s1 - s2;

	if ( (s1 ^ s2) == s4 ) std::cout << "\nUnion of s1 and s2 is equal to s4.\n";
	
	std::cout << "\nComplement of s1 has " << (!s1).size() << " elements.\n";
	//std::cout << "\nElements of s1:\n"<< (!s1);	// You can print elements of "!s1" here, it is commented since it has a lot of elements


	s3[2].getDate();

	s3.remove();

	std::cout << "\ns3 without the last element:\n"<< s3;
}