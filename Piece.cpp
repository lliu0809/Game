#include "Piece.h"
#include "UserInterface.h"


//default constructor
Piece::Piece() {
	m_ori = 0;
	m_x = 3+1;
	m_y = 0;
	m_type = chooseRandomPieceType();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_piece[i][j] = ' ';
		}
	}
	switch (m_type) {
	case (PIECE_I):
		m_piece[0][1] = '#';
		m_piece[1][1] = '#';
		m_piece[2][1] = '#';
		m_piece[3][1] = '#';
		break;
	case (PIECE_L):
		m_piece[0][1] = '#';
		m_piece[1][1] = '#';
		m_piece[2][1] = '#';
		m_piece[0][2] = '#';
		break;
	case(PIECE_J):
		m_piece[3][2] = '#';
		m_piece[1][1] = '#';
		m_piece[2][1] = '#';
		m_piece[3][1] = '#';
		break;
	case(PIECE_T):
		m_piece[0][1] = '#';
		m_piece[1][1] = '#';
		m_piece[2][1] = '#';
		m_piece[1][0] = '#';
		break;
	case(PIECE_O) :
		m_piece[0][1] = '#';
		m_piece[0][0] = '#';
		m_piece[1][1] = '#';
		m_piece[1][0] = '#';
		break;
	case(PIECE_S):
		m_piece[2][1] = '#';
		m_piece[1][1] = '#';
		m_piece[1][2] = '#';
		m_piece[0][2] = '#';
		break;
	case(PIECE_Z):
		m_piece[0][1] = '#';
		m_piece[1][1] = '#';
		m_piece[1][2] = '#';
		m_piece[2][2] = '#';
		break;
	case(PIECE_VAPOR):
		m_piece[2][0] = '#';
		m_piece[1][0] = '#';
		break;
	case(PIECE_FOAM):
		m_piece[1][1] = '#';
		break;
	case(PIECE_CRAZY):
		m_piece[0][0] = '#';
		m_piece[1][1] = '#';
		m_piece[2][1] = '#';
		m_piece[3][0] = '#';
		break;
	}
}   



//move to the next orientation
void Piece::rotate() {
	PieceType mType = m_type;
	int mOri = m_ori % 4;
	switch (mType) {
	case(PIECE_I):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[3][1] = '#';
			break;
		case 1:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[1][3] = '#';
			break;
		case 2:
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[3][1] = '#';
			break;
		case 3:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[1][3] = '#';
			break;
		}
		break;
	case(PIECE_L):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[0][2] = '#';
			break;
		case 1:
			m_piece[1][0] = '#';
			m_piece[2][1] = '#';
			m_piece[2][0] = '#';
			m_piece[2][2] = '#';
			break;
		case 2:
			m_piece[0][2] = '#';
			m_piece[1][2] = '#';
			m_piece[2][1] = '#';
			m_piece[2][2] = '#';
			break;
		case 3:
			m_piece[1][3] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[2][3] = '#';
			break;
		}
		break;
	case(PIECE_J):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[3][2] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[3][1] = '#';
			break;
		case 1:
			m_piece[2][1] = '#';
			m_piece[2][2] = '#';
			m_piece[1][3] = '#';
			m_piece[2][3] = '#';
			break;
		case 2:
			m_piece[1][2] = '#';
			m_piece[2][2] = '#';
			m_piece[3][2] = '#';
			m_piece[1][1] = '#';
			break;
		case 3:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[2][0] = '#';
			break;
		}
		break;
	case(PIECE_T):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[1][0] = '#';
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			break;
		case 1:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[1][2] = '#';
			break;
		case 2:
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[1][2] = '#';
			break;
		case 3:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[0][1] = '#';
			break;
		}
		break;
	case(PIECE_O):
		break;
	case(PIECE_S):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[2][1] = '#';
			m_piece[1][1] = '#';
			m_piece[0][2] = '#';
			m_piece[1][2] = '#';
			break;
		case 1:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[2][2] = '#';
			break;
		case 2:
			m_piece[2][1] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[0][2] = '#';
			break;
		case 3:
			m_piece[1][0] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[2][2] = '#';
			break;
		}
		break;
	case(PIECE_Z):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[2][2] = '#';
			break;
		case 1:
			m_piece[2][0] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[1][2] = '#';
			break;
		case 2:
			m_piece[0][1] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[2][2] = '#';
			break;
		case 3:
			m_piece[2][0] = '#';
			m_piece[1][1] = '#';
			m_piece[2][1] = '#';
			m_piece[1][2] = '#';
			break;
		}
		break;
	case(PIECE_VAPOR):
		break;
	case(PIECE_FOAM):
		break;
	case(PIECE_CRAZY):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m_piece[i][j] = ' ';
			}
		}
		switch (mOri) {
		case 0:
			m_piece[0][0] = '#';
			m_piece[3][0] = '#';
			m_piece[2][1] = '#';
			m_piece[1][1] = '#';
			break;
		case 1:
			m_piece[3][0] = '#';
			m_piece[2][1] = '#';
			m_piece[2][2] = '#';
			m_piece[3][3] = '#';
			break;
		case 2:
			m_piece[0][3] = '#';
			m_piece[1][2] = '#';
			m_piece[2][2] = '#';
			m_piece[3][3] = '#';
			break;
		case 3:
			m_piece[0][0] = '#';
			m_piece[1][1] = '#';
			m_piece[1][2] = '#';
			m_piece[0][3] = '#';
			break;
		}
		break;
	}
}

//move LEFT/RIGHT/DOWN
void Piece::move(char m_move) {
	if (m_type == PIECE_CRAZY) {
		switch (m_move) {
		case ARROW_DOWN:
			m_y++;
			break;
		case ARROW_LEFT:
			m_x++;
			break;
		case ARROW_RIGHT:
			m_x--;
			break;
		case ARROW_UP:
			m_ori++;
			rotate();
			break;
		}
	}
	else {
		switch (m_move) {
		case ARROW_DOWN:
			m_y++;
			break;
		case ARROW_LEFT:
			m_x--;
			break;
		case ARROW_RIGHT:
			m_x++;
			break;
		case ARROW_UP:
			m_ori++;
			rotate();
			break;
		}
	}
}

int Piece::returnX() { return m_x; }  //accessor
int Piece::returnY() { return m_y; }  //accessor
PieceType Piece::returnType() { return m_type; } //accessor 
int Piece::returnOri() { return m_ori; }  //accessor