#include <iostream>       // Peg Solitaire by Tarık Özcaner
#include <vector>         // 2021.10.27
#include <fstream>
#include <string>
#include <ctime>          // for random number generation
#include <cstdlib>

using namespace std;

enum class types {none = ' ', empty = '.' , peg = 'P'};

void start();                                          // executes the algorithm by calling necessary functions or simply coordinator
void puzzle_creator(const int choice = 6);     
                                                            // loads the vector according to the "choice" or "filename" string

bool loader(vector<vector<types>> &puzzle, const string filename, bool &player);
															// loads the game if it can
bool saver(const vector<vector<types>> puzzle, const string filename, const bool player);
															// saves the board if it can
void printer(const vector<vector<types>> puzzle);           // prints the board
void input(vector<vector<types>> &puzzle, bool player);		// gets and processes the input
void movement(vector<vector<types>> &puzzle, const bool player, char column = 0, char direction = 0, int row = 0);  
                                                            // according to the parameters manipulates the "puzzle" vector with the help of
                                                            // "is_legal" function and plays for cpu if asked
bool is_legal(const vector<vector<types>> puzzle, const char column, const char direction, const int row);    
                                                            // checks if the entered move is legal
bool is_finished(const vector<vector<types>> puzzle);       // checks to see if the puzzle is finished
void score(const vector<vector<types>> puzzle);             // counts and prints the number of pegs left


int main(){
    start();     // calling "start" to create magic :)
    return 0;
}



void start(){

  cout << "\n\n\tPeg Solitaire by Tarık Özcaner\n\n";

  int choice; bool err = 0, player, load;

  cout << "Enter '0' to choose an arbitrary board or '1' to load a board: ";	// there is no game to save so load from saved games or load an arbitrary one?
  cin >> load;

  if (load) puzzle_creator();	// because of the default argument function is called empty
  else{

  	do{
	
  	  if (err) cerr << "\nIncorrect input.\n" << endl; err = true;   // if input for arbitrary board number is incorrect error message is printed
	
  	  cout << endl << "Please select a shape to start (1 to 5): ";	
  	  cin >> choice;
	
  	}while(choice < 1 || choice > 5);
	
  	puzzle_creator(choice);  // according to the choice
  }
}



bool loader(vector<vector<types>> &puzzle, const string filename, bool &player){

	if (filename.size() < 5){cerr << endl << "File name is invalid.\n"; return 1;}							// if .txt is nor existent and "filename" is too short
	if (".txt" != filename.substr (filename.size()-4)){cerr << endl << "File is not found.\n"; return 1;}	// loading is not done

	ifstream file; auto row = 0; string in;

		file.open(filename);
	
		if(file){

			puzzle.clear();	// clearing vector before loading the new one from the text

			getline(file, in);  if (in[0] == '1')	player = true;
													else			 				player = false;

			while(!file.eof()){

				getline(file, in);											// puzzle is filled up
			
				puzzle.push_back(vector<types>());
	 			for (int c = 0; c < in.size(); ++c) puzzle[row].push_back(types(in[c]));
	 			++row;
			}
		}
		else{
			cerr << endl << "File is not found.\n"; return 1;
		}

		file.close();
		return 0;
}

bool saver(const vector<vector<types>> puzzle, const string filename, const bool player){
	
	if (filename.size() < 5){cerr << endl << "File can not be created.\n"; return 1;}						// same controls as "loader"
	if (".txt" != filename.substr (filename.size()-4)){cerr << endl << "Incorrect file type.\n"; return 1;}

	ofstream file; string out;

		file.open(filename);

		file << player;
	
		for (int row = 0; row < puzzle.size(); ++row){
			file << endl;
	 	for (int column = 0; column < puzzle[0].size(); ++column)  file << char(puzzle[row][column]);

		}
		
	file.close();
	return 0;
}



