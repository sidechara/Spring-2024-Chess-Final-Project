#include "../header/Pawn.h"

std::vector<Square> Pawn::validMoves() {
  std::vector<Square> moves;
  int direction;
  if (color == White) {
    direction = -1;
  } else {
    direction = 1;
  }
  Square fMove(place.get_row()+direction, place.get_col());
  Square rKill(place.get_row()+direction, place.get_col()+1);
  Square lKill(place.get_row()+direction, place.get_col()-1);

  // move the piece forward once or twice if not moved yet
  if (fMove.get_row()<=7 && fMove.get_row() >= 0) {
    // move one step
    if (!hasPiece(fMove)){
      moves.push_back(fMove);
      // move two steps
      if (!moved) {
        if ((color == White && place.get_row() < 6) || (color == Black && place.get_row() > 1)) {
          moved = true;
        }
      }
      if (!moved) {//TODO:fix (moved is private, create a getter or change access to protected/public)
        fMove.set_row(place.get_row()+2*direction);
        if (!hasPiece(fMove)) {
          moves.push_back(fMove);
        }
      }
    }
  }
   // if there is enemy on either diagonal, can move there to kill.
  if (rKill.get_row()<=7&&rKill.get_row()>=0&&rKill.get_col()<=7&&rKill.get_col()>=0) {
    if (hasPiece(rKill)) {
      if (isEnemy(rKill)) {
        moves.push_back(rKill);
      }
    }
  }
  if (lKill.get_row()<=7&&lKill.get_row()>=0&&lKill.get_col()<=7&&lKill.get_col()>=0) {
    if (hasPiece(lKill)) {
      if (isEnemy(lKill)) {
        moves.push_back(lKill);
      }
    }
  }
  return moves;
}