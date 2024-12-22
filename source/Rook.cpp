#include "../header/Rook.h"

std::vector<Square> Rook::validMoves() {
  return this->slidingXY();
}