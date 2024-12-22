#ifndef SQUARE_H
#define SQUARE_H

class Piece;
class Square{
  int row;
  int column;
  Piece* occupyingPiece;
public:
  Square(int r=0,int c=0,Piece* oPiece=0);
  // delete unused big three function
  Square& operator=(const Square&)=delete;
  // setters
  void set_row(int r);
  void set_col(int c);
  //void delete_piece();
  void set_piece(Piece* oPiece);
  void remove_piece();
  // getters
  int get_row()const;
  int get_col()const;
  Piece* get_piece()const;
};

#endif