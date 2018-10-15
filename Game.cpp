#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1)
{
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus(m_screen,m_well);  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
	Piece m_piece;
	m_well.onePiece(m_piece, m_screen);

    for(;;)
    {
        if ( !playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
		for (int i = 1; i <= 10; i++) {
			for (int j = 0; j < 18; j++) {
				m_screen.gotoXY(i, j);
				m_screen.printChar(' ');
				m_well.m_map[i][j] = ' ';
			}
		}
		m_well.increLevel();
		m_well.displayLevel(m_screen);
		m_well.setRowLeft();
		m_well.displayRowLeft(m_screen);
		Piece m_piece;
		m_well.onePiece(m_piece, m_screen);
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
	exit(0);
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus(Screen&m_screen,Well&m_well)
{
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score:     ");
	m_well.initializeScore();
	m_well.displayScore(m_screen);

	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:     ");
	m_well.initializeLevel();
	m_well.displayLevel(m_screen);

	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows left: ");
	m_well.setRowLeft();
	m_well.displayRowLeft(m_screen);
}



bool Game::playOneLevel()
{
	if (m_well.getRowLeft() <= 0) { return true; }
	m_well.gameOver(m_piece, m_screen);
	return (!m_well.getGameOver());
}
