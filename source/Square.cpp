#include "../header/Square.h"
// #define NDEBUG
#include "../header/Piece.h"
#include <assert.h>

Square::Square(int r,int c,Piece* oPiece):row(r),column(c),occupyingPiece(oPiece){}

void Square::set_row(int r){
  //assert(r>=0&&r<=7&&"Invalid row");
  row=r;
}
void Square::set_col(int c){
  //assert(c>=0&&c<=7&&"Invalid column");
  column=c;
}
/*void Square::delete_piece(){
  delete occupyingPiece;
}*/
void Square::set_piece(Piece*oPiece){
  occupyingPiece=oPiece;
}
void Square::remove_piece(){
  set_piece(0);
}

int Square::get_row()const{
  return row;
}
int Square::get_col()const{
  return column;
}
Piece* Square::get_piece()const{
  return occupyingPiece;
}