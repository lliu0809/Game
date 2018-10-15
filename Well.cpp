#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <cmath>


Well::Well() {
	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < 19; j++) {
			m_map[i][j] = ' ';
		}
	}
}
void Well::display(Screen& screen, int x, int y)
{

	///left bound of the well
	for (int i = y; i <=18+y; i++) {
		screen.gotoXY(x, i);
		screen.printChar('@');
		m_map[x][i] = '@';
	}
	///bottom of the well
	for (int j = x; j <=10+x; j++) {
		screen.gotoXY(j, 18+y);
		screen.printChar('@');
		m_map[j][18 + y] = '@';
	}
	///right bound of the well
	for (int k = y; k <=18+y; k++) {
		screen.gotoXY(11+x, k);
		screen.printChar('@');
		m_map[11 + x][k] = '@';
	}
}


void Well::gameOver(Piece& piece, Screen& screen) {
	int mx = piece.returnX();
	int my = piece.returnY();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.m_piece[i][j] == '#'){
				if (m_map[mx + i][my + j] == '$'|| m_map[mx + i][my + j] == '*') {
					m_gameover = true;
					return;
				}
				else {}
			}
			else {}
		}
	}
	m_gameover = false;
}
void Well::display(Piece& piece, Screen& screen) {
	int mx = piece.returnX();
	int my = piece.returnY();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (piece.m_piece[i][j] == ' ') {
				}
				else {
					screen.gotoXY(mx + i, my + j);
					screen.printChar('#');
					screen.gotoXY(12, 19);
				}
			}
		}
		screen.refresh();
}

void Well::deleteLine(int y,Screen&screen) {
	for (int j = y; j > 0; j--) {
		for (int i = 1; i < 11; i++) {
			char temp = m_map[i][j - 1];
			screen.gotoXY(i, j);
			screen.printChar(temp);
			screen.gotoXY(12, 19);
			m_map[i][j] = m_map[i][j - 1];
		}
	}
	if (rowLeft > 0) {
		rowLeft--;
		displayRowLeft(screen);
	}
}

void Well::clearLastPiece(Screen&screen,Piece&piece) {
	int mx = piece.returnX();
	int my = piece.returnY();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.m_piece[i][j] == '#') {
				screen.gotoXY(i+mx,j+my);
				screen.printChar(' ');
				screen.gotoXY(12, 19);
			}
		}
	}
}

void Well::deleteFilled(Screen&screen) {
	int countDeleted = 0;
	for (int i = 0; i < 18; i++) {
		int count = 0;
		for (int j = 1; j < 11; j++) {
			if (m_map[j][i] == ' ') { break; }
			else {
				count++;
			}
		}
		if (count == 10) {
			deleteLine(i,screen);
			countDeleted++;
		}
	}
	switch (countDeleted) {
	case 1:
		incrementScore(100);
		displayScore(screen);
		break;
	case 2:
		incrementScore(200);
		displayScore(screen);
		break;
	case 3:
		incrementScore(400);
		displayScore(screen);
		break;
	case 4:
		incrementScore(800);
		displayScore(screen);
		break;
	case 5:
		incrementScore(1600);
		displayScore(screen);
		break;
	}

}

bool Well::isMovePossible(Piece& piece) {
	int mx = piece.returnX();
	int my = piece.returnY();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.m_piece[i][j] == '#') {
				if (i + mx <= 0 || i + mx >= 11 || j + my < 0 || j + my >= 18) { return false; }
				if (m_map[i + mx][j + my] != ' ') { return false; }
			}
		}
	}
	return true;
}
void Well::drop(Piece& piece, Screen& screen) {
	while (true) {
		display(piece, screen);    ///display the piece first
		screen.gotoXY(12, 18);		
		Timer timer;
		timer.start();          ///start the timer
		while (timer.elapsed() < fmax(1000 - (100 * (m_level - 1)), 100)) {
			char mChar;
			if (getCharIfAny(mChar)) {
				if (mChar == 'q') {
					screen.gotoXY(0, 20);
					screen.printStringClearLine("Game Over!  Press the Enter key to exit!");   // overwrites previous text
					exit(0);
					waitForEnter();
				}
				if (mChar == ' ') {    ///land to the bottom
					while (isMovePossible(piece)) {
						display(piece, screen);
						screen.gotoXY(12, 18);
						Piece oldPiece = piece;
						piece.move(ARROW_DOWN);
						if (isMovePossible(piece)) {
							clearLastPiece(screen, oldPiece);
							screen.gotoXY(12, 18);
						}
						else {
							piece = oldPiece;
							if (piece.returnType() == PIECE_VAPOR) {
								specialVapor(piece, screen);
								return;
							}
							else if (piece.returnType() == PIECE_FOAM) {
								specialFoam(piece, screen);
								deleteFilled(screen);
								return;
							}
							landed(piece, screen);
							deleteFilled(screen);
							return;
						}
					}
				}
				else {
					Piece pieceNotChange = piece;
					if (mChar == ARROW_DOWN || mChar == ARROW_LEFT || mChar == ARROW_RIGHT || mChar == ARROW_UP) {
						piece.move(mChar);
						if (isMovePossible(piece)) {
							clearLastPiece(screen, pieceNotChange);
							display(piece, screen);
							screen.gotoXY(12, 18);
						}
						else {
							piece = pieceNotChange;
						}
					}
				}
			}
		}
		Piece oldPiece = piece;
		piece.move(ARROW_DOWN);
		if (isMovePossible(piece)) {
			clearLastPiece(screen, oldPiece);
			screen.gotoXY(12, 18);
		}
		else {
			piece = oldPiece;
			if (piece.returnType() == PIECE_VAPOR) {
				specialVapor(piece, screen);
				return;
			}
			else if (piece.returnType() == PIECE_FOAM) {
				specialFoam(piece, screen);
				deleteFilled(screen);
				return;
			}
			landed(piece, screen);
			deleteFilled(screen);
			break;
		}
	}
}

