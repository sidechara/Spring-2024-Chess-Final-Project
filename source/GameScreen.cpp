#include "../header/GameScreen.h"
#include <gtkmm/picture.h>

GameScreen::GameScreen(int boardN) {
    bool which = 0;
    for (unsigned i = 0; i < 8; i++) {
        for (unsigned j = 0; j < 8; j++) {
            Gtk::Picture squarePic;
            if (which == 0) {
                squarePic.set_resource("/images/images/tan.jpg");
                if (j != 7) which = 1;
            } else {
                squarePic.set_resource("/images/images/green.jpg");
                if (j!= 7) which = 0;
            }
            squarePic.set_size_request(162, 162);
            squaresGrid.attach(squarePic, j, i, 1, 1);
        }
    }

    piecesGrid.set_vexpand(false);

    if (boardN == -1) {
        board = new Board();
    } else {
        board = game.loadGame(boardN);
    }
    computer = new ComputerPlayer(board->getSet());
    for (unsigned i = 0; i < 8; i++) {
        for (unsigned j = 0; j < 8; j++) {
            Gtk::Picture pic;
            pic.set_resource(getPictureResource(board->getPiece(i, j)));
            pic.set_size_request(162, 162);
            piecesGrid.attach(pic, j, i, 1, 1);
        }
    }

    game.setBoard(board);

    append(overlay);
    
    squaresGrid.set_size_request(1300, 1300);
    overlay.set_child(squaresGrid);

    piecesGrid.set_size_request(1300, 1300);
    overlay.add_overlay(piecesGrid);

    append(area);

    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(sigc::mem_fun(*this, &GameScreen::on_key_pressed), false);
    add_controller(controller);
    append(donotremove);

}

GameScreen::~GameScreen() {
    delete board;
    delete computer;
}

Gtk::Widget* GameScreen::getPieces() {
    return &piecesGrid;
}

Gtk::Widget* GameScreen::getPiece(int col, int row) {
    return piecesGrid.get_child_at(col, row);

}

void GameScreen::hidePieceAt(int col, int row) {
    Gtk::Picture* p = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(col, row));

    p->set_resource("images/images/transparent.png");
}

void GameScreen::showHiddenPiece(int col, int row) {
    Gtk::Picture* p = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(col, row));
    p->set_paintable(paintable_dragged);
}

void GameScreen::movePiece(int old_col, int old_row, int new_col, int new_row) {
    Gtk::Picture* old_pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(old_col, old_row));
    old_pos->set_resource("images/images/transparent.png");

    Gtk::Picture* new_pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(new_col, new_row));
    new_pos->set_paintable(paintable_dragged);

    Square& begin = board->getSquare(old_row, old_col);
    Square& end = board->getSquare(new_row, new_col);
    
    Move added = game.addMove(begin, end);
    delete addedMove;
    addedMove = new Move(added.getStartSquare(), added.getEndSquare(), added.getMovedPiece(), added.getCapturedPiece());
    int points = board->movePiece(old_row, old_col, new_row, new_col);
    if (game.isPawnPromotion(*addedMove)) {
        queen.set_label("Queen");
        queen.signal_clicked().connect(sigc::mem_fun(*this, &GameScreen::on_choice_queen));
        knight.set_label("Knight");
        knight.signal_clicked().connect(sigc::mem_fun(*this, &GameScreen::on_choice_knight));
        bishop.set_label("Bishop");
        bishop.signal_clicked().connect(sigc::mem_fun(*this, &GameScreen::on_choice_bishop));
        rook.set_label("Rook");
        rook.signal_clicked().connect(sigc::mem_fun(*this, &GameScreen::on_choice_rook));
        promotionGrid.attach(queen, 0, 0, 1, 1);
        promotionGrid.attach(knight, 1, 0, 1, 1);
        promotionGrid.attach(bishop, 0, 1, 1, 1);
        promotionGrid.attach(rook, 1, 1, 1, 1);
        overlay.add_overlay(promotionGrid);

        //game.PromotePawn(addedMove.getMovedPiece(),  /*TODO: second parameter should be PieceType that got returned from the user input*/);
    }
    
    area.setPoints(points);

    game.switchTurn();
    area.switchTurn();
    if (area.getGameType() == 0) {
        if (board->isInCheck(game.getTurn())) {
            if (board->hasNoLegalMoves(game.getTurn())) {
                //checkmate, do something
                Gtk::Picture gameOver;
                gameOver.set_resource("images/images/halftransparent.png");
                gameOver.set_size_request(3000, 3000);
                overlay.add_overlay(gameOver);
                return;
            }
        } else {
            //calls some function to check for stalemate
        }
    }

    if (playerType == 1 && game.getTurn() == 1) {
        Square move = computer->makeMove();
        Piece* moved = computer->getMoved();
        int col = moved->getPlace().get_col();
        int row = moved->getPlace().get_row();
        paintable_dragged = (dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(col, row)))->get_paintable();
        movePiece(col, row, move.get_col(), move.get_row());
    }

}

