#include "lib_hw5.h"	// Main function 5th homework
#include <iostream>		// by Şiyar Tarık Özcaner 16.12.2021
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

int main(int argc, char const *argv[]){
	
	std::cout << "\nGames are initializing...\n";

	std::vector<board_games::BoardGame2D*> V;
	
	board_games::BoardGame2D* ptr;
	board_games::PegSolitaire p1, p2;
	board_games::EightPuzzle e1, e2;
	board_games::Klotski k1, k2;
	
	std::cout << "\nDone!\n";

	ptr = &p1; V.push_back(ptr);
	ptr = &p2; V.push_back(ptr);
	ptr = &e1; V.push_back(ptr);
	ptr = &e2; V.push_back(ptr);
	ptr = &k1; V.push_back(ptr);
	ptr = &k2; V.push_back(ptr);

	std::string input;

	p1.print();
	std::cout << "\nEnter a string to move: ";
	getline(std::cin, input);
	p1.playUser(input);
	p1.print();
	std::this_thread::sleep_for( std::chrono::milliseconds(800) );

	std::cout << ptr;	// testing operator<<
	ptr->playAuto();
	std::this_thread::sleep_for( std::chrono::milliseconds(800) );
	std::cout << ptr;

	//ptr->playUser();	// playUser can be tested with this line
	
	board_games::BoardGame2D::playVector(V);

	p2.txtPrinter();	// boards are printed to output.txt file
	e2.txtPrinter();
	k2.txtPrinter();

	return 0;
}