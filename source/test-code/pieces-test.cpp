#include "gtest/gtest.h"
#include "../../header/Board.h"
#include "../../header/Game.h"

TEST(BishopTests, BishopConstructor) {
    Bishop* bishop = new Bishop(0, 2, Black, nullptr);
    EXPECT_EQ(Black, bishop->getColor());
    delete bishop;
}

TEST(BishopTests, BishopType) {
    Bishop* bishop = new Bishop(0, 2, Black, nullptr);
    EXPECT_EQ(BISHOP, bishop->getType());
    delete bishop;
}

TEST(BishopTests, BishopPoints) {
    Bishop* bishop = new Bishop(0, 2, Black, nullptr);
    EXPECT_EQ(3, bishop->getPoints());
    delete bishop;
}

TEST(BishopTests, BishopMoves) {
    Piece* pieces[32];
    pieces[0] = new Bishop(0, 2, Black, nullptr);
    for (unsigned i = 1; i < 32; i++) {
        pieces[i] = nullptr;
    }
    PieceSet* set = new PieceSet(pieces);
    set->getPieceAt(0)->setSet(set);
    std::vector<Square> validSquares = set->getPieceAt(0)->validMoves();
    bool isValid = 0;
    Square square = Square(2, 4);
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == square.get_row() && validSquares.at(i).get_col() == square.get_col()) {
            isValid = 1;
            break;
        }
    }
    EXPECT_TRUE(isValid);
    delete set;
}

TEST(KingTests, KingConstructor) {
    King* king = new King(7, 4, White, nullptr);
    EXPECT_EQ(White, king->getColor());
    delete king;
}

TEST(KingTests, KingType) {
    King* king = new King(7, 4, White, nullptr);
    EXPECT_EQ(KING, king->getType());
    delete king;
}

TEST(KingTests, KingPoints) {
    King* king = new King(7, 4, White, nullptr);
    EXPECT_EQ(0, king->getPoints());
    delete king;
}

TEST(KingTests, KingMoves) {
    Piece* pieces[32];
    pieces[28] = new King(7, 4, White, nullptr);
    for (unsigned i = 0; i < 32; i++) {
        if (i != 28) pieces[i] = nullptr;
    }
    PieceSet* set = new PieceSet(pieces);
    set->getPieceAt(28)->setSet(set);
    std::vector<Square> validSquares = set->getPieceAt(28)->validMoves();
    bool isValid = 0;
    Square square = Square(5, 2);
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == square.get_row() && validSquares.at(i).get_col() == square.get_col()) {
            isValid = 1;
            break;
        }
    }
    EXPECT_FALSE(isValid);
    delete set;
}

TEST(KnightTests, KnightConstructor) {
    Knight* knight = new Knight(0, 1, Black, nullptr);
    EXPECT_EQ(Black, knight->getColor());
    delete knight;
}

TEST(KnightTests, KnightType) {
    Knight* knight = new Knight(0, 1, Black, nullptr);
    EXPECT_EQ(KNIGHT, knight->getType());
    delete knight;
}

TEST(KnightTests, KnightPoints) {
    Knight* knight = new Knight(0, 1, Black, nullptr);
    EXPECT_EQ(3, knight->getPoints());
    delete knight;
}

TEST(KnightTests, KnightMoves) {
    Piece* pieces[32];
    pieces[1] = new Knight(0, 1, Black, nullptr);
    for (unsigned i = 0; i < 32; i++) {
        if (i != 1) pieces[i] = nullptr;
    }
    PieceSet* set = new PieceSet(pieces);
    set->getPieceAt(1)->setSet(set);
    std::vector<Square> validSquares = set->getPieceAt(1)->validMoves();
    bool isValid = 0;
    Square square = Square(2, 0);
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == square.get_row() && validSquares.at(i).get_col() == square.get_col()) {
            isValid = 1;
            break;
        }
    }
    EXPECT_TRUE(isValid);
    delete set;
}

