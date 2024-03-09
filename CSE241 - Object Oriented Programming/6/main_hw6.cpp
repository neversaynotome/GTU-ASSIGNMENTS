#include <iostream>			// CSE241 HW6 by Tarık Özcaner
#include <string>			// 01.01.2021
#include <memory>			// All of the implementations are kept in headers to avoid any possible errors
#include <vector>			// sourcing from templates that are compiler related
#include <algorithm>
#include "itr_hw6.h"
#include "const_itr_hw6.h"
#include "vector_hw6.h"
#include "array_hw6.h"
#include "set_hw6.h"		// You are advised to check implementations from "set_hw6.h" header since it has higher function count
							// most of the explanations are provided there
using std::cout;
using std::endl;
using namespace GTU;

void x5(int a){		// An arbitrary function to use with "std::for_each"
    cout << a * 5 << " ";
}

int main(int argc, char const *argv[]){

	cout << "\n\n Testing GTUSet" << endl;	// move semantics, delete iterator test

	GTU::GTUSet <int> set1, set3;

	if ( set3.empty() == true ) cout << "\n\"set3\" contains 3!\n";

	set1.add(3); set1.add(7); set1.add(5);	// "add" function

	GTU::GTUIterator<int> itr;				// range based loop using iterator
	
	cout << "\nElements of \"set1\" are : ";

	for (itr = set1.begin(); itr != set1.end(); itr++)
        cout << *itr << " ";
    cout << endl;

	GTU::GTUSet <int> set2(set1);			// copy constructor

	set2.add(3); set2.add(9); set2.add(4);				// "add(3)" to test duplication avoid system

	cout << "\nElements of \"set2\" are : ";

	for (itr = set2.begin(); itr != set2.end(); itr++)
        cout << *itr << " ";
    cout << endl;

	set3 = set1 ^ set2;						// intersection operation

	cout << "\nElements of \"set3\" are : ";

	for (itr = set3.begin(); itr != set3.end(); itr++)
        cout << *itr << " ";
    cout << endl;

	set3 = set1 + set2;						// union operation

	cout << "\nElements of \"set3\" are : ";

	for (itr = set3.begin(); itr != set3.end(); itr++)
        cout << *itr << " ";
    cout << endl;
    										// "search" is on the go
	if ( set3.search(3) == true ) cout << "\n\"set3\" contains 3!\n";

	set3.delete_member(3);					// deleting 3 from "set3"

	if ( set3.search(3) == false ) cout << "\nNow \"set3\" doesn't contain 3!\n";

	set3.erase( set3.begin() );				// "erase" function

	cout << "\nElements of \"set3\" are : ";

	for (itr = set3.begin(); itr != set3.end(); itr++)
        cout << *itr << " ";
    cout << endl;

	cout << "\n---------------------------\n" << endl;

	cout << "\n Testing GTUVector" << endl;

	GTU::GTUVector <int> vec1;

	if ( vec1.empty() ) cout << "\n\"vec1\" is empty!\n";	// "empty" function

	vec1.add(1); vec1.add(2); vec1.add(3);
	vec1.add(-3); vec1.add(7); vec1.add(0);

	GTU::GTUVector <int> vec2 = vec1;						// assignment function
    
	cout << "\nElements of \"vec2\" are : ";
    for (itr = vec2.begin(); itr != vec2.end(); itr++)
        cout << *itr << " ";
    cout << endl;

    if ( *std::find( vec2.begin(), vec2.begin() + vec2.size(), 3 ) ) cout << "\n\"vec2\" contains 3!\n";

    std::sort( vec2.returnData(), vec2.returnData() + vec2.size() ); // using "std::sort"

    	cout << "\nElements of \"vec2\" after \"std::sort\" are : ";
    for (itr = vec2.begin(); itr != vec2.end(); itr++)
        cout << *itr << " ";
    cout << endl;

    vec2.erase( std::find(vec2.begin(), vec2.end(), 0) );	// "erase" using "std::find"

    cout << "\nElements of \"vec2\" times 5 are : ";		// "std::for_each" tested
    std::for_each (vec2.begin(), vec2.end(), x5 );

	cout << "\n---------------------------\n" << endl;

	cout << "\n Testing GTUArray" << endl;

	GTU::GTUArray <int, 5> arr1, arr2;
	arr1[0] = -2; arr1[1] = 1; arr1[2] = 2; arr1[4] = 4; arr2 = arr1;	// assignment tested
    
    cout << "\nElements of \"arr2\" are : ";
	for (itr = arr2.begin(); itr != arr2.end(); itr++)
        cout << *itr << " ";
    cout << endl;

	GTU::GTUArray <char, 3> arrc;
	arrc[0] = 'H'; arrc[1] = 'I'; arrc[2] = '!';

	GTU::GTUIterator<char> itrc;		// "GTUArray" of chars

	cout << "\nElements of \"arrc\" are : ";
	for (itrc = arrc.begin(); itrc != arrc.end(); itrc++)
        cout << *itrc;
    cout << endl;

/*
	try{
		cout << arr1[33] << endl;		// exception handling can be tested here
	} catch( char* error ){
	}
*/
	return 0;
}