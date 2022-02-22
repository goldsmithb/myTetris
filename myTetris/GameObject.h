#pragma once
//#include "Game.h" TODO
#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>        // std::abs

/*      FORWARD DECLARATIONS   */

/*		ENUMS					*/
// TODO : create a piece subclass? Q: should a piece and the game field share ALL methods?
// TODO : static_cast instead of C-style casting >_<
// Which type of piece is this Game Object? 
enum class Piece {
	Square,
	N,			// TODO change order for my sanity
	Nreverse,
	L,
	Lreverse,
	Psi,
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
// TODO : add rotations. this will require adding another dimension - working on
extern std::vector<std::vector<std::vector<std::vector<char>>>> piecesGuide;

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
	// Constructor
	// width is the window width -- used to calculate starting position
	GameObject(SDL_Renderer* ren, int w, int h, Color c, Position XY, int unitSize, Piece pieceTypeID);
	~GameObject();


	/*		METHODS			*/

	// move the gameObject by the given amount
	void move(int dx, int dy);

	// move the gameObject to the given position
	void move(Position newXY);

	// Rotate the block
	// This means changing the rotation value and the pixelArray
	void rotate(SDL_Event event);

	/* update()
	 * update the state of the game object based on game state
	 */
	void update();

	/* render
	 * render the objcet to the screen
	 * this means drawing the rectangle to the window
	 */
	void render();


private:
	unsigned char unit; // for storing the gUnit value QUESTION this seems inelegant, to copy it
	Position pos;
	int cnt; // for counting until fall speed
	int speed; // how many frames to fall 1 unit - initially 60 or once per second
	// will be set based on level eventually
	Color color; // for storing R G B value of the object  TODO - link this to the pieceType using enum Piece
	Piece pieceType; // piece shape
	Rotation rotation; // rotation state
	int width, height;

	// 2D vector telling us which grid squares are occupied
	std::vector<std::vector<char>> pixelVec;

	// Rectangles representing the game object
	SDL_Rect rect;

	// renderer needed for rendering. Will pass in game renderer by reference
	SDL_Renderer* renderer;

	// translate the local array coordinates to the global window coordinates
	Position translateLocalGlobal(int x, int y);
	// TODO: verbose and unecessary? right now, it would be more lines of code 
	// to call this function
	


};