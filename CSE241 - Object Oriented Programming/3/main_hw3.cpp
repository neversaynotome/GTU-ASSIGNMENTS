#include <iostream>       // Peg Solitaire by Tarık Özcaner
#include <vector>         // 2021.11.10
#include <fstream>
#include <string>
#include <ctime>          // For random number generation
#include <cstdlib>

using namespace std;

enum class types {none = ' ', empty = '.' , peg = 'P'};

void Play_PegSolitaire();		// User required only to call this global function to play the game
								// Can be called a 'driver' function for the main class(es)
class PegSolitaire{		// Main class
public:
	class Cell{		// Inner class
	public:
		Cell(types T, int R, int C) : space(T), row(R), column(C) {} // Different types of constructors
		Cell(types T) : space(T) {}
		inline void setType(types T) { space = T;}
		inline const types getType() const { return space; }
	private:
		types space;
		int row, column;
	};
	PegSolitaire(int B) : boardtype(B) {}	// Constructors for the main class
	PegSolitaire(string F) : filename(F) {}	// These are unused since i decided using a 'driver global function' in parallel with
	PegSolitaire() : boardtype(1) {}		// member functions is the way to go since my algorithm is able to play unlimited
											// amount of games simultaneously
	void menu();	// To print the menu
	void setBoard();			// Ask input for the first time and initializes it according to the input with the help of "loader" function
	void getBoard() const;		// Prints the board
	inline int isInitialized() const { return initialized;}
	void setFilename(string name) { filename = name; }
	void loader();				// Modifies the "game" vector by the data in .txt files
	void saver();				// Saves the "game" vector to a .txt file
	bool isLegal(const char column, const char direction, const int row);	// Checks if the entered move is legal
	inline int pegsTaken() const {return emptyCells()-1;}	// dots (empty cells) - 1
	int emptyCells() const;		// dots
	int pegsLeft() const; 		// pegs
	void play(); 				// Move made by computer w/o parameters
	void play(const char column, const char direction, const int row){ move(column, direction, row);}
																		// Makes a move with arguments, manually
	void move(const char column, const char direction, const int row);  // Modifies the "game" vector according to a move
	bool isFinished();		// Checks if the game is finished
	inline void playGame(){while(isFinished()) { getBoard(); play();} getBoard();} 
							// game played automatically until it is finished
	static int getTotalPegs() {return totalpeg;}
	void setTotalPegs() {totalpeg -= pegsLeft();} // When a new board is loaded number of pegs it has is decreased from the total number 
	inline bool moreThan(PegSolitaire other) const{ return pegsLeft() > other.pegsLeft();} // Compares two games
private:
	vector<vector<Cell>> game;
	string filename;
	static int totalpeg;
	int boardtype;
	bool initialized = false; // Helps to know if "setBoard" function will be called
};

int PegSolitaire::totalpeg = 0;

int main(){
	Play_PegSolitaire(); // 'driver' function is called
	return 0;
}

