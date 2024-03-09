#include "lib_hw5.h"			// Implementations of base class "BoardGame2D"s functions
#include <iostream>				// by Şiyar Tarık Özcaner 16.12.2021
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

namespace board_games{

void BoardGame2D::playUser(){

	string str;
	print();

	while( !endGame() ){
		cout << "Enter your move: ";
		getline(cin, str);
		playUser(str);
		print();
	}
}

void BoardGame2D::playAutoAll(){

	print();	int c = 0;
	
	while( !endGame() && c < 1000000 ){		// If "playAuto" fails to solve the puzzle after a million moves loop is terminated
		++c;
		playAuto();
		print();
	}
	cout << "\nThe game is finished (hopefully)!\nGame score is: "
		 << boardScore();
   	this_thread::sleep_for( chrono::milliseconds(4500) );
}

void BoardGame2D::playVector( std::vector<BoardGame2D*> V ){

	for (int i = 0; i < 6; ++i)
		V[i]->playAutoAll();
}

std::ostream & operator << (std::ostream& out, BoardGame2D* P){

	P->print();
	return out;
}
}