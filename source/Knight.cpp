#include "../header/Knight.h"


std::vector<Square> Knight::validMoves() {
  std::vector<Square> moves;
  Square move1 = Square(place.get_row()+2, place.get_col()-1);
  Square move2 = Square(place.get_row()+2, place.get_col()+1);
  Square move3 = Square(place.get_row()+1, place.get_col()+2);
  Square move4 = Square(place.get_row()-1, place.get_col()+2);
  Square move5 = Square(place.get_row()-2, place.get_col()+1);
  Square move6 = Square(place.get_row()-2, place.get_col()-1);
  Square move7 = Square(place.get_row()-1, place.get_col()-2);
  Square move8 = Square(place.get_row()+1, place.get_col()-2);
  
  if (isValidMove(move1, false)) {
    moves.push_back(move1);
  }
  if (isValidMove(move2, false)) {
    moves.push_back(move2);
  }
  if (isValidMove(move3, false)) {
    moves.push_back(move3);
  }
  if (isValidMove(move4, false)) {
    moves.push_back(move4);
  }  
  if (isValidMove(move5, false)) {
    moves.push_back(move5);
  }
  if (isValidMove(move6, false)) {
    moves.push_back(move6);
  }
  if (isValidMove(move7, false)) {
    moves.push_back(move7);
  }
  if (isValidMove(move8, false)) {
    moves.push_back(move8);
  }
  return moves;
}
