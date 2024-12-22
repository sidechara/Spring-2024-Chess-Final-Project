#include <iostream>
#include "../../header/Board.h"
#include "../../header/Game.h"
#include "gtest/gtest.h"


TEST(MoveTests, MoveConstructor) {
    PieceSet* newSet = new PieceSet();
    Square begin(1,1);
    Square end(2,2);
    Piece* rook = newSet->PieceAt(begin);
    Move newMove(begin,end,rook,nullptr);
    EXPECT_EQ(1,newMove.getStartSquare().get_col());
    delete newSet;
}


TEST(MoveTests, CapturedPiece) {
    PieceSet* newSet = new PieceSet();
    Square begin(1,1);
    Square end(2,2);
    Piece* rook = newSet->PieceAt(begin);
    Move newMove(begin,end,rook,nullptr);
    EXPECT_EQ(nullptr,newMove.getCapturedPiece());
    delete newSet;
}

TEST(MoveTests, MovedPiece) {
    PieceSet* newSet = new PieceSet();
    Square begin(1,1);
    Square end(2,2);
    Piece* rook = newSet->PieceAt(begin);
    Move newMove(begin,end,rook,nullptr);
    EXPECT_EQ(rook,newMove.getMovedPiece());
    delete newSet;
}

TEST(MoveTests, StartingSquare) {
    PieceSet* newSet = new PieceSet();
    Square begin(1,1);
    Square end(2,2);
    Piece* rook = newSet->PieceAt(begin);
    Move newMove(begin,end,rook,nullptr);
    EXPECT_EQ(1,newMove.getStartSquare().get_col());
    delete newSet;
}

TEST(MoveTests, EndingSquare) {
    PieceSet* newSet = new PieceSet();
    Square begin(1,1);
    Square end(2,2);
    Piece* rook = newSet->PieceAt(begin);
    Move newMove(begin,end,rook,nullptr);
    EXPECT_EQ(2,newMove.getEndSquare().get_col());
    delete newSet;
}
