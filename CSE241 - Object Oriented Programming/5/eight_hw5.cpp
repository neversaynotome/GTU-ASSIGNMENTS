#include "lib_hw5.h"		// Implementations of "EightPuzzle"s functions
#include <iostream>			// by Şiyar Tarık Özcaner 16.12.2021
#include <string>
#include <vector>
#include <fstream>
#include <ctime>			// For random number generation
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

namespace board_games{

EightPuzzle::EightPuzzle(){ initialize(); }


void EightPuzzle::initialize(){

	board = {{1,2,3},
			 {4,5,6},
        	 {7,8,0}};

    int shuffle = 0;
    while (shuffle != 2000){								// Board is shuffled randomly for game variety
    	this_thread::sleep_for( chrono::milliseconds(1) );
    	playAuto();
    	++shuffle;
    }
}

void EightPuzzle::playUser( string str ){

	while( !isLegal( str[0] ) ){
   		cerr << "\nIncorrect input.\nEnter new move (ex: U): ";
   		getline(cin, str);
   	}

   	movement( str[0] );
}

void EightPuzzle::playAuto(){

	srand( ( (unsigned) time(0) ) + boardScore() * boardScore() );  

	int ran;	char direction;		// For random number creation
	
    vector<char> dir = {'U','D','R','L'};         	// With random indexes from 0 to 3, a random direction is selected
   	
   	do{
    	
    	ran = rand();   direction = dir[ran%4];

   	}while( !isLegal( direction ) );  // If the info of generated move is ok to execute, loop is terminated

   	movement( direction );
}

bool EightPuzzle::endGame() const{

	for (int i = 0; i < 8; ++i)
		if ( board[i/3][i%3] != i+1 ) return false;
	return true;
}

void EightPuzzle::print() const{

	cout << "\033[H\033[J";

	for (int i = 0; i < 9; ++i){
		if ( i%3 == 0 ) cout << "\n";

		if ( board[i/3][i%3] != 0 ) cout << " " << board[i/3][i%3];
		else		  				cout << "  ";
	}
	cout << endl;
}

int EightPuzzle::boardScore() const{	// See report for information of how score is calculated

	auto point = 0;

	for (int i = 0; i < 9; ++i)
			if ( i == 8 && board[i/3][i%3] == 0 ) ++point;
			else if ( board[i/3][i%3] == i+1 ) ++point;
		
	return 9-point;
}

bool EightPuzzle::isLegal( const char direction ) const{ // Checks if entered move is possible to make
														 // see report for further info
	auto pointer = zeroPointer();

 	switch (direction){

   		case 'U': case 'u':
   			if ( pointer < 3 ) return false;
   		break;
	
   		case 'D': case 'd':                                 // similar checks for other directions
    		if ( pointer > 5 ) return false;
    	break;
	
   		case 'L': case 'l':
    		if ( pointer % 3 == 0 ) return false;
   		break;
	
    	case 'R': case 'r':
    		if ( pointer % 3 == 2 ) return false;
   		break;
	
   		default:      // if entered direction is not a valid one
    	   	return false; 
    	break;
	}
	return true;
}

void EightPuzzle::movement( const char direction ){ // Checks if entered move is possible to make
													// see report for further info
	auto pointer = zeroPointer();

	switch (direction){   // According to direction, modifying is executed with slight differences
	
		case 'U': case 'u':
			board[pointer/3][pointer%3] = board[pointer/3-1][pointer%3];
			board[pointer/3-1][pointer%3] = 0;
		break;
	
		case 'D': case 'd':
			board[pointer/3][pointer%3] = board[pointer/3+1][pointer%3];
			board[pointer/3+1][pointer%3] = 0;
		break;
	
		case 'L': case 'l':
			board[pointer/3][pointer%3] = board[pointer/3][pointer%3-1];
			board[pointer/3][pointer%3-1] = 0;
		break;
	
		case 'R': case 'r':
			board[pointer/3][pointer%3] = board[pointer/3][pointer%3+1];
			board[pointer/3][pointer%3+1] = 0;
		break;
	}
}

int EightPuzzle::zeroPointer() const{

	for (int i = 0; i < 9; ++i)
		if (board[i/3][i%3] == 0) return i;
	return -1;
}

void EightPuzzle::txtPrinter() const{

	ofstream file;

	file.open("output.txt", ios_base::app);

	for (int i = 0; i < 9; ++i){
		if ( i%3 == 0 ) file << "\n";

		if ( board[i/3][i%3] != 0 ) file << " " << board[i/3][i%3];
		else		  				file << "  ";
	}
	file << endl;

	file.close();
}
}