TEST(PawnTests, PawnConstructor) {
    Pawn* pawn = new Pawn(3, 4, White, nullptr);
    EXPECT_EQ(White, pawn->getColor());
    delete pawn;
}

TEST(PawnTests, PawnType) {
    Pawn* pawn = new Pawn(3, 4, White, nullptr);
    EXPECT_EQ(PAWN, pawn->getType());
    delete pawn;
}

TEST(PawnTests, PawnPoints) {
    Pawn* pawn = new Pawn(3, 4, White, nullptr);
    EXPECT_EQ(1, pawn->getPoints());
    delete pawn;
}

TEST(PawnTests, PawnMoves) {
    Piece* pieces[32];
    pieces[20] = new Pawn(3, 4, White, nullptr);
    for (unsigned i = 0; i < 32; i++) {
        if (i != 20) pieces[i] = nullptr;
    }
    PieceSet* set = new PieceSet(pieces);
    set->getPieceAt(20)->setSet(set);
    std::vector<Square> validSquares = set->getPieceAt(20)->validMoves();
    bool isValid = 0;
    Square square = Square(1, 4);
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == square.get_row() && validSquares.at(i).get_col() == square.get_col()) {
            isValid = 1;
            break;
        }
    }
    EXPECT_FALSE(isValid);
    delete set;
}

TEST(QueenTests, QueenConstructor) {
    Queen* queen = new Queen(7, 2, Black, nullptr);
    EXPECT_EQ(Black, queen->getColor());
    delete queen;
}

TEST(QueenTests, QueenType) {
    Queen* queen = new Queen(7, 2, Black, nullptr);
    EXPECT_EQ(QUEEN, queen->getType());
    delete queen;
}

TEST(QueenTests, QueenPoints) {
    Queen* queen = new Queen(7, 2, Black, nullptr);
    EXPECT_EQ(9, queen->getPoints());
    delete queen;
}

TEST(QueenTests, QueenMoves) {
    Piece* pieces[32];
    pieces[3] = new Queen(7, 2, Black, nullptr);
    for (unsigned i = 0; i < 32; i++) {
        if (i != 3) pieces[i] = nullptr;
    }
    PieceSet* set = new PieceSet(pieces);
    set->getPieceAt(3)->setSet(set);
    std::vector<Square> validSquares = set->getPieceAt(3)->validMoves();
    bool isValid = 0;
    Square square = Square(0, 2);
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == square.get_row() && validSquares.at(i).get_col() == square.get_col()) {
            isValid = 1;
            break;
        }
    }
    EXPECT_TRUE(isValid);
    delete set;
}

TEST(RookTests, RookConstructor) {
    Rook* rook = new Rook(6, 3, White, nullptr);
    EXPECT_EQ(White, rook->getColor());
    delete rook;
}

TEST(RookTests, RookType) {
    Rook* rook = new Rook(6, 3, White, nullptr);
    EXPECT_EQ(ROOK, rook->getType());
    delete rook;
}

TEST(RookTests, RookPoints) {
    Rook* rook = new Rook(6, 3, White, nullptr);
    EXPECT_EQ(5, rook->getPoints());
    delete rook;
}

TEST(RookTests, RookMoves) {
    Piece* pieces[32];
    pieces[31] = new Rook(6, 3, White, nullptr);
    for (unsigned i = 0; i < 31; i++) {
        pieces[i] = nullptr;
    }
    PieceSet* set = new PieceSet(pieces);
    set->getPieceAt(31)->setSet(set);
    std::vector<Square> validSquares = set->getPieceAt(31)->validMoves();
    bool isValid = 0;
    Square square = Square(5, 6);
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == square.get_row() && validSquares.at(i).get_col() == square.get_col()) {
            isValid = 1;
            break;
        }
    }
    EXPECT_FALSE(isValid);
    delete set;
}