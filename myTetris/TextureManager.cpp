#include "TextureManager.h"

/*
* creates a texture from the file fileName and returns a pointer to it
*/
SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	if (tempSurface == NULL) {
		std::cout << "Error loading " << fileName << " Error: " << IMG_GetError() << std::endl;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}