#include "GameObject.h"

/* TODO: 
*  - FIX "GLOBAL" VARIABLE gUnit
 * - subclasses for pieces and the game field (inheret from GameObject)?
 *		- because it simplifies initializing
 *		- because pieces rotate but the field doesn't have too
 *		- just need to make sure the collision detection (when written)
 *		  works for a gameObject of any size (should be okay)
 * - header just for the grand piece array
 *		- Solution?: solve by subclassing
 * - Collision detection
 * - gameField Subclass
 *		- renderBackGround()
 * - Pieces Queue
 *
 *
 */

/*			PUBLIC METHODS			*/
// TODO this seems to be needed in order to have a subclass. Is there a more elegant workaround?
GameObject::GameObject() {
	std::cout << "Called default GameObject constructor" << std::endl;; // ERROR
	unit = 0;
	pos.x = 0;
	pos.y = 0;
	width = height = 0;

	// copy the RGBs
	color = { 0xff,0,0xff };


	// retrieve pointer to global renderer
	renderer = nullptr;

	// Set rect's width and height to 1x1
	rect.w = rect.h = 100;
	std::cout << "&renderer = " << int(renderer) << std::endl;		// ERROR
}

GameObject::GameObject(SDL_Renderer* ren, const int w, const int h, int unitSize) 
	: renderer(ren), unit(unitSize), width(w), height(h)
{
	std::cout << "Called override GameObject constructor" << std::endl;; // ERROR

	// Set rect's width and height to 1x1
	rect.w = rect.h = unitSize;

	// Create pixel matrix of size h x w and populate with 0's
	pixelVec.resize(h, std::vector<char>(w, 0));
}

void GameObject::move(int dx, int dy) {
	pos.x += unit * dx;
	pos.y += unit * dy;
}

void GameObject::move(Position newXY) { pos = newXY; }

// TODO document - for debugging purposes
void GameObject::printGameObjectVector(std::vector<std::vector<char>> array) {
	std::cout << "PRINTING VECTOR:" << '\n';
	for (std::vector<char> vec : array) {
		for (char c : vec) {
			std::cout << int(c) << ", ";
		}
		std::cout << std::endl;
	}
}

void GameObject::render() {
	// Set render draw color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);

	int jWidth, iHeight;
	jWidth = iHeight = 5;

	// Render the "pixels"
	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < jWidth; j++) {
			// render any place there is non-zero
			if (pixelVec[i][j] != 0) {
				// translate matrix coordinate to x,y coordinate in pixels
				rect.x = pos.x + (unit * j);
				rect.y = pos.y + (unit * i);
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);
				SDL_RenderFillRect(renderer, &rect); // draw rect
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
				SDL_RenderDrawRect(renderer, &rect); // draw outline
			}
		}
	}
}


/*			FUNCTIONS			*/
// translates the global coordinates into local coordinates 
// based around a local origin, localOG.
// Because this is only ever used for determining matrix positions,
//	return Position tuple in block units rather than pixels		!!!!!!!!!!
// TODO this is probably bad because Position::Position has up to 
// now only stored pixel coords...
Position translateLocalToGlobal(Position global, Position localOG) {
	// perform translation
	global.x -= localOG.x;
	global.y -= localOG.y;

	// now convert to block coordinates
	global.x /= 15;			// TODO gUnit
	global.y /= 15;			// TODO gUnit

	return global;
}