#include "lib_hw5.h"		// Implementations of "PegSolitaire"s functions
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

PegSolitaire::PegSolitaire(){ initialize(); }

void PegSolitaire::initialize(){

	board = {{' ',' ','P','P','P',' ',' '},		// initialization
             {' ',' ','P','P','P',' ',' '},
             {'P','P','P','P','P','P','P'},
             {'P','P','P','.','P','P','P'},
             {'P','P','P','P','P','P','P'},
             {' ',' ','P','P','P',' ',' '},
     		 {' ',' ','P','P','P',' ',' '}};
    totalpegs = 32;
}

void PegSolitaire::playUser( string str){
	
   	while( !isLegal( str[1] - 'A', str[3], static_cast<int>(str[0] - '1') ) ){	// If input is valid board will be modified
   		cerr << "\nIncorrect input.\nEnter new move (ex: 2B U): ";
   		getline(cin, str);
   	}

   	movement( str[1] - 'A', str[3], static_cast<int>(str[0] - '1') );
}

void PegSolitaire::playAuto(){

	srand((unsigned) time(0));  int ran, row;	char column, direction;		// For random number creation
	
    vector<char> dir = {'U','D','R','L'};         	// With random indexes from 0 to 3, a random direction is selected
   	
   	do{
    	
    	ran = rand();   row =       ran%board.size();    // Random numbers are selected to randomly decide on a element (hopefully a peg :D)
    	ran = rand();   column =    ran%board[0].size();
    	ran = rand();   direction = dir[ran%4];
	
   	}while( !isLegal( column, direction, row ) );  // If the peg info and direction of generated move is ok to execute, loop is terminated

   	movement( column, direction, row );
}

bool PegSolitaire::endGame() const{

	for (int row = 0; row < board.size(); ++row) // Even if one move is legal then game is not finished
    	for (char column = 0; column < board[0].size(); ++column){

        	if( isLegal( column, 'u', row ) ) return false;	// Every element and direction is checked for peg-peg-empty combination
        	if( isLegal( column, 'd', row ) ) return false;
        	if( isLegal( column, 'l', row ) ) return false;
        	if( isLegal( column, 'r', row ) ) return false;
    	}
    
	return true;
}

void PegSolitaire::print() const{

	cout << "\033[H\033[J";

	cout << "\n   ";

	for (char c = 'A'; c < board[0].size() + 'A'; ++c){  // First columns are printed
 
	 	cout << c << " ";
	}

	cout << "\n\n";

	for (int r = 1; r <= board.size(); ++r){   // The rest is printed here

	 	cout << r << "  ";// row numbers
	 	for (int c = 0; c < board[0].size(); ++c)  cout << board[r-1][c] << " ";  // then the elements
	 	cout << endl;
	}

cout << endl;
}

int PegSolitaire::boardScore() const{

	return totalpegs-1;
}

bool PegSolitaire::isLegal( const char column, const char direction, const int row ) const{

	if (row < 0 || column < 0 || (row >= board.size()) || column >= board.size()) return false; 
                 // if indexes are not in the range of the board then no it is not legal ofc c:
 	if('.' == board[row][column] || ' ' == board[row][column]) return false; 
                 // if element is not a peg then how are we going to move it?
 
 	switch (direction){
   	case 'U': case 'u':
   		if (row < 2) return false;                          // you can't move outside of the board so return false;
   		if (board[row-1][column] != 'P' || board[row-2][column] != '.') return false; // if there is not a peg-peg-empty combination
   	break;
   	case 'D': case 'd':                                 // similar checks for other directions
       	if (row > board.size()-3) return false;
       	if (board[row+1][column] != 'P' || board[row+2][column] != '.') return false;
    	break;
   	case 'L': case 'l':
       	if (column < 2) return false;
       	if (board[row][column-1] != 'P' || board[row][column-2] != '.') return false;
   	break;
    case 'R': case 'r':
   	    if (column > board.size()-3) return false;
       	if (board[row][column+1] != 'P' || board[row][column+2] != '.') return false;
   	break;
   	default:      // if entered direction is not a valid one
       	return false; 
     	break;
	}
	return true;
}

void PegSolitaire::movement( const char column, const char direction, const int row ){

	switch (direction){   // According to direction, modifying is executed with slight differences
	
		case 'U': case 'u':
			board[row][column] = '.'; board[row-1][column] = '.'; board[row-2][column] = 'P';
		break;
	
		case 'D': case 'd':
			board[row][column] = '.'; board[row+1][column] = '.'; board[row+2][column] = 'P';
		break;
	
		case 'L': case 'l':
			board[row][column] = '.'; board[row][column-1] = '.'; board[row][column-2] = 'P';
		break;
	
		case 'R': case 'r':
			board[row][column] = '.'; board[row][column+1] = '.'; board[row][column+2] = 'P';
		break;
	}
	--totalpegs;	// a move is done so 1 peg less is left
}

void PegSolitaire::txtPrinter() const{

	ofstream file;

	file.open("output.txt", ios_base::app);

	file << "\n   ";

	for (char c = 'A'; c < board[0].size() + 'A'; ++c){  // First columns are printed
 
	 	file << c << " ";
	}

	file << "\n\n";

	for (int r = 1; r <= board.size(); ++r){   // The rest is printed here

	 	file << r << "  ";// row numbers
	 	for (int c = 0; c < board[0].size(); ++c)  file << board[r-1][c] << " ";  // then the elements
	 	file << endl;
	}

	file << endl;
	
	file.close();
}
}