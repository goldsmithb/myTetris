#include "GameField.h"

GameField::GameField(SDL_Renderer* ren, Color c, int unitSize, int winW, int winH)
	: GameObject(ren, FIELD_WIDTH, FIELD_HEIGHT, c, unitSize)
{
    fieldRect.x = unitSize * std::abs(((winW / unitSize) - FIELD_WIDTH) / 2);
    fieldRect.y = unitSize * std::abs(((winH / unitSize) - FIELD_HEIGHT) / 2);
    fieldRect.w = FIELD_WIDTH * unitSize;
    fieldRect.h = FIELD_HEIGHT * unitSize;
}

void GameField::render() {
    SDL_SetRenderDrawColor(renderer, color.r,  color.g, color.b, 0xff);

    SDL_RenderFillRect(renderer, &fieldRect);

    GameObject::render();
}