void Well::landed(Piece&piece, Screen&screen) {     ///change the piece to $ signs
	int mx = piece.returnX();
	int my = piece.returnY();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.m_piece[i][j] == '#') {
				screen.gotoXY(mx + i, my + j);
				screen.printChar('$');
				m_map[mx + i][my + j] = '$';
			}
		}
	}
}

void Well:: specialVapor(Piece& piece, Screen&screen) {
	int mx = piece.returnX();
	int my = piece.returnY();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.m_piece[i][j] == '#') {
				if (my+j - 2 >= 0) {
					screen.gotoXY(mx+i, my+j - 2);
					screen.printChar(' ');
					m_map[mx+i][my+j - 2] = ' ';
				}
				if (my+j - 1 >= 0) {
					screen.gotoXY(mx+i, my+j - 1);
					screen.printChar(' ');
					m_map[mx+i][my+j - 1] = ' ';
				}
				screen.gotoXY(mx+i, my+j);
				screen.printChar(' ');
				m_map[mx+i][my+j] = ' ';

				if (my+j + 1 <= 17) {
					screen.gotoXY(mx+i, my+j + 1);
					screen.printChar(' ');
					m_map[mx+i][my+j + 1] = ' ';
				}
				if (my+j + 2 <= 17) {
					screen.gotoXY(mx+i, my+j + 2);
					screen.printChar(' ');
					m_map[mx+i][my+j + 2] = ' ';
				}
			}
		}
	}
}

void Well::foamHelper(Screen&screen, int x,int y,int mx,int my) {
	if (m_map[x][y + 1] == ' '&&x <= mx + 2 && x >= mx - 2 && y+1 >= my - 2 && y+1 <= my + 2) {
		screen.gotoXY(x, y + 1);
		screen.printChar('*');
		m_map[x][y + 1] = '*';
		foamHelper(screen, x, y + 1, mx, my);
	}
	if (m_map[x][y - 1] == ' '&&x <= mx + 2 && x >= mx - 2 && y-1 >= my - 2 && y-1 <= my + 2) {
		screen.gotoXY(x, y - 1);
		screen.printChar('*');
		m_map[x][y - 1] = '*';
		foamHelper(screen, x, y - 1, mx, my);
	}
	if (m_map[x-1][y] == ' '&&x-1 <= mx + 2 && x-1 >= mx - 2 && y >= my - 2 && y <= my + 2) {
		screen.gotoXY(x-1, y);
		screen.printChar('*');
		m_map[x-1][y] = '*';
		foamHelper(screen, x - 1, y, mx, my);
	}
	if (m_map[x+1][y] == ' '&&x+1 <= mx + 2 && x+1 >= mx - 2 && y >= my - 2 && y <= my + 2) {
		screen.gotoXY(x+1, y);
		screen.printChar('*');
		m_map[x+1][y] = '*';
		foamHelper(screen, x + 1, y, mx, my);
	}
	return;
}
void Well::specialFoam(Piece& piece, Screen&screen) {
	int mx = piece.returnX();
	int my = piece.returnY();
	int foamX = mx + 1;			///the position of the foam block
	int foamY = my + 1;
	screen.gotoXY(foamX, foamY);
	screen.printChar('*');
	m_map[foamX][foamY] = '*';
	foamHelper(screen, foamX, foamY, foamX, foamY);
}

