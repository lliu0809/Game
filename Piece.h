#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

class Screen;
class Well;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};


PieceType chooseRandomPieceType();







class Piece {
public:
	Piece();   //default constructor
	void rotate();  //move to the next orientation
	void move(char m_move);  //move LEFT/RIGHT/DOWN
	int returnX();  //accessor
	int returnY();  //accessor
	PieceType returnType();
	int returnOri();
	char m_piece[4][4];

private:
	PieceType m_type;
	int m_ori;//orientation of the piece
	int m_x;  //x coordinate of the left corner
	int m_y;  //y coordinate of the left corner
};

#endif // PIECE_INCLUDED
