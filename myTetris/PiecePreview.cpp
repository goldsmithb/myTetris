#pragma once
#include "PiecePreview.h"

PiecePreview::PiecePreview() {

}
PiecePreview::PiecePreview(Position p, GamePiece* gamePiece, SDL_Renderer* r)
    : pos(p), piece(gamePiece), renderer(r), title(nullptr) 
{
    rect.w = rect.h = 5 * GameObject::gUnit;
}
PiecePreview::PiecePreview(Position p, GamePiece * gamePiece, SDL_Renderer * r, const char* t)
    : pos(p), piece(gamePiece), renderer(r), title(t) 
{
    rect.w = rect.h = 5 * GameObject::gUnit;
}