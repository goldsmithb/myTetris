#include "Game.h"
#include "SDL_ttf.h"
//#undef main // needed if main() prototype does not match the SDL.h one


/*		GLOBAL VARIABLES		*/
Game* game = nullptr;
TTF_Font* gFont = nullptr;
SDL_Texture* gTextTexture = nullptr;


int main(int argc, char* argv[]) {

	game = new Game();

	// Frame rate variables
	// the time when frame begins (top of game loop)
	Uint32 frameStart;
	// the time it took to process the frame (bottom of game loop)
	int frameTime;

	// Game Loop
	while (game->running()) {

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


    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    std::string text = "GAME OVER";
    SDL_Color textColor = { 0,0,0 };
    gFont = TTF_OpenFont("assets/Ticketing.ttf", 28); 
    if (gFont == NULL) {
        std::cout << "Could not load font. Error: " << TTF_GetError() << std::endl;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "GAME OVER", textColor);
    if (textSurface == NULL) {
        std::cout << "Could not render textSurface. Error: " << TTF_GetError() << std::endl;
    }

    gTextTexture = SDL_CreateTextureFromSurface(game->getRenderer(), textSurface);
    if (gTextTexture == NULL) {
        std::cout << "Could not create texture from surface text! Error: " << TTF_GetError() << std::endl;
    }
    
    SDL_FreeSurface(textSurface);

    SDL_Rect gTextTextureRect;
    gTextTextureRect.w = gWidth;
    gTextTextureRect.h = gWidth / 3;
    gTextTextureRect.x = 0;
    gTextTextureRect.y = (gHeight / 2) - (gTextTextureRect.h / 2);

	while (!game->running()) {
        SDL_RenderCopy(game->getRenderer(), gTextTexture, NULL, &gTextTextureRect);
        SDL_RenderPresent(game->getRenderer());
        SDL_Delay(3000);
        break;
	}

	delete game;

	return 0;
}