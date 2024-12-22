#include "../header/King.h"

std::vector<Square> King::validMoves() {
  std::vector<Square> moves;
  Square move1(place.get_row()+1, place.get_col());
  Square move2(place.get_row()+1, place.get_col()+1);
  Square move3(place.get_row(), place.get_col()+1);
  Square move4(place.get_row()-1, place.get_col()+1);
  Square move5(place.get_row()-1, place.get_col());
  Square move6(place.get_row()-1, place.get_col()-1);
  Square move7(place.get_row(), place.get_col()-1);
  Square move8(place.get_row()+1, place.get_col()-1);

  if (isValidMove(move1, true)) {
    moves.push_back(move1);
  }
  if (isValidMove(move2, true)) {
    moves.push_back(move2);
  }
  if (isValidMove(move3, true)) {
    moves.push_back(move3);
  }
  if (isValidMove(move4, true)) {
    moves.push_back(move4);
  }  
  if (isValidMove(move5, true)) {
    moves.push_back(move5);
  }
  if (isValidMove(move6, true)) {
    moves.push_back(move6);
  }
  if (isValidMove(move7, true)) {
    moves.push_back(move7);
  }
  if (isValidMove(move8, true)) {
    moves.push_back(move8);
  }
  return moves;
}
