#include "../header/Bishop.h"

std::vector<Square> Bishop::validMoves() {
  return this->slidingDiag();
  
}
