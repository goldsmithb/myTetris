#include "Game.h"
//#undef main // needed if main() prototype does not match the SDL.h one


/*		GLOBAL VARIABLES		*/
Game* game = NULL;

int main(int argc, char* argv[]) {

	game = new Game();

	// Frame rate variables
	// the time when frame begins (top of game loop)
	Uint32 frameStart;
	// the time it took to process the frame (bottom of game loop)
	int frameTime;

	// Game Loop
	while (game->running() == true) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		// If frameDelay amount of time has not passed,
		// wait until time for the next frame
		if (gFrameDelay > frameTime) {
			SDL_Delay(gFrameDelay - frameTime);
		}
	}

	delete game;

	return 0;
}