#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include "Piece.h"
// [Add other #include directives as necessary.]


class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus(Screen&screen, Well&well);

  private:
    Well    m_well;
    Screen  m_screen;
	Piece   m_piece;
    int     m_level;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
