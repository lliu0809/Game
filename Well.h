#ifndef WELL_INCLUDED
#define WELL_INCLUDED
#include "Piece.h"


class Screen;
class Piece;

class Well
{
  public:
	  Well();
      void display(Screen& screen, int x, int y);
	  void display(Piece& piece,Screen& screen);
	  void gameOver(Piece& piece, Screen& screen);
	  void deleteLine(int y,Screen&screen);
	  void deleteFilled(Screen&screen);
	  void clearLastPiece(Screen&screen,Piece& piece);
	  bool isMovePossible(Piece& piece);
	  void drop(Piece &piece, Screen& screen);
	  void landed(Piece&piece, Screen&screen);
	  void specialVapor(Piece& piece, Screen&screen);
	  void specialFoam(Piece& piece, Screen&screen);
	  void foamHelper(Screen&screen, int x, int y,int mx,int my);
	  void displayScore(Screen&screen);
	  void incrementScore(int i);
	  int getScore();
	  void initializeScore();
	  void onePiece(Piece&piece,Screen&screen);
	  int getRowLeft();
	  int getLevel();
	  void initializeLevel();
	  void displayLevel(Screen&screen);
	  void increLevel();
	  void setRowLeft();
	  void displayRowLeft(Screen&screen);
	  bool getGameOver();
	  void initialGameOver();
	  char m_map[12][19];
private:
	
	int m_score;
	int m_level;
	int rowLeft;
	bool m_gameover;
};

#endif // WELL_INCLUDED
