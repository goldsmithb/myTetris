#include "GameObject.h"

/* TODO: 
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

GameObject::GameObject(SDL_Renderer* ren, const int w, const int h, Color c, Position XY, int unitSize) 
	: pos(XY), renderer(ren), unit(unitSize), color(c), width(w), height(h)
{
	std::cout << "Called override GameObject constructor" << std::endl;; // ERROR
	
	// TODO : make w,h obsolete by subclassing ?
	//		 WAIT LOL  - this is already obscolete because it vector's can have any size!!! ?

	std::cout << "&renderer = " << int(renderer) << std::endl;		// ERROR
	std::cout << "&ren (the paramater given) = " << int(ren) << std::endl;		// ERROR

	// Set rect's width and height to 1x1
	rect.w = rect.h = unitSize;
}

void GameObject::move(int dx, int dy) {
	pos.x += dx;
	pos.y += dy;
}


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

void GameObject::move(Position newXY) { pos = newXY;  }

SDL_Rect rect1;

void GameObject::render() {
	// ERROR : renderer is nullptr
	//std::cout << "Rendering GameObject" << std::endl;

	rect1.x = 0;
	rect1.y = 0;
	rect1.w = rect1.h = 50;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff); // TODO set as a bg color
	SDL_RenderFillRect(renderer, &rect1); // draw rect
	
	return;

	// Set render draw color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);

	int jWidth, iHeight;
	jWidth = iHeight = 5;


	// Render the "pixels"
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
}


/*			PRIVATE METHODS			*/

Position GameObject::translateLocalGlobal(int x, int y) {
	Position res;
	res.x = pos.x + x;
	res.y = pos.y + y;

	return res;
}