void Play_PegSolitaire(){ // Coordinates everything in such a beautiful manner and creates that most wanted order

	cout << "________________________________________________________________"
		 << "\n\n\t\tPeg Solitaire by Tarık Özcaner\n";

	vector<PegSolitaire> games; int gamecount = 0, input = -1, gamenumber = 0; string file; // Variable names are self-explanatory
																					// extra explanations are provided below
	games.push_back(PegSolitaire()); ++gamecount;	// First game is pushed to "games" vector

	while(input != 0){

		if(!(games[gamenumber].isInitialized())) games[gamenumber].setBoard(); 
											// Initialize the vector by setboard if it is not initialized
		else if(!(games[gamenumber].isFinished())){	// If current game is finished
			cout << "\nGame number " << gamenumber+1 << " is finished." << endl
				 << "\nEnter '1' to switch or create a new game, '0' to exit the program: "; cin >> input;
	
			if (input == 1){
				if (gamecount > 1){	// If there is more games than 1
										// Creating a new game or switching to an existing one
					cout << "\nEnter '1' to create a new game, '2' to switch to an existing game: "; cin >> input;
	
				if (input == 1){ games.push_back(PegSolitaire()); ++gamecount; ++gamenumber;} // New game is pushed to "games" vector
				else{
	
					int togame; bool err = false;
	
					cout << "\nTotal number of games: " << gamecount;
					do{ 					// Asking a game number to switch to
						if (err) cout << "\nIncorrect game number!";
						cout << "\n\nTo which game do you want to switch: "; cin >> togame; err = true;
					}while((togame < 1) || (gamenumber+1 == togame) || (togame > gamecount));
					gamenumber = togame-1;	// If the game number is valid then switching is done
				}
				}
				else{ cout << "\nYou must create another game in order to keep playing.\n";	// There is only one game so
					games.push_back(PegSolitaire()); ++gamecount; ++gamenumber;
				}
			}
		}
		else{		// So game is initialized and is not finished yet then 'normal' operations can start
	
			cout << "\nGame number: " << gamenumber+1 << "\nTotal number of pegs: " << games[gamenumber].getTotalPegs() << endl; 
			games[gamenumber].getBoard();	games[gamenumber].menu();	cin >> input;
						// Function "getBoard" prints the board and function "menu" prints the menu
			switch(input){	// with the help of the function "menu" an input is read
		
				case 1:	// Making a move
					int play, row;	char direction, column;	
					cout << "\nEnter '1' to input a move, '2' for a computer generated move: "; cin >> play;
		
					if (play == 1){
					do{				// Asking for a manual move until a valid one is read
						cout << "\nPlease enter a move: "; cin >> column; cin >> row; cin >> direction; cin >> direction;
						if (column >= 65 && column <= 90)  column -=65;	// Column and row are modified to access the intended element of the array
  						else                               column -=97; --row;
					}while(games[gamenumber].isLegal(column, direction, row)); games[gamenumber].move(column, direction, row);}
					else games[gamenumber].play();							   // function "move" makes the valid move 
					// computer plays w/o arguments
				break;
		
				case 2: // Computer plays until game finishes
					games[gamenumber].playGame();
				break;
		
				case 3: // Creating a new game or switching to an existing one
					if (gamecount > 1){	// Similar code snippet with line 80 "isFinished"
									// Creating a new game or switching to an existing one
						cout << "\nEnter '1' to create a new game, '2' to switch to an existing game: "; cin >> input;
		
					if (input == 1){ games.push_back(PegSolitaire()); ++gamecount; ++gamenumber;}
					else{
		
					int togame; bool err = false;
		
						cout << "\nTotal number of games: " << gamecount;
						do{ 
							if (err) cout << "\nIncorrect game number!";	// Asking a game number to switch to
							cout << "\n\nTo which game do you want to switch: "; cin >> togame; err = true;
						}while((togame < 1) || (gamenumber+1 == togame) || (togame > gamecount));
						gamenumber = togame-1;	// If the game number is valid then switching is done
					}
					}
					else{ cout << "\nYou must create more games in order to be able to switch to other games.\n";
						games.push_back(PegSolitaire()); ++gamecount; ++gamenumber;	// Only one game is available
					}
				break;
		
				case 4:
					cout << "\nTo load a game please enter the file name: "; cin >> file; games[gamenumber].setFilename(file);
					games[gamenumber].setTotalPegs(); games[gamenumber].loader();  
								// Before loading member function "setTotalPegs" decreases total number of pegs since old board is 'deleted'
					cout << "\nGame loaded successfully.\n";
				break;
		
				case 5:	// Saving the game
					games[gamenumber].saver(); cout << "\nGame saved successfully.\n";
				break;
		
				case 6: // Comparing the games
					if (gamecount > 1){	// Similar code snippet with line 80 "isFinished" and "case 3"
		
					int compare; bool err = false;
		
						cout << "\nTotal number of games: " << gamecount;
						do{
							if (err) cout << "\nIncorrect game number!";	// Asking a game number to compare
							cout << "\n\nWhich game do you want to compare with: "; cin >> compare; err = true;
						}while((compare < 1) || (gamenumber+1 == compare) || (compare > gamecount));

						if (games[gamenumber].moreThan(games[compare-1])) cout << "\nCurrent game has more pegs.\n";
						else											  cout << "\nCurrent game has less pegs.\n";
					}
					else cout << "\nYou must create more games in order to be able to make comparison.\n";
					
				break;
		
				case 0:	// Exit
				
				break;
		
				default:
					cout << "\nInvalid input.\n";
				break;
			}
		}
	}
	cout << "\nExitted successfully.\n\n"
		 << "________________________________________________________________\n\n";
}

