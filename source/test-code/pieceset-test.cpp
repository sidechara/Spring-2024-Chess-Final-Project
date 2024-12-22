#include "gtest/gtest.h"
#include "../../header/Board.h"
#include "../../header/Game.h"

TEST(PieceSetTests,getPieceAt){
  PieceSet pieceSet;
  Piece* rook = pieceSet.getPieceAt(0);
  EXPECT_EQ(ROOK, rook->getType());
}
TEST(PieceSetTests,pieceAt){
  PieceSet pieceSet;
  Square testSquare(0,0);
  Piece* rook = pieceSet.PieceAt(testSquare);
  EXPECT_EQ(ROOK, rook->getType());
}
TEST(PieceSetTests,removePiece){
  PieceSet pieceSet;
  Piece* piece = pieceSet.getPieceAt(0);
  pieceSet.removePiece(piece);
  EXPECT_EQ(pieceSet.getPieceAt(0)->getCaptured(), 1);
}
TEST(PieceSetTests,addPiece){
  PieceSet pieceSet;
  Piece* piece = pieceSet.getPieceAt(0);
  pieceSet.removePiece(piece);
  pieceSet.addPiece(piece);
  EXPECT_EQ(pieceSet.getPieceAt(0)->getCaptured(), 0);
}

TEST(PieceSetTests, PieceSetConstructor) {
    PieceSet set;
    EXPECT_EQ(BISHOP, set.getPieceAt(2)->getType());
}

TEST(PieceSetTests, PieceSetFromPieceArray) {
    Piece* pieces[32];
    for (unsigned i = 0; i < 32; i++) {
        if (i != 2) pieces[i] = nullptr;
        else pieces[i] = new Bishop(0, 2, Black, nullptr);
    }
    PieceSet set(pieces);
    EXPECT_EQ(BISHOP, set.getPieceAt(2)->getType());
}

TEST(PieceSetTests, PieceAt2) {
    PieceSet set;
    Square square(0, 2);
    EXPECT_EQ(BISHOP, set.PieceAt(square)->getType());
}

TEST(PieceSetTests, RemovePiece2) {
    PieceSet set;
    Piece* piece = set.getPieceAt(2);
    set.removePiece(piece);
    EXPECT_TRUE(set.getPieceAt(2)->getCaptured());
}

TEST(PieceSetTests, ChangePieceTo) {
    PieceSet set;
    delete set.getPieceAt(2);
    set.changePieceTo(nullptr, 2);
    EXPECT_EQ(nullptr, set.getPieceAt(2));
}