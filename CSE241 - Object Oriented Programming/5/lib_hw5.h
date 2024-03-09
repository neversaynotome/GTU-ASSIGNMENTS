#include <iostream>			// Header file of 5th homework
#include <string>			// by Şiyar Tarık Özcaner 16.12.2021
#include <vector>
#include <fstream>

namespace board_games{

class BoardGame2D{
public:
	virtual void initialize() = 0;
	virtual void playUser( std::string ) = 0;
	virtual void playUser() final;
	virtual void playAuto() = 0;
	virtual void playAutoAll() final;
	virtual bool endGame () const = 0;
	virtual void print() const = 0;
	virtual int boardScore() const = 0;
	friend std::ostream & operator << (std::ostream&, BoardGame2D*);
	static void playVector( std::vector<BoardGame2D*> );
};



class PegSolitaire : public BoardGame2D{
public:
	PegSolitaire();
	void initialize();
	void playUser( std::string );
	void playAuto();
	bool endGame () const;
	void print() const;
	int boardScore() const;
	void txtPrinter() const;
private:
	bool isLegal( const char, const char, const int ) const;
	void movement( const char, const char, const int );
	std::vector< std::vector<char> > board;
	int totalpegs;
};



class EightPuzzle : public BoardGame2D{
public:
	EightPuzzle();
	void initialize();
	void playUser( std::string );
	void playAuto();
	bool endGame () const;
	void print() const;
	int boardScore() const;
	void movement( const char );
	void txtPrinter() const;
private:
	bool isLegal( const char ) const;
	int zeroPointer() const;
	std::vector< std::vector<int> > board; 
};



class Klotski : public BoardGame2D{
public:
	Klotski();
	void initialize();
	void playUser( std::string );
	void playAuto();
	bool endGame () const;
	void print() const;
	int boardScore() const;
	bool isLegal( const char, const char ) const;
	void movement( const char, const char );
	void txtPrinter() const;
private:
	std::vector< std::vector<char> > board; 
	int piecePointer( const char ) const;
	int numofmoves;
};
}