void PegSolitaire::menu(){	// Prints the menu

	cout << "\n1- Play a move.\n"
		 << "2- Let CPU finish the current game.\n"
		 << "3- Start or switch to another game.\n"
		 << "4- Load another game.\n"
		 << "5- Save the current game.\n"
		 << "6- Compare this game with another one.\n"
		 << "0- Exit the program.\n\n"
		 << "Please choose an action from the menu above: ";
}



void PegSolitaire::setBoard(){ // Initializing the "game" vector

	bool err = false; int load;

	cout << "\nEnter '1' to choose an arbitrary board or '2' to load a board: ";	cin >> load;
					// Load from saved games or load an arbitrary one

	if (load == 2){cout << endl << "To load a game please enter the file name: ";	cin >> filename; loader();}
	else{

		do{
	
  			if (err) cerr << "\nIncorrect input." << endl; err = true;   // if input for arbitrary board number is incorrect error message is printed
	
  			cout << endl << "Please select a shape to start (1 to 6): ";	cin >> boardtype;
	
  		}while(boardtype < 1 || boardtype > 6);

 	 	switch (boardtype) {

			case 1:	filename = "board1.txt"; break;		// Arbitrary ones
			case 2:	filename = "board2.txt"; break;
			case 3:	filename = "board3.txt"; break;
			case 4:	filename = "board4.txt"; break;
			case 5:	filename = "board5.txt"; break;
			case 6:	filename = "board6.txt"; break;
		}
		loader();
	}
	initialized = true;		// Marking that 'this object has a functioning game vector'
}

void PegSolitaire::getBoard() const{ // Prints the board
  
	int num = 1;  char chr = 'A';    // To print the board in the 'accepted' fashion

	cout << endl << "   ";

	for (int i = 1; i <= game[0].size(); ++i){  // First columns are printed
  
	 	cout << chr << " ";
	 	++chr;
	}
	cout << endl << endl;

	for (int r = 0; r < game.size(); ++r){   // The rest is printed here
  

	 	cout << num << "  "; ++num; // Row numbers

	 	for (int c = 0; c < game[0].size(); ++c)  cout << char(game[r][c].getType()) << " ";  // then the elements

	 	cout << endl;
	}
	cout << endl;

	cout << "\n***********************************************"			// After the move up-to-date board info is printed
   		 << "\n** Number of peg(s) the board contains: " 	<< pegsLeft()
   		 << "\n** Number of peg(s) taken from the board: "	<< pegsTaken()
   		 << "\n***********************************************\n";
}



void PegSolitaire::loader(){ // Loads a game from .txt files

	if (filename.size() < 5){cerr << endl << "Error: File name is invalid.\n\n"; exit(1);}						// if .txt is nor existent and "filename" is too short
	if (".txt" != filename.substr(filename.size()-4)){cerr << endl << "Error: File is not found.\n\n"; exit(1);}	// loading is not done

	ifstream file; auto row = 0; string in;

		file.open(filename);

		if(file){

			game.clear();	// Clearing vector before loading the new one from the text

			while(!file.eof()){

				getline(file, in);											// "game" vector is being filled up
			
				game.push_back(vector<Cell>());
	 			for (int column = 0; column < in.size(); ++column)	game[row].push_back(Cell(types(in[column]), row, column));
	 			++row;												// Constructor is used
			}
		}
		else{cerr << endl << "Error: File is not found.\n\n"; exit(1);}

		file.close();

		totalpeg += pegsLeft();	// Total pegs added after loading is done
}

void PegSolitaire::saver(){ // Saves the board to a .txt file

	cout << endl << "To save a game please enter the file name: ";	cin >> filename;

	if (filename.size() < 5){cerr << endl << "Error: File can not be created.\n\n"; exit (1);}		// Same controls as "loader"
	if (".txt" != filename.substr(filename.size()-4)){cerr << endl << "Error: Incorrect file type.\n\n"; exit (1);}

	ofstream file;

		file.open(filename);
	
		for (int row = 0; row < game.size(); ++row){  if(row)	file << endl;
	 	for (int column = 0; column < game[0].size(); ++column) file << char(game[row][column].getType());
		}
		
	file.close();
}


bool PegSolitaire::isLegal(const char column, const char direction, const int row){
                                                    // is there a peg-peg-empty combination in the wanted direction?

 	if (row < 0 || column < 0 || (row >= game.size()) || column >= game.size()) return 1; 
 									// if indexes are not in the range of the board then no it is not legal ofc c:
 	if(types::empty == game[row][column].getType() || types::none == game[row][column].getType()) return 1; 
 									// if element is not a peg then how are we going to move it?
  
 	switch (direction){

 		case 'U': case 'u':
			if (row < 2) return 1;                          // you can't move outside of the board so return 1;
			if (game[row-1][column].getType() != types::peg || game[row-2][column].getType() != types::empty) return 1;	
    	return 0;											// if there is not a peg-peg-empty combination
    	break;

 		case 'D': case 'd':                                 // similar checks for other directions
    		if (row > game.size()-3) return 1;
    		if (game[row+1][column].getType() != types::peg || game[row+2][column].getType() != types::empty) return 1;
    	return 0;
    	break;

		case 'L': case 'l':
    		if (column < 2) return 1;
    		if (game[row][column-1].getType() != types::peg || game[row][column-2].getType() != types::empty) return 1;
    	return 0;
    	break;

		case 'R': case 'r':
    		if (column > game.size()-3) return 1;
    		if (game[row][column+1].getType() != types::peg || game[row][column+2].getType() != types::empty) return 1;
    	return 0;
    	break;

		default:      // if entered direction is not a valid one
    		return 1; 
    	break;
 	}
    return 0;
}



void PegSolitaire::play(){ // Move made by the computer

	srand(time(NULL));  int ran, row;	char column, direction;		// For random number creation
	
   	do{
	
    	vector<char> dir = {'U','D','R','L'};         	// With random indexes from 0 to 3, a random direction is selected
    	
    	ran = rand();   row =       ran%game.size();    // Random numbers are selected to randomly decide on a element (hopefully a peg :D)
    	ran = rand();   column =    ran%game[0].size();
    	ran = rand();   direction = dir[ran%4];
	
   	}while(isLegal(column, direction, row));  // If the peg info and direction of move is ok to execute, loop is terminated

   	move(column, direction, row);
}



void PegSolitaire::move(const char column, const char direction, const int row){ // Makes the move

	cout << "\n*******************************";
   	cout << "\n  The executed move is: " << char(column+65) << row+1 << "-" << char(direction);  
   	cout << " **\n*******************************\n";	   	// The move of computer is printed for user

	switch (direction){   // According to direction, modifying is executed with slight differences
	
		case 'U': case 'u':
		  game[row][column].setType(types::empty); game[row-1][column].setType(types::empty); game[row-2][column].setType(types::peg);
		  break;
	
		case 'D': case 'd':
		  game[row][column].setType(types::empty); game[row+1][column].setType(types::empty); game[row+2][column].setType(types::peg);
		  break;
	
		case 'L': case 'l':
		  game[row][column].setType(types::empty); game[row][column-1].setType(types::empty); game[row][column-2].setType(types::peg);
		  break;
	
		case 'R': case 'r':
		  game[row][column].setType(types::empty); game[row][column+1].setType(types::empty); game[row][column+2].setType(types::peg);
		  break;
		}
	--totalpeg;	// a move is done so 1 peg less is left
}



bool PegSolitaire::isFinished(){ // Is there any peg-peg-empty combination left in any direction?
  
    for (int row = 0; row < game.size(); ++row) // Even if one move is legal then game is not finished
    {
      for (char column = 0; column < game[0].size(); ++column)
      {
        if( !(isLegal(column, 'u', row)) ) return 1;  // Every element and direction is checked for peg-peg-empty combination
        if( !(isLegal(column, 'd', row)) ) return 1;
        if( !(isLegal(column, 'l', row)) ) return 1;
        if( !(isLegal(column, 'r', row)) ) return 1;
      }
    }
  return 0;
}



int PegSolitaire::emptyCells() const{	// Number of empty cells is returned

	auto dots = 0;

 	for (int row = 0; row < game.size(); ++row)
 	for (char column = 0; column < game[0].size(); ++column)
    
		if(game[row][column].getType() == types::empty) ++dots;  // Count them dots
    
  return dots;
}



int PegSolitaire::pegsLeft() const{		// Number of pegs is returned
  
  auto pegs = 0;

  for (int row = 0; row < game.size(); ++row)
 
    for (char column = 0; column < game[0].size(); ++column)
    
      if(game[row][column].getType() == types::peg) ++pegs;  // Count them pegs
    
  return pegs;
}