void GameScreen::setDragged(Glib::RefPtr<Gdk::Paintable> paintable) {
    paintable_dragged = paintable;
}

Piece* GameScreen::getActualPiece(int row, int col) {
    return board->getPiece(row, col);
}

bool GameScreen::getTurn() {
    return game.getTurn();
}

bool GameScreen::on_key_pressed(guint keyval, guint, Gdk::ModifierType state) {
    if (keyval == GDK_KEY_z && (state & (Gdk::ModifierType::SHIFT_MASK | Gdk::ModifierType::CONTROL_MASK | Gdk::ModifierType::ALT_MASK)) == Gdk::ModifierType::CONTROL_MASK) {
        Move lastMove = game.undoMove();
        area.switchTurn();
        Piece* movedPiece = lastMove.getMovedPiece();
        Square& startSquare = lastMove.getStartSquare();
        Square& endSquare = lastMove.getEndSquare();
        Gtk::Picture* old_pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(startSquare.get_col(), startSquare.get_row()));
        old_pos->set_resource(getPictureResource(movedPiece));

        Piece* capturedPiece = lastMove.getCapturedPiece();
        Gtk::Picture* new_pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(endSquare.get_col(), endSquare.get_row()));
        if (capturedPiece != nullptr) {
            new_pos->set_resource(getPictureResource(capturedPiece));
        } else {
            new_pos->set_resource("images/images/transparent.png");
        }
        return true;
    }

    return false;
}

std::string GameScreen::getPictureResource(Piece* piece) {
    if (piece == nullptr) return "images/images/transparent.png";
    if (piece->getType() == PAWN) {
        if (piece->getColor() == White) return "images/images/LightPawn.png";
        else return "images/images/DarkPawn.png";
    }
    if (piece->getType() == ROOK) {
        if (piece->getColor() == White) return "images/images/LightRook.png";
        else return "images/images/DarkRook.png";
    }
    if (piece->getType() == KNIGHT) {
        if (piece->getColor() == White) return "images/images/LightKnight.png";
        else return "images/images/DarkKnight.png";
    }
    if (piece->getType() == BISHOP) {
        if (piece->getColor() == White) return "images/images/LightBishop.png";
        else return "images/images/DarkBishop.png";
    }
    if (piece->getType() == QUEEN) {
        if (piece->getColor() == White) return "images/images/LightQueen.png";
        else return "images/images/DarkQueen.png";
    }
    if (piece->getColor() == White) return "images/images/LightKing.png";
    return "images/images/DarkKing.png";
}

void GameScreen::on_choice_queen() {
    Piece* piece = game.PromotePawn(addedMove->getMovedPiece(), QUEEN);
    overlay.remove_overlay(promotionGrid);
    Gtk::Picture* pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(piece->getPlace().get_col(), piece->getPlace().get_row()));
    pos->set_resource(getPictureResource(piece));
}

void GameScreen::on_choice_knight() {
    Piece* piece = game.PromotePawn(addedMove->getMovedPiece(), KNIGHT);
    overlay.remove_overlay(promotionGrid);
    Gtk::Picture* pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(piece->getPlace().get_col(), piece->getPlace().get_row()));
    pos->set_resource(getPictureResource(piece));
}

void GameScreen::on_choice_bishop() {
    Piece* piece = game.PromotePawn(addedMove->getMovedPiece(), BISHOP);
    overlay.remove_overlay(promotionGrid);
    Gtk::Picture* pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(piece->getPlace().get_col(), piece->getPlace().get_row()));
    pos->set_resource(getPictureResource(piece));
}

void GameScreen::on_choice_rook() {
    Piece* piece = game.PromotePawn(addedMove->getMovedPiece(), ROOK);
    overlay.remove_overlay(promotionGrid);
    Gtk::Picture* pos = dynamic_cast<Gtk::Picture*>(piecesGrid.get_child_at(piece->getPlace().get_col(), piece->getPlace().get_row()));
    pos->set_resource(getPictureResource(piece));
}

void GameScreen::saveGame() {
    game.saveGame(area.getSeconds1(), area.getSeconds2(), area.getPoints1(), area.getPoints2());
}


