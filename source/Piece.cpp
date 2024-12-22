#include "../header/Piece.h"
#include "../header/PieceSet.h"

bool Piece::hasPiece(Square position) {
  if (set->PieceAt(position) != 0) {
    return true;
  }
  return false;
}

bool Piece::isEnemy(Square position) {
  if (hasPiece(position)) {
    if (set->PieceAt(position)->color != color) {
      return true;
    }
  }
  return false;
}

std::vector<Square> Piece::slidingXY() {
  //vector storing all the squares directions that are accessible by the rook      
  std::vector<Square> moves;

  // set direction traversals
  Square travUp(place.get_row()+1, place.get_col());
  Square travDown(place.get_row()-1, place.get_col());
  Square travLeft(place.get_row(), place.get_col()-1);
  Square travRight(place.get_row(), place.get_col()+1);

  while(travUp.get_row()<=7&&travUp.get_row()>=0&&travUp.get_col()<=7&&travUp.get_col()>=0) {           // check if in between bounds of the board (both rows and columns)
    if (!hasPiece(travUp)) {                                                                                
      moves.push_back(travUp);                                                                          // if potential position has no piece, we add it to our moves
    }
    else {
      if (isEnemy(travUp)) {                                                                            // if we bump into a piece, and the piece is an enemy, that enemy can be captured, therefore it will be a valid move
        moves.push_back(travUp);  
      }
      break;
    }     
    travUp.set_row(travUp.get_row()+1);                                                                 // increment to next position
  }

  while(travDown.get_row()<=7&&travDown.get_row()>=0&&travDown.get_col()<=7&&travDown.get_col()>=0) {
    if (!hasPiece(travDown)) {
      moves.push_back(travDown);
    }
    else {
      if (isEnemy(travDown)) {
        moves.push_back(travDown);
      } 
      break;
    }
    travDown.set_row(travDown.get_row()-1);
  }

  while(travLeft.get_row()<=7&&travLeft.get_row()>=0&&travLeft.get_col()<=7&&travLeft.get_col()>=0) {
    if (!hasPiece(travLeft)) {
      moves.push_back(travLeft);
    }
    else {
      if (isEnemy(travLeft)) {
        moves.push_back(travLeft);
      } 
      break;
    }
    travLeft.set_col(travLeft.get_col()-1);
  }

  while(travRight.get_row()<=7&&travRight.get_row()>=0&&travRight.get_col()<=7&&travRight.get_col()>=0) {
    if (!hasPiece(travRight)) {
      moves.push_back(travRight);
    }
    else {
      if (isEnemy(travRight)) {
        moves.push_back(travRight);
      } 
      break;
    }
    travRight.set_col(travRight.get_col()+1);
  }

  return moves; 
}

std::vector<Square> Piece::slidingDiag() {

  std::vector<Square> moves;

  Square travNE(place.get_row()+1, place.get_col()+1);
  Square travSE(place.get_row()-1, place.get_col()+1);
  Square travSW(place.get_row()-1, place.get_col()-1);
  Square travNW(place.get_row()+1, place.get_col()-1);

  while(travNE.get_row()<=7&&travNE.get_row()>=0&&travNE.get_col()<=7&&travNE.get_col()>=0) {
    if (!hasPiece(travNE)) {
      moves.push_back(travNE);
    }
    else {
      if (isEnemy(travNE)) {
        moves.push_back(travNE);
      } 
      break;
    }
    travNE.set_row(travNE.get_row()+1);
    travNE.set_col(travNE.get_col()+1);
  }
  while(travSE.get_row()<=7&&travSE.get_row()>=0&&travSE.get_col()<=7&&travSE.get_col()>=0) {
    if (!hasPiece(travSE)) {
      moves.push_back(travSE);
    }
    else {
      if (isEnemy(travSE)) {
        moves.push_back(travSE);
      } 
      break;
    }
    travSE.set_row(travSE.get_row()-1);
    travSE.set_col(travSE.get_col()+1);
  }
  while(travSW.get_row()<=7&&travSW.get_row()>=0&&travSW.get_col()<=7&&travSW.get_col()>=0) {
    if (!hasPiece(travSW)) {
      moves.push_back(travSW);
    }
    else {
      if (isEnemy(travSW)) {
        moves.push_back(travSW);
      } 
      break;
    }
    travSW.set_row(travSW.get_row()-1);
    travSW.set_col(travSW.get_col()-1);
  }
  while(travNW.get_row()<=7&&travNW.get_row()>=0&&travNW.get_col()<=7&&travNW.get_col()>=0) {
    if (!hasPiece(travNW)) {
      moves.push_back(travNW);
    }
    else {
      if (isEnemy(travNW)) {
        moves.push_back(travNW);
      } 
      break;
    }
    travNW.set_row(travNW.get_row()+1);
    travNW.set_col(travNW.get_col()-1);
  }
  return moves;
}


bool Piece::isValidMove(Square position, bool isKing) {
  if (position.get_row()<=7&&position.get_row()>=0&&position.get_col()<=7&&position.get_col()>=0) {
    if (!hasPiece(position)) {
      if (isKing) {
        return !threatened(position);
      }
      return true;
    }
    else {
      if (isEnemy(position)) {
        if (isKing) {
          return !threatened(position);
        }
        return true;
      }
    }
  }
  return false;
}

bool Piece::threatened(Square position) {
  int index;
  if (color == White) {
    index = 0;
  } else {
    index = 16;
  }
  for (int i = index; i < index+16; i++) {
    if (i != 4 && i != 28 && set->getPieceAt(i) != nullptr && set->getPieceAt(i)->getCaptured() == false) {
      std::vector<Square> valid = set->getPieceAt(i)->validMoves();
      for (unsigned i = 0; i < valid.size(); i++) {
        if (valid.at(i).get_row() == position.get_row() && valid.at(i).get_col() == position.get_col()) {
          return true;
        }
      }
    }
  }
  return false;
}

int Piece::getPieceSetIndex() const {
  for (int i=0;i<32;++i) {
    if (set->getPieceAt(i) == this) {
      return i;
      break;
    }
  }
  return -1;    // can't find piece in pieceSet
}