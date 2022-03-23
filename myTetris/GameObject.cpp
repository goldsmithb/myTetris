#include "GameObject.h"

/* TODO: 
*  - FIX "GLOBAL" VARIABLE gUnit
 * - header just for the grand piece array
 *		- QUESTION this is not allowed impossible - why?
 *			- Things MUST be defined in a cpp file ? can only be declared in a header?
 * - Collision detection
 *		- prevent colliding while moving Left and right against blocks
 * - Pieces Queue
 * - Don't allow piece to rotate out of bounds--have to adjust their position
 *
 */

/*			PUBLIC METHODS			*/
// TODO this seems to be needed in order to have a subclass. Is there a more elegant workaround?
GameObject::GameObject() {
	//std::cout << "Called default GameObject constructor" << std::endl;; // ERROR
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
	//std::cout << "&renderer = " << int(renderer) << std::endl;		// ERROR
}

// ERROR for debugging
void print(const std::vector<std::vector<char>>& v)
{
	for (std::size_t i = 0; i < v.size(); ++i)
	{
		for (std::size_t j = 0; j < v[i].size(); ++j) std::cout << (int)v[i][j] << ' ';
		std::cout << '\n';
	}
}

GameObject::GameObject(SDL_Renderer* ren, const int w, const int h, int unitSize) 
	: renderer(ren), unit(unitSize), width(w), height(h)
{
	//std::cout << "Called override GameObject constructor" << std::endl;; // ERROR

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
//			But still, shouldn't need an input vector as a class method of GameObject
void GameObject::printGameObjectVector(std::vector<std::vector<char>> array) {
	std::cout << "PRINTING VECTOR:" << '\n';
	for (std::vector<char> vec : array) {
		for (char c : vec) {
			std::cout << int(c) << ", ";
		}
		std::cout << std::endl;
	}
}

// Overridden version
void GameObject::printGameObjectVector() {
	std::cout << "PRINTING VECTOR (overridden):" << '\n';
	for (std::vector<char> vec : pixelVec) {
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
	jWidth = this->width;
	iHeight = this->height;

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
	//std::cout << "(" << global.x << ", " << global.y << ") -->";					// ERROR
	
	// perform translation
	global.x -= localOG.x;
	global.y -= localOG.y;

	// now convert to block coordinates
	global.x /= gUnit;			// TODO gUnit
	global.y /= gUnit;			// TODO gUnit

	//std::cout << "(" << global.x << ", " << global.y << ")" << std::endl;		// ERROR

	return global;
}