#pragma once
#include "GameObject.h"

/* 
 * A Game Field is a type of GameObject that represents the
 * playing field and the blocks that have been placed down.
 * 
 * The only difference between it and a normal GameObject is that
 * it has additional rendering to do -- namely, the background color
 * to deliniate the game field.
 *
 */
class GameField : public GameObject {
public:
	GameField(SDL_Renderer* ren, Color c, int unitSize, int winW, int winH);

	void render();
	
	void update();

	/* copies a piece into a gameField */
	void absorb(GameObject piece);

private:
	SDL_Rect fieldRect;
	Color bgColor;
};