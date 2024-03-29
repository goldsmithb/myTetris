#pragma once
//#include "Game.h" TODO
#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>


/*      GLOBAL VARIABLES		*/

/*      CONSTANTS		*/

/*      STRUCTS                 */
// TODO these should probably be in some external, though I haven't decided yet
// tbf they are only needed for game objects
// cannot define in Game.h becuase Game.h inherets GameObject.h in order
// to make the players. --> therefore the compiler does Game before GameObject, and
// is lost because it doesn't know what a GameObject is yet.
/*  struct for storing (X,Y) SDL position */
typedef struct Position {
	int x, y;
} Position;

/*  struct for storing RGB values */
typedef struct Color {
	int r, g, b;
} Color;

/*
 * GameObject class 
 *  TODO : update documentation
 * 
 * Game objects are anything that is rendered to the screen that is mutable 
 * -- i.e., the grid 'game board' on which the blocks fall, the current
 * falling block, the held nlock, and the queue of blocks that will fall next
 * is a queue of gameObjects.
 * 
 * the constructor will allocate space for the objects properties, and, most
 * importantly, it will allocate space for the 2D int array pixelArray which
 * represents the dimensions of the game object and which squares are occupied.
 * 
 * e.g. the gameObject squareBlock might have a pixelArray that looks like:
 *		{{0, 0, 0, 0},
 *		 {0, 1, 1, 0},
 *		 {0, 1, 1, 0},
 *		 {0, 0, 0, 0}}			(all blocks should be able to fit in 4x4s)
 * which the render method will use to draw 4 SDL Rectangles at the 
 * desired positions (once per call to update).
 * some amount of translation will eventually be required.
 */
class GameObject {
public:
	/*      STATIC PROPERTIES */
	static const int gUnit = 20;			// value of an in-game 'pixel' unit in actual pixels
	static const int FIELD_WIDTH = 10;		// gameField width in units
	static const int FIELD_HEIGHT = 20;		// gameField height in units


	/*		CONSTRUCTORS	*/
	// width is the window width -- used to calculate starting position
	// TODO pass SDL_Renderer by reference !! in non C style :)
	GameObject(SDL_Renderer* ren, int w, int h);
	GameObject();
	//~GameObject();


	/*		METHODS			*/

	// move the gameObject by the given amount
	// dx, dy given in units
	void move(int dx, int dy);

	// move the gameObject to the given position
	void move(Position newXY);

	/* render()
	 * render the objcet to the screen
	 * this means drawing the rectangle to the window
	 */
	virtual void render();

	void printGameObjectVector(std::vector<std::vector<char>> array);

	void printGameObjectVector();

	Position& accessPos() { return pos; }

	void setPos(Position p) { pos = p; }

	std::vector<std::vector<char>>& accessPixelVec() { return pixelVec; }

	int getHeight() { return height; }

	int getWidth() { return width; }

protected:
	Position pos;		// position of the top-left corner, in pixels

	// 2D vector telling us which grid squares are occupied
	std::vector<std::vector<char>> pixelVec;

	SDL_Rect rect;		// Rectangles representing the game object

	// renderer needed for rendering. Will pass in game renderer by reference
	SDL_Renderer* renderer;

	Color color; // for storing R G B value of the object  TODO - link this to the pieceType using enum Piece

	int width, height; // dimensions of the pixelVec matrix (aka in units)

private:
};


// returns in UNITS!
Position translateLocalToGlobal(Position global, Position localOG);