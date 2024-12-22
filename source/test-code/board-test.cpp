#include "gtest/gtest.h"
#include "../../header/Board.h"
#include "../../header/Game.h"

TEST(BoardTests, BoardConstructor) {
    Board board;
    Piece* rook = board.getPiece(0, 0);
    EXPECT_EQ(ROOK, rook->getType());
}

TEST(BoardTests, BoardFromSet) {
    PieceSet set;
    EXPECT_NO_FATAL_FAILURE(Board board(set));
}

TEST(BoardTests, BoardSquare) {
    Board board;
    Piece* blackQueen = board.getPiece(0, 3);
    EXPECT_EQ(blackQueen, board.getSquare(0, 3).get_piece());
}

TEST(BoardTests, MovePiece) {
    Board board;
    board.movePiece(7, 1, 5, 0);
    EXPECT_EQ(KNIGHT, board.getPiece(5, 0)->getType());
}

TEST(BoardTests, InCheck) {
    Board board;
    board.movePiece(6, 4, 5, 4);
    board.movePiece(1, 3, 2, 3);
    board.movePiece(7, 5, 3, 1);
    EXPECT_TRUE(board.isInCheck(1));
}

TEST(BoardTests, NoLegalMoves) {
    Board board;
    board.movePiece(6, 4, 5, 4);
    board.movePiece(1, 3, 2, 3);
    board.movePiece(7, 5, 3, 1);
    EXPECT_TRUE(board.hasNoLegalMoves(1));
}

TEST(BoardTests, GetSet) {
    Board board;
    PieceSet* set = board.getSet();
    EXPECT_EQ(KNIGHT, set->getPieceAt(30)->getType());
}