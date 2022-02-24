#include "GamePiece.h"
#include <vector>


/*		piecesGuide :
/* The 4D char array describing all the different types of pieces
 * in the game. */
std::vector<std::vector<std::vector<std::vector<char>>>> piecesGuide =
{
	// square = 0
	{
		// Default - no rotations
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 2, 1, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0},
		}
	},
	// N = 1
	{
		// Default rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 2, 1, 0},
			{0, 1, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// First rotation
		{
			{0, 0, 0, 0, 0},
			{0, 1, 0, 0, 0},
			{0, 1, 2, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Second Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 1, 2, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Third Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 2, 1, 0},
			{0, 0, 0, 1, 0},
			{0, 0, 0, 0, 0},
		}
	},
	// NReverse = 2
	{
		// Default rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 2, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0},
		},
		// First rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 1, 2, 0, 0},
			{0, 1, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Second Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 1, 1, 0, 0},
			{0, 0, 2, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Third Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 1, 0},
			{0, 0, 2, 1, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		}
	},
	// L = 3
	{
		// Default rotation
		{
			{0, 0, 0, 0, 0},
			{0, 1, 1, 0, 0},
			{0, 0, 2, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// First rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 1, 0},
			{0, 1, 2, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Second Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 2, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0},
		},
		// Third Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 2, 1, 0},
			{0, 1, 0, 0, 0},
			{0, 0, 0, 0, 0},
		}
	},
	// LReverse = 4
	{
		// Default rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 2, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// First rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 2, 1, 0},
			{0, 0, 0, 1, 0},
			{0, 0, 0, 0, 0},
		},
		// Second Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 2, 0, 0},
			{0, 1, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Third Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 1, 0, 0, 0},
			{0, 1, 2, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		}
	},
	// Psi = 5
	{
		// Default rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 2, 1, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// First rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 1, 2, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Second Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 1, 2, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Third Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 2, 1, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		}
	},
	// I = 6
	{
		// Default rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 2, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
		},
		// First rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{1, 1, 2, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Second Rotation
		{
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 2, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0},
		},
		// Third Rotation
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 2, 1, 1},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		}
	}
};


GamePiece::GamePiece(SDL_Renderer* ren, int unitSize, Piece pieceTypeID, int GFWidth, Position GFXY)
	: GameObject(ren, PIECE_WIDTH_HEIGHT, PIECE_WIDTH_HEIGHT, unitSize), 
	  cnt(0), speed(60), pieceType(pieceTypeID), rotation(Rotation::Default)
{
	std::cout << "called gamePiece override constructor" << std::endl;	// ERROR

	// set Piece's position to middle of the screen
	// TODO : this changes based on the pieceType and the position of the game field
	//		  so this is all wrong lol
	pos.x = GFXY.x;
	pos.y = GFXY.y;
	pos.x += unit * ((GFWidth - PIECE_WIDTH_HEIGHT) / 2);

	color = { 0xff, 0, 0 };

	// create the pixelVec for appropriate PieceType at default rotation
	pixelVec = piecesGuide.at(int(pieceType)).at(int(rotation));

	std::cout << "Created piece!" << std::endl;							// ERROR
	printGameObjectVector(pixelVec);									// ERROR
	std::cout << "Exiting GamePiece constructor. &renderer = " << int(renderer) << std::endl; // ERROR
}

void GamePiece::printRendererPtr() {
	std::cout << "print renderer ptr: renderer pts to " << int(renderer) << std::endl;		// ERROR
}

void GamePiece::update() {
	// All blocks fall at base speed 2 units per second
	// at 60 frames/s that means 1 unit (yet undefined) every 30 frames

	cnt += 1;
	// if enough frames have elapsed, fall 1 unit
	if ((cnt % speed) == 0) {
		pos.y += unit;
	}

	// save this state into rect so that it can be rendered
	rect.x = pos.x;
	rect.y = pos.y;
}

// TODO (optimization) pass enum SDL_KeyCode instead of entire event
void GamePiece::rotate(SDL_Event event) {

	// Square does not rotate
	if (pieceType == Piece::Square){
		return;
	}

	int res;
	int total = int(Rotation::RotationsTotal);

	//std::cout << "in GameObject::rotate()" << std::endl; // ERROR

	switch (event.key.keysym.sym) {
	case SDLK_z:
		// Rotate counter-clockwise
		res = int(rotation) - 1; // TODO yucky casting - make static casting?
		if (res < 0) { res = 3; }
		rotation = Rotation(std::abs(res % total));
		pixelVec = piecesGuide.at(int(pieceType)).at(int(rotation));
		break;
	case SDLK_x:
		// Rotate clockwise
		res = int(rotation) + 1; // TODO yucky casting
		rotation = Rotation(std::abs(res % total));
		pixelVec = piecesGuide.at(int(pieceType)).at(int(rotation));
		break;
	default:
		break;
	}
}