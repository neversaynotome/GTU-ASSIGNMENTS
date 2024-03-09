#include "lib_hw5.h"		// Implementations of "Klotski"s functions
#include <iostream>			// by Şiyar Tarık Özcaner 16.12.2021
#include <string>
#include <vector>
#include <fstream>
#include <ctime>          // For random number generation
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

namespace board_games{

Klotski::Klotski(){ initialize(); }

void Klotski::initialize(){

	board = {{'U','X','X','I'},
			 {'U','X','X','I'},
			 {'O','+','+','*'},
			 {'O','2','3','*'},
			 {'1','.','.','4'}};
	numofmoves = 0;
}

void Klotski::playUser( string str ){
	
   	while( !isLegal( str[0], str[2] ) ){
   		cerr << "\nIncorrect input.\nEnter new move (ex: X U): ";
   		getline(cin, str);
   	}

   	movement( str[0], str[2] );
}

void Klotski::playAuto(){

	srand( ( (unsigned) time(0) ) + numofmoves );  int ran;	char piece, direction;		// For random number creation
	
    vector<char> dir = {'U','D','R','L'};         	// With random indexes from 0 to 3, a random direction is selected
    vector<char> pieces = {'X','U','O','I','*','+','1','2','3','4'};

   	do{
    	
    	ran = rand();   direction = dir[ran%4];
    	ran = rand();   piece = pieces[ran%10];

   	}while( !isLegal( piece, direction ) );  // If info of generated move is ok to execute, loop is terminated

   	movement( piece, direction );
}

bool Klotski::endGame () const{

	if ( piecePointer( 'X' ) == 13 )
		return true;
	return false;
}

int Klotski::boardScore() const{

	if ( numofmoves < 81 )
	cout << "\nIt is impossible for game to be finished yet!\n";
	else return numofmoves - 81;
	return -1;
}


void Klotski::print() const{

	cout << "\033[H\033[J";

	for (int i = 0; i < 20; ++i){
		if (i%4 == 0) cout << "\n";
		cout << " " << board[i/4][i%4];
	}
	cout << endl;
}

bool Klotski::isLegal( const char piece, const char direction ) const{	// Checks if entered move is possible to make
																		// see report for further info
	if ( !( piece == '1' || piece == '2' || piece == '3' || piece == '4' || piece == 'X'
		 || piece == 'U' || piece == 'O' || piece == 'I' || piece == '+' || piece == '*' ) ) return false;
																		// Suitable piece code should be entered
	auto pointer = piecePointer( piece );

	switch (direction){

   		case 'U': case 'u':

   			if ( pointer < 4 ) return false;				// Is space available for a piece to move?

   			switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					if ( board[pointer/4-1][pointer%4] != '.' ) return false;
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					if ( board[pointer/4-1][pointer%4] != '.' ) return false;
   				break;

   				case '+':
   					if ( board[pointer/4-1][pointer%4] != '.' || board[pointer/4-1][pointer%4+1] != '.' ) return false;
   				break;

   				case 'X':
   					if ( board[pointer/4-1][pointer%4] != '.' || board[pointer/4-1][pointer%4+1] != '.' ) return false;
   				break;
   			}
   		break;
	
   		case 'D': case 'd':                                 // similar checks for other directions

  			if ( pointer > 15 ) return false;

    		switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					if ( board[pointer/4+1][pointer%4] != '.' ) return false;
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					if ( pointer > 11 ) return false;
   					if ( board[pointer/4+2][pointer%4] != '.' ) return false;
   				break;

   				case '+':
   					if ( board[pointer/4+1][pointer%4] != '.' || board[pointer/4+1][pointer%4+1] != '.' ) return false;
   				break;

   				case 'X':
   					if ( pointer > 11 ) return false;
   					if ( board[pointer/4+2][pointer%4] != '.' || board[pointer/4+2][pointer%4+1] != '.' ) return false;
   				break;
   			}
    	break;
	
   		case 'L': case 'l':

   			if ( pointer%4 == 0 ) return false;

   			switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					if ( board[pointer/4][pointer%4-1] != '.' ) return false;
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					if ( board[pointer/4][pointer%4-1] != '.' || board[pointer/4+1][pointer%4-1] != '.' ) return false;
   				break;

   				case '+':
   					if ( board[pointer/4][pointer%4-1] != '.' ) return false;
   				break;

