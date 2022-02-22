#include "GameObject.h"

/* TODO: 
 * - DEBUG : : : : GameObject::rotate(SDL_Event event) 
 * - subclasses for pieces and the game field (inheret from GameObject)?
 *		- because it simplifies initializing
 *		- because pieces rotate but the field doesn't have too
 *		- just need to make sure the collision detection (when written)
 *		  works for a gameObject of any size (should be okay)
 * - header just for the grand piece array
 *		- complete the grand piece array
 *
 *
 */


/*		ENUM DEFINITION			*/
// TODO : put in a header
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


/*			PUBLIC METHODS			*/

GameObject::GameObject(SDL_Renderer* ren, const int w, const int h, Color c, Position XY, int unitSize, Piece pieceTypeID) {
	// copy the value of gUnit
	unit = unitSize;
	
	// Default position for all blocks will be center top
	pos.x = XY.x;
	pos.y = XY.y;
	cnt = 0;
	speed = 60;
	pieceType = pieceTypeID;

	// TODO : make obsolete by subclassing ?
	//		 WAIT LOL  - this is already obscolete because it vector's can have any size!!! ?
	width = w, height = h;

	// default rotation 
	rotation = Rotation::Default;

	// copy the RGBs
	color = c;

	// create the pixelVec
	// TODO construct based on w and h varibales
	// for now:
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

	// retrieve pointer to global renderer
	renderer = ren;

	// set rect's width and height to 1x1
	rect.w = rect.h = unitSize;
}

void GameObject::move(int dx, int dy) {
	pos.x += dx;
	pos.y += dy;
}


// TODO document - for debugging purposes
void printPiece(std::vector<std::vector<char>> array) {
	std::cout << "PRINTING VECTOR:" << '\n';
	for (std::vector<char> vec : array) {
		for (char c : vec) {
			std::cout << int(c) << ", ";
		}
		std::cout << std::endl;
	}
}

void GameObject::move(Position newXY) { pos = newXY;  }

// TODO (optimization) pass enum SDL_KeyCode instead of entire event
void GameObject::rotate(SDL_Event event) {
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

void GameObject::update() {
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

void GameObject::render() {

	// Set render draw color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);

	int jWidth, iHeight;
	jWidth = iHeight = 5; 



	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < jWidth; j++) {
			// render any place there is non-zero
			if (pixelVec[i][j] != 0) {
				// render based on position translation
				rect.x = pos.x + (unit * j);
				rect.y = pos.y + (unit * i);
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);
				SDL_RenderFillRect(renderer, &rect); // draw rect
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
				SDL_RenderDrawRect(renderer, &rect); // draw outline
			}
		}
	}


	// Render the object
	//SDL_RenderFillRect(renderer, &rect);
}


/*			PRIVATE METHODS			*/

Position GameObject::translateLocalGlobal(int x, int y) {
	Position res;
	res.x = pos.x + x;
	res.y = pos.y + y;

	return res;
}