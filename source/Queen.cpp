#include "../header/Queen.h"

std::vector<Square> Queen::validMoves() {
  std::vector<Square> xy = this->slidingXY();
  std::vector<Square> diag = this->slidingDiag();

  for (int i = 0; i < diag.size(); ++i) {
    xy.push_back(diag.at(i));
  }
  return xy;
}