   				case 'X':
   					if ( board[pointer/4][pointer%4-1] != '.' || board[pointer/4+1][pointer%4-1] != '.' ) return false;
   				break;
   			}
   		break;
	
    	case 'R': case 'r':

  	   		if ( pointer%4 == 3 ) return false; 	

  	   		switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					if ( board[pointer/4][pointer%4+1] != '.' ) return false;
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					if ( board[pointer/4][pointer%4+1] != '.' || board[pointer/4+1][pointer%4+1] != '.' ) return false;
   				break;

   				case '+':
		  	   		if ( pointer%4 == 2 ) return false;
   					if ( board[pointer/4][pointer%4+2] != '.' ) return false;
   				break;

   				case 'X':
		  	   		if ( pointer%4 == 2 ) return false;
   					if ( board[pointer/4][pointer%4+2] != '.' || board[pointer/4+1][pointer%4+2] != '.' ) return false;
   				break;
   			}
   		break;
	
   		default:      // if entered direction is not a valid one
    	   	return false; 
    	break;
	}
	return true;
}

void Klotski::movement( const char piece, const char direction ){ // Checks if entered move is possible to make
																  // see report for further info
	auto pointer = piecePointer( piece ); 	++numofmoves;

	switch (direction){

   		case 'U': case 'u':

   			switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					board[pointer/4-1][pointer%4] = piece;		board[pointer/4][pointer%4] = '.';
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					board[pointer/4-1][pointer%4] = piece;		board[pointer/4+1][pointer%4] = '.';
   				break;

   				case '+':
   					board[pointer/4-1][pointer%4] = piece;		board[pointer/4][pointer%4] = '.';
   					board[pointer/4-1][pointer%4+1] = piece;	board[pointer/4][pointer%4+1] = '.';
   				break;

   				case 'X':
   					board[pointer/4-1][pointer%4] = piece;		board[pointer/4+1][pointer%4] = '.';
   					board[pointer/4-1][pointer%4+1] = piece;	board[pointer/4+1][pointer%4+1] = '.';
   				break;
   			}
   		break;
	
   		case 'D': case 'd':                                 // similar operations for other directions

  			switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					board[pointer/4+1][pointer%4] = piece;		board[pointer/4][pointer%4] = '.';
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					board[pointer/4+2][pointer%4] = piece;		board[pointer/4][pointer%4] = '.';
   				break;

   				case '+':
   					board[pointer/4+1][pointer%4] = piece;		board[pointer/4][pointer%4] = '.';
   					board[pointer/4+1][pointer%4+1] = piece;	board[pointer/4][pointer%4+1] = '.';
   				break;

   				case 'X':
   					board[pointer/4+2][pointer%4] = piece;		board[pointer/4][pointer%4] = '.';
   					board[pointer/4+2][pointer%4+1] = piece;	board[pointer/4][pointer%4+1] = '.';
   				break;
   			}
    	break;
	
   		case 'L': case 'l':

   			switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					board[pointer/4][pointer%4-1] = piece;		board[pointer/4][pointer%4] = '.';
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					board[pointer/4][pointer%4-1] = piece;		board[pointer/4][pointer%4] = '.';
   					board[pointer/4+1][pointer%4-1] = piece;	board[pointer/4+1][pointer%4] = '.';
   				break;

   				case '+':
   					board[pointer/4][pointer%4-1] = piece;		board[pointer/4][pointer%4+1] = '.';
   				break;

   				case 'X':
   					board[pointer/4][pointer%4-1] = piece;		board[pointer/4][pointer%4+1] = '.';
   					board[pointer/4+1][pointer%4-1] = piece;	board[pointer/4+1][pointer%4+1] = '.';
   				break;
   			}
   		break;
	
    	case 'R': case 'r':

  	   		switch ( piece ){
   				case '1': case '2': case '3': case '4':
   					board[pointer/4][pointer%4+1] = piece;		board[pointer/4][pointer%4] = '.';
   				break;

   				case 'U': case 'O': case 'I': case '*':
   					board[pointer/4][pointer%4+1] = piece;		board[pointer/4][pointer%4] = '.';
   					board[pointer/4+1][pointer%4+1] = piece;	board[pointer/4+1][pointer%4] = '.';
   				break;

   				case '+':
   					board[pointer/4][pointer%4+2] = piece;		board[pointer/4][pointer%4] = '.';
   				break;

   				case 'X':
   					board[pointer/4][pointer%4+2] = piece;		board[pointer/4][pointer%4] = '.';
   					board[pointer/4+1][pointer%4+2] = piece;	board[pointer/4+1][pointer%4] = '.';
   				break;
   			}
   		break;
	}
}

int Klotski::piecePointer( const char piece ) const{

	for (int i = 0; i < 20; ++i)
		if (board[i/4][i%4] == piece) return i;
	return -1;
}

void Klotski::txtPrinter() const{

	ofstream file;

	file.open("output.txt", ios_base::app);

	for (int i = 0; i < 20; ++i){
		if (i%4 == 0) file << "\n";
		file << " " << board[i/4][i%4];
	}
	file << endl;

	file.close();
}
}