void puzzle_creator(const int choice){   // Here one of the pre-existing boards is loaded as "puzzle" vector

  vector<vector<types>> puzzle; bool player;

  switch (choice) {

  case 1:
    	loader(puzzle, "board1.txt", player);					// arbitrary ones
    break;
  case 2:
    	loader(puzzle, "board2.txt", player);
    break;
  case 3:
    	loader(puzzle, "board3.txt", player);
    break;
  case 4:
    	loader(puzzle, "board4.txt", player);
    break;
  case 5:
    	loader(puzzle, "board5.txt", player);
    break;
  case 6:
    	string filename;
    	do{
    		cout << endl << "Please enter the name of the file you want to load: ";	cin >> filename;	// asking a name to load
    	}while(loader(puzzle, filename, player));
    break;
}
	if (choice > 0 && choice < 6) {cout << endl << "Do you want computer to play (0:No 1:Yes): "; cin >> player;}	
	input(puzzle, player);
}							// all information needed to start is got and input is called for gameplay



void input(vector<vector<types>> &puzzle, bool player){

	string input, filename;	bool err = 0, command, save = 0;	// "input" stores the input, "filename" stores name of the text file
																	// err is used for exception handling, "command" holds info about load and save commands
	do{															// by the help "save" program is terminted if a game is saved
	
		printer(puzzle);	command = 1;
	
		do{
	
			if (err && command) {cout << endl << "Incorrect input, try again." << endl; printer(puzzle);}
	
			cout << endl << "Please enter a move or a command (just input something invalid for the next cpu move): ";	cin >> input;
																									// example valid inputs are: 
																									// load qwerty,txt, SAVE game.txt, b4-U, a3-u, A3-u
	
			if (input == "LOAD" || input == "load" || input == "Load"){
		
				cin >> filename;
		
				command = loader(puzzle, filename, player);
			}
			else if (input == "SAVE" || input == "save" || input == "Save"){
		
				cin >> filename;
				
				command = saver(puzzle, filename, player);
		
				if (command == 0) {cout << "\nBoard below is saved.\n"; save = true;}
			}
			else if (player == 0){		// so "input" will be processed and passed like it is a game move
					
				err = true;
				if (input[0] >= 65 && input[0] <= 90)	input[0] -=65;              // "input"s elements are modified to access the intended element of the vector
				else                         	     	input[0] -=97;
			}
		}while(is_legal(puzzle, input[0], input[3], input[1]-49) && !player);
											// in this while loop if cpu plays the game then any input other than save and load commands will be an 
		err = false;						// indicator for next move if user is playing then valid inputs like a game move or save or
											// load commands are expected and asked until one of them is gotten
		if (command && !player)	movement(puzzle, false, input[0], input[3], input[1]-49);	// load or save commands are not entered so a legal move will be made
		if (command && player)	{movement(puzzle, true); printer(puzzle);}		// or cpu will make a move
	}while(is_finished(puzzle) && !save);	// if puzzle is finished or game is saved algorithm won't ask for anymore inputs and program will be terminated

	printer(puzzle);	if(!is_finished(puzzle)) score(puzzle);
}



void printer(const vector<vector<types>> puzzle){
  
	int num = 1;  char chr = 'A';     // To print the board in the 'accepted' fashion

	cout << endl << "   ";

	for (int i = 1; i <= puzzle[0].size(); ++i){  // First columns are printed
  
	 	cout << chr << " ";
	 	++chr;
	}
	cout << endl << endl;

	for (int r = 0; r < puzzle.size(); ++r){   // The rest is printed here
  

	 	cout << num << "  "; ++num; // row numbers

	 	for (int c = 0; c < puzzle[0].size(); ++c)  cout << char(puzzle[r][c]) << " ";  // then the elements

	 	cout << endl;
	}
	cout << endl;
}



