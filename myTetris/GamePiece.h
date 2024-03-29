#pragma once
#include "GameObject.h"

/*		CONSTANTS		*/
const int PIECE_WIDTH_HEIGHT = 5;

/*		ENUMS					*/
// TODO : create a piece subclass? Q: should a piece and the game field share ALL methods?
// TODO : static_cast instead of C-style casting >_<
// Which type of piece is this Game Object? 
enum class Piece {
	Square,
	N,			// TODO change order for my sanity
	NReverse,
	L,
	LReverse,
	Psi,
	I,
	PiecesTotal
};

enum class Rotation {
	Default,
	First,
	Second,
	Third,
	RotationsTotal

};


/*		GLOBAL VARIABLES		*/
/* 4D array for storing all pieces. Each piece and every rotation
 * of each piece fits in a 5x5 array, so:
 *		D1 : Piece type ( indexed by enum class Piece )
 *		D2 : Piece rotation ( 0 = default, rotate clockwise with each index )
 *		D3 : rows (Y positions) of the local GameObject 5x5 pixel array
 *		D4 : columns (X positoins) of the local GameObject 5x5 pixel array
 */
 // TODO : is this necessary? Could just declare and define in the cpp
//extern std::vector<std::vector<std::vector<std::vector<char>>>> piecesGuide;


/*		CLASSES					*/
class GamePiece : public GameObject {

public:

	/* GamePiece(..) constructor
	 *		ren :			global renderer passed in from Game.cpp
	 *		unitSize :		the global unit size defined in Game.h. # of pixels in 1 unit
	 *		PieceTypeID :	determines the type of piece to create
	 *		winW :			width of the app window in pixels
	 *		winH :			height of the app window in pixels
	 *		GFXY :			position of the gameField. Needed to determine the starting position of the piece
	 *
	 * 
	 */
	GamePiece(SDL_Renderer* ren, int unitSize, Piece PieceTypeID, Position GFXY);
	//~GamePiece();

	/*		METHODS		*/

	/* update()
	 * update the state of the game object based on game state
	 */
	void update();

	// Rotate the piece
	// This means changing the rotation value and the pixelArray ptr
	void rotate(SDL_Event event);

	// center the position of a piece so that it starts in the right place
	// take in the gameField's position and width for calculation
	void centerPiece(Position GFXY);

	void printRendererPtr() {
		std::cout << "print renderer ptr: renderer pts to " << int(renderer) << std::endl;
	}

private:
	/*      PROPERTIES  */
	int cnt; // for counting until fall speed
	int speed; // how many frames to fall 1 unit - initially 60 or once per second
	// will be set based on level eventually
	Piece pieceType;
	Rotation rotation;
	Position startingPosition;

};