void Well::displayScore(Screen&screen) {
	if (m_score == 0) {
		screen.gotoXY(33, 8);
		screen.printChar('0');
	}
	if (m_score >= 100 && m_score < 1000) {
		screen.gotoXY(31, 8);
		screen.printStringClearLine(std::to_string(m_score));
	}
	if (m_score >= 1000 && m_score < 10000) {
		screen.gotoXY(30, 8);
		screen.printStringClearLine(std::to_string(m_score));
	}
	if (m_score >= 10000 && m_score < 100000) {
		screen.gotoXY(29, 8);
		screen.printStringClearLine(std::to_string(m_score));
	}
	if (m_score >= 100000 && m_score < 1000000) {
		screen.gotoXY(28, 8);
		screen.printStringClearLine(std::to_string(m_score));
	}
	if (m_score >= 1000000 && m_score < 10000000) {
		screen.gotoXY(27, 8);
		screen.printStringClearLine(std::to_string(m_score));
	}
}
void Well::incrementScore(int i) {
	m_score = m_score + i;
}
int Well::getScore() { return m_score; }

void Well::initializeScore() { m_score = 0; }




void Well::onePiece(Piece&piece, Screen&screen) {       ///piece is the piece to drop, newpiece is the next piece
		Piece newpiece;
		screen.gotoXY(16, 3);
		screen.printString("Next piece:");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
					screen.gotoXY(16 + i, 4 + j);
					screen.printChar(' ');
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (newpiece.m_piece[i][j] == '#') {
					screen.gotoXY(16 + i, 4 + j);
					screen.printChar('#');
				}
			}
		}
		gameOver(piece, screen);
		if (m_gameover) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (piece.m_piece[i][j] == '#') {
						screen.gotoXY(piece.returnX() + i, piece.returnY() + j);
						screen.printChar('#');
					}
				}
			}
			return;
		}
		else{
			drop(piece, screen);
			if (rowLeft <= 0) { 
				return; 
			}
			onePiece(newpiece, screen);
		}
}

int Well::getRowLeft() { return rowLeft; };
int Well::getLevel() { return m_level; }
void Well::initializeLevel() { m_level = 1; }

void Well::displayLevel(Screen&screen) {
		if (m_level >= 1 && m_level < 10) {
			screen.gotoXY(33, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
		if (m_level >= 10 && m_level < 100) {
			screen.gotoXY(32, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
		if (m_level >= 100 && m_level < 1000) {
			screen.gotoXY(31, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
		if (m_level >= 1000 && m_level < 10000) {
			screen.gotoXY(30, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
		if (m_level >= 10000 && m_level < 100000) {
			screen.gotoXY(29, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
		if (m_level >= 100000 && m_level < 1000000) {
			screen.gotoXY(28, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
		if (m_level >= 1000000 && m_level < 10000000) {
			screen.gotoXY(27, 10);
			screen.printStringClearLine(std::to_string(m_level));
		}
}
void Well::increLevel() { m_level++; }

void Well::setRowLeft() {
	rowLeft = 5 * m_level;
}
void Well::displayRowLeft(Screen&screen) {
	if (rowLeft >= 0 && rowLeft < 10) {
		for (int i = 27; i < 33; i++) {
			screen.gotoXY(i, 9);
			screen.printChar(' ');
		}
		screen.gotoXY(33, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}
	if (rowLeft >= 10 && rowLeft < 100) {
		for (int i = 27; i < 32; i++) {
			screen.gotoXY(i, 9);
			screen.printChar(' ');
		}
		screen.gotoXY(32, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}

	if (rowLeft >= 100 && rowLeft < 1000) {
		for (int i = 27; i < 31; i++) {
			screen.gotoXY(i, 9);
			screen.printChar(' ');
		}
		screen.gotoXY(31, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}
	if (rowLeft >= 1000 && rowLeft < 10000) {
		for (int i = 27; i < 30; i++) {
			screen.gotoXY(i, 9);
			screen.printChar(' ');
		}
		screen.gotoXY(30, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}
	if (rowLeft >= 10000 && rowLeft < 100000) {
		for (int i = 27; i < 29; i++) {
			screen.gotoXY(i, 9);
			screen.printChar(' ');
		}
		screen.gotoXY(29, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}
	if (rowLeft >= 100000 && rowLeft < 1000000) {
		for (int i = 27; i < 28; i++) {
			screen.gotoXY(i, 9);
			screen.printChar(' ');
		}
		screen.gotoXY(28, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}
	if (rowLeft >= 1000000 && rowLeft < 10000000) {
		screen.gotoXY(27, 9);
		screen.printStringClearLine(std::to_string(rowLeft));
	}
}

bool Well::getGameOver() {
	return m_gameover;
}

void Well::initialGameOver() {
	m_gameover = false;
}