void movement(vector<vector<types>> &puzzle, const bool player, char column, char direction, int row){

	if(player){                         // if computer is going to play the game
	
    	srand(time(NULL));  int ran;		// for random number creation
	
    	do{
	
    	vector<char> dir = {'u','d','r','l'};         // with random indexes from 0 to 3, a random direction is selected
    	
    	ran = rand();   row =       ran%puzzle.size();     // random numbers are selected to randomly decide on a element (hopefully a peg :D)
    	ran = rand();   column =    ran%puzzle.size();
    	ran = rand();   direction = dir[ran%4];
	
    	}while(is_legal(puzzle,column,direction,row));  // if the peg info and direction of move is ok to execute, loop is terminated
	
    	cout << "\n*******************************";
    	cout << "\n  The executed move is: " << char(column+65) << row+1 << "-" << char(direction-32);  // The move of computer is printed for user
    	cout << " **\n*******************************\n";

	}

		// modifying the vector according to VALID info we got or extracted? maybe :D
	
		switch (direction){   // according to direction, modifying is executed with slight differences
	
		case 'U': case 'u':
		  puzzle[row][column] = types::empty; puzzle[row-1][column] = types::empty; puzzle[row-2][column] = types::peg;
		  break;
	
		case 'D': case 'd':
		  puzzle[row][column] = types::empty; puzzle[row+1][column] = types::empty; puzzle[row+2][column] = types::peg;
		  break;
	
		case 'L': case 'l':
		  puzzle[row][column] = types::empty; puzzle[row][column-1] = types::empty; puzzle[row][column-2] = types::peg;
		  break;
	
		case 'R': case 'r':
		  puzzle[row][column] = types::empty; puzzle[row][column+1] = types::empty; puzzle[row][column+2] = types::peg;
		  break;
		}
	
}



bool is_legal(const vector<vector<types>> puzzle, const char column, const char direction, const int row){
                                                                                          // is there a peg-peg-empty combination in the wanted direction?

  if (row < 0 || column < 0 || row >= puzzle.size() || column >= puzzle.size()) return 1; // if indexes are not in the range of the board then no it is not legal ofc c:
  if(types::empty == puzzle[row][column] || types::none == puzzle[row][column]) return 1; // if element is not a peg then how are we going to move it?
  
  switch (direction){

  case 'U': case 'u':
    if (row < 2) return 1;                                                                      // you can't move outside of the board so return 1;
    if (puzzle[row-1][column] != types::peg || puzzle[row-2][column] != types::empty) return 1;	// if there is not a peg-peg-empty combination
    return 0;
    break;

  case 'D': case 'd':                                                                           // similar checks for other directions
    if (row > puzzle.size()-3) return 1;
    if (puzzle[row+1][column] != types::peg || puzzle[row+2][column] != types::empty) return 1;
    return 0;
    break;

  case 'L': case 'l':
    if (column < 2) return 1;
    if (puzzle[row][column-1] != types::peg || puzzle[row][column-2] != types::empty) return 1;
    return 0;
    break;

  case 'R': case 'r':
    if (column > puzzle.size()-3) return 1;
    if (puzzle[row][column+1] != types::peg || puzzle[row][column+2] != types::empty) return 1;
    return 0;
    break;

  default:      // if entered direction is not a valid one
    return 1; 
    break;
  }
    return 0;
}



bool is_finished(const vector<vector<types>> puzzle){ // is there any peg-peg-empty combination left?
  
    for (int r = 0; r < puzzle.size(); ++r) // even if one move is legal then puzzle is not finished
    {
      for (char c = 0; c < puzzle.size(); ++c)
      {
        if(is_legal(puzzle, c, 'u', r) == 0) return 1;  // every element and direction is checked for peg-peg-empty combination
        if(is_legal(puzzle, c, 'd', r) == 0) return 1;
        if(is_legal(puzzle, c, 'l', r) == 0) return 1;
        if(is_legal(puzzle, c, 'r', r) == 0) return 1;
      }
    }
  
  return 0;
}



void score(const vector<vector<types>> puzzle){  // finally puzzle is finished
  
  auto pegs = 0;

  for (int row = 0; row < puzzle.size(); ++row)
  {
    for (char column = 0; column < puzzle.size(); ++column)
    {
      if(puzzle[row][column] == types::peg) ++pegs;  // print them pegs
    }
  }
  
  cout << endl << "The puzzle is finished and the score is: " << pegs << endl << endl;
}