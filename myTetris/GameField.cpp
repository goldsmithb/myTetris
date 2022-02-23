#include "GameField.h"

GameField::GameField(SDL_Renderer* ren, Color c, int unitSize, int winW, int winH)
	: GameObject(ren, FIELD_WIDTH, FIELD_HEIGHT, unitSize)
{
    bgColor = c;
    color = { 0xd3, 0xd3, 0xd3 };

    // calculate position by first converting the window dimensions from pixels to units,
    // performing the calculation, then converting back to pixels
    pos.x = unit * std::abs(((winW / unit) - FIELD_WIDTH) / 2);
    pos.y = unit * std::abs(((winH / unit) - FIELD_HEIGHT) / 2);
    fieldRect.x = pos.x;
    fieldRect.y = pos.y;
    fieldRect.w = FIELD_WIDTH * unit;
    fieldRect.h = FIELD_HEIGHT * unit;
}

void GameField::render() {
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 0xff);

    SDL_RenderFillRect(renderer, &fieldRect);

    GameObject::render();
}