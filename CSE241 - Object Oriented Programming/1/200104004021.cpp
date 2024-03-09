#include <iostream>       // Peg Solitaire by Tarık Özcaner
#include <vector>         // 2021.10.20
#include <ctime>          // for random number generation
#include <cstdlib>

using namespace std;

enum class types {none = ' ', empty = '.' , peg = 'P'};

void menu();                                          // executes the algorithm by calling necessary functions or simply coordinator
vector<vector<types>> puzzle_creator(const int choice = 6);     
                                                            // loads the vector according to the "choice" or "filename" string
void printer(const vector<vector<types>> puzzle);           // prints the board
void movement(vector<vector<types>> &puzzle, const bool player);  
                                                            // according to the inputs manipulates the "puzzle" vector with the help of
                                                            // "is_legal" function and plays for cpu if asked
bool is_legal(const vector<vector<types>> puzzle, const char column, const char direction, const int row);    
                                                            // checks if the entered move is legal
bool is_finished(const vector<vector<types>> puzzle);       // checks to see if the puzzle is finished
void score(const vector<vector<types>> puzzle);             // counts and prints the number of pegs left


int main(){
    menu();     // calling "menu" to create magic :)
    return 0;
}



void menu(){

  cout << "\n\n\tPeg Solitaire by Tarık Özcaner\n\n";

  int choice, err = 0; bool player;

  do{

    if (err) cout << "\nIncorrect input.\n" << endl; ++err;   // if input for board number is incorrect error message is printed

    cout<<"Please select a shape to start (1 to 6): ";
    cin>>choice;

  }while(choice < 1 || choice > 6);   // Asking for input until eligible one is read

    cout<<"\nDo you want computer to play (0:No 1:Yes): ";
    cin>>player;

  vector<vector<types>> puzzle = puzzle_creator(choice);  // "puzzle" is the vector that contains the information of the game

    do{

    printer(puzzle);
    movement(puzzle, player);
    
  }while(is_finished(puzzle));  // inputs are asked or created (by cpu) untik the puzzle is finished
  
  printer(puzzle);
  score(puzzle);    // The puzzle is finished so the board and the score are printed respectively
}


vector<vector<types>> puzzle_creator(const int choice){   // Here one of the pre-existing board is returned as "puzzle" vector

  vector<vector<types>> puzzle;

  switch (choice) {
  case 1:
    puzzle =                  {{types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none},
                              {types::none,types::peg,types::peg,types::peg,types::peg,types::peg,types::none},
                              {types::peg,types::peg,types::peg,types::none,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::empty,types::peg,types::peg,types::peg},
                              {types::none,types::peg,types::peg,types::peg,types::peg,types::peg,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none}};
    break;
  case 2:
    puzzle =                  {{types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::peg,types::empty,types::peg,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none}};
    break;
  case 3:
    puzzle =                  {{types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::empty,types::peg,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none}};
    break;
  case 4:
    puzzle =                  {{types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::empty,types::peg,types::peg,types::peg},
                              {types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none}};
    break;
  case 5:
    puzzle =                  {{types::none,types::none,types::none,types::none,types::peg,types::none,types::none,types::none,types::none},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::peg,types::peg,types::none,types::none},
                              {types::none,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::none},
                              {types::peg,types::peg,types::peg,types::peg,types::empty,types::peg,types::peg,types::peg,types::peg},
                              {types::none,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::peg,types::none},
                              {types::none,types::none,types::peg,types::peg,types::peg,types::peg,types::peg,types::none,types::none},
                              {types::none,types::none,types::none,types::peg,types::peg,types::peg,types::none,types::none,types::none},
                              {types::none,types::none,types::none,types::none,types::peg,types::none,types::none,types::none,types::none}};
    break;
  case 6:
    puzzle =                  {{types::empty,types::none,types::none,types::none,types::none},
                              {types::peg,types::peg,types::none,types::none,types::none},
                              {types::peg,types::peg,types::peg,types::none,types::none},
                              {types::peg,types::peg,types::peg,types::peg,types::none},
                              {types::peg,types::peg,types::peg,types::peg,types::peg}};
    break;
}
  return puzzle;
}



void printer(const vector<vector<types>> puzzle){
  
  int num = 1;  char chr = 'A';     // To print the board in the 'accepted' fashion

  cout << endl << "   ";

  for (int i = 1; i <= puzzle.size(); ++i)  // First columns are printed
  {
    cout << chr << " ";
    ++chr;
  }
  cout << endl << endl;

  for (int r = 0; r < puzzle.size(); ++r)   // The rest is printed here
  {

    cout << num << "  "; ++num; // row numbers

    for (int c = 0; c < puzzle.size(); ++c)  cout << char(puzzle[r][c]) << " ";  // then the elements

    cout << endl;
  }
  cout << endl;
}



void movement(vector<vector<types>> &puzzle, const bool player){
  

  char column, direction; int row, err=0; // err is for a warning message for invalid inputs 
                                          // the rest contains the information of the peg that is planned to move

  if(player)
  {                           // if computer is going to play the game

    srand(time(NULL));  int ran;       // for random number creation

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

  else    // if user is going to play the game
  {

  do{

    if (err) {cout << endl << "Incorrect input." << endl; printer(puzzle);} ++err;

  cout << endl << "Please select a peg and direction (example:B4-U): "; //example valid inputs are: b4, a3, A3

  cin >> column; cin >> row; cin >> direction; cin >> direction; --row; // row and
  
  if (column >= 65 && column <= 90)  column -=65;                       // column are modified to modify the intended element of the array
  else                               column -=97;

  }while(is_legal(puzzle,column,direction,row));
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
    if (puzzle[row-1][column] != types::peg || puzzle[row-2][column] != types::empty) return 1;   // if there is not a peg-peg-empty combination
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
  
  int pegs = 0;

  for (int r = 0; r < puzzle.size(); ++r)
  {
    for (char c = 0; c < puzzle.size(); ++c)
    {
      if(puzzle[r][c] == types::peg) ++pegs;  // print them pegs
    }
  }
  
  cout << endl << "The puzzle is finished and the score is: " << pegs << endl << endl;
}