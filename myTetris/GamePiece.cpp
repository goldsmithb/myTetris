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
	}
};


GamePiece::GamePiece(SDL_Renderer* ren, int w, int h, Color c, Position XY, int unitSize, Piece pieceTypeID) {
	// Call superclass constructor
	GameObject(ren, w, h, c, XY, unitSize);
	
	// Initialize cnt to 0 - used with speed
	cnt = 0;
	// Initialize speed to 60 --> fall every 60 frames (1 second)
	speed = 60;

	pieceType = pieceTypeID;

	// default rotation 
	rotation = Rotation::Default;

	// create the pixelVec for appropriate PieceType at default rotation
	pixelVec = piecesGuide.at(int(pieceType)).at(int(rotation));
	/*
	switch (pieceType) {
	case Piece::Square :
		pixelVec = piecesGuide.at(int(Piece::Square)).at(int(rotation));
		break;
	case Piece::N :
		pixelVec = piecesGuide.at(int(Piece::N)).at(int(rotation));
		break;
	default:
		break;
	}*/
}

void GamePiece::update() {
	// All blocks fall at base speed 2 units per second
	// at 60 frames/s that means 1 unit (yet undefined) every 30 frames

	cnt += 1;
	// if enough frames have elapsed, fall 1 unit
	if ((cnt % speed) == 0) {
		pos.y += 50;
	}

	// save this state into rect so that it can be rendered
	rect.x = pos.x;
	rect.y = pos.y;
}

// TODO (optimization) pass enum SDL_KeyCode instead of entire event
void GamePiece::rotate(SDL_Event event) {
	int res;
	int total = int(Rotation::RotationsTotal);

	//std::cout << "in GameObject::rotate()" << std::endl; // ERROR TODO add logging?

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