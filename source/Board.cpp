#include "../header/Board.h"

Board::Board() {
    for (unsigned i = 0; i < 2; i++) {
        for (unsigned j = 0; j < 8; j++) {
            board[i][j].set_piece(pieceSet.getPieceAt(8*i+j));
        }
    }

    for (unsigned i = 6; i < 8; i++) {
        for (unsigned j = 0; j < 8; j++) {
            board[i][j].set_piece(pieceSet.getPieceAt(16+8*(i-6)+j));
        }
    }

    for (unsigned i = 0; i < 8; i++) {
        for (unsigned j = 0; j < 8; j++) {
            board[i][j].set_row(i);
            board[i][j].set_col(j);
        }
    }

}

Board::Board(PieceSet& load){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 32; ++k)
                if (load.getPieceAt(k)!=0&&
                    j==load.getPieceAt(k)->getPlace().get_row()&&
                    i==load.getPieceAt(k)->getPlace().get_col())
                    board[i][j].set_piece(load.getPieceAt(k));
}

Piece* Board::getPiece(int row, int col) {
    return board[row][col].get_piece();
}

int Board::movePiece(int old_row, int old_col, int new_row, int new_col) {
    Piece* moved = board[old_row][old_col].get_piece();
    Piece* captured = board[new_row][new_col].get_piece();
    board[old_row][old_col].set_piece(nullptr);
    board[new_row][new_col].set_piece(moved);
    moved->setPlace(new_row, new_col);
    if (captured != nullptr) {
        pieceSet.removePiece(captured);
        int side = 1;
        if (captured->getColor() == White) side = -1;
        return captured->getPoints()*side;
    }
    return 0;
}

bool Board::isInCheck(bool side) {
    if (side == 0) {
        Piece* king = pieceSet.getPieceAt(28);
        return king->threatened(king->getPlace());
    }
    Piece* king = pieceSet.getPieceAt(4);
    return king->threatened(king->getPlace());
}

bool Board::hasNoLegalMoves(bool side) {
    if (side == 0) {
        Piece* king = pieceSet.getPieceAt(28);
        return (king->validMoves().size() == 0);
    }
    Piece* king = pieceSet.getPieceAt(4);
    return (king->validMoves().size() == 0);
}