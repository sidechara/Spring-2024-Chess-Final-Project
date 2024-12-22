#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>
# include "Square.h"

enum Color {
  White,
  Black
};

enum PieceType {
  PAWN,
  QUEEN,
  ROOK,
  BISHOP,
  KNIGHT,
  KING
};

class PieceSet;
class Piece {
protected:
  Color color;
  Square place;
  PieceSet * set;
public:
  virtual std::vector<Square> validMoves() = 0;
  virtual Color getColor() const = 0;
  virtual PieceType getType() const = 0;
  virtual int getPoints() const = 0;
  virtual ~Piece() = default;
   
    void gotCaptured() {                              // changes status to being captured
      toBeCaptured = true;  
    }
    void gotUncaptured() {                            // revives the piece (used when undoing move)
      toBeCaptured = false;
    }
    Square& getPlace() {                          // returns place
      return place;
    }
    PieceSet * getSet() const {
      return set;
    }
    void setSet(PieceSet* s){set = s;}
    void setPlace(int row, int col) {
      place.set_row(row);
      place.set_col(col);
    }

    std::vector<Square> slidingXY();                    // finds all valid Moves of horizontal and vertical paths
    std::vector<Square> slidingDiag();                  // finds all valid Moves of diagonal paths
    bool hasPiece(Square position);                     // checks if a square has a piece
    bool isEnemy(Square position);                      // checks if a square has an enemy piece
    bool isValidMove(Square position, bool isKing);                  // see's if a position is valid (no teammates exist on square and not out of bounds) 
    bool threatened(Square position);
    bool getCaptured(){return toBeCaptured;}
    int getPieceSetIndex() const;

  protected:
    Color color;
    Square place;
    PieceSet * set;
    bool toBeCaptured = false;                        // status of being captured or not
};

#endif