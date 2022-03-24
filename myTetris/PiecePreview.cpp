#pragma once
#include "PiecePreview.h"

PiecePreview::PiecePreview() {

}

PiecePreview::PiecePreview(Position p, GamePiece* gamePiece, SDL_Renderer* r)
    : pos(p), piece(gamePiece), renderer(r), title(nullptr) 
{
    rect.w = rect.h = 5 * GameObject::gUnit;
    rect.x = pos.x, rect.y = pos.y;
}

PiecePreview::PiecePreview(Position p, GamePiece * gamePiece, SDL_Renderer * r, const char* t)
    : pos(p), piece(gamePiece), renderer(r), title(t) 
{
    rect.w = rect.h = 5 * GameObject::gUnit;
    rect.x = pos.x, rect.y = pos.y;
}

void PiecePreview::render() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xff);
    SDL_RenderFillRect(renderer, &rect);
    // draw outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderDrawRect(renderer, &rect);
    // draw held piece
    if (piece) {
        piece->render();
        //std::cout << "-hPP pos: " << pos.x << " " << pos.y << "." << std::endl;
        //std::cout << "-hP pos: " << piece->accessPos().x << " " << piece->accessPos().y << "." << std::endl;

    }
}