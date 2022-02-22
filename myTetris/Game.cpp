#include "Game.h"

GameObject* currentPiece;

int count = 0;

Game::Game() {

}

Game::~Game() {

}


// TODO : initialize GameObject properties
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen == true) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized..." << std::endl;

        // create window
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        // create renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer created!" << std::endl;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff); // TODO make background color
        }

        isRunning = true;

        // Load game 
        // Load all the gameObjects!
        // TODO for now w and h aren't used (may not need if we end up subclassing)
        //  for now set to 5 bc all pieces are 5x5
        currentPiece = new GameObject(renderer, 5, 5, gBackGroundColor, gOrigin, gUnit, Piece::N);

    }
    else {
        std::cout << "SDL Failed to initialize. Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
}

// TODO document
// Process key press event and update current surface respectively
void processKeyEvent(SDL_Event event) {

    switch (event.key.keysym.sym) {
    case SDLK_UP:
        currentPiece->move(0, -5);
        break;
    case SDLK_DOWN:
        currentPiece->move(0, 5);
        break;
    case SDLK_LEFT:
        currentPiece->move(-5, 0);
        break;
    case SDLK_RIGHT:
        currentPiece->move(5, 0);
        break;
    case SDLK_x:
    case SDLK_z:
        currentPiece->rotate(event);
        break;
    default:
        break;
    }
}

// TODO document
// Process io events
// Right now, just quit and key events
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        processKeyEvent(event);
    default:
        break;
    }
}


void Game::update() { 

    // update game variables

    currentPiece->update();

}

void Game::render() {
    // clear render buffer & draw window base color
    SDL_SetRenderDrawColor(renderer, 235, 233, 178, 0xff); // TODO set as a bg color
    SDL_RenderClear(renderer);

    currentPiece->render();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}