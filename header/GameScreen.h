#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/overlay.h>
#include <gtkmm/button.h>
#include <gdkmm/paintable.h>
#include <gtkmm.h>

#include "DisplayInfo.h"
#include "Board.h"
#include "Game.h"
#include "ComputerPlayer.h"

class GameScreen : public Gtk::Box {

    public:
        GameScreen(int);
        ~GameScreen();
        Gtk::Widget* getPiece(int, int);
        void hidePieceAt(int, int);
        void showHiddenPiece(int, int);
        Gtk::Widget* getPieces();
        void movePiece(int, int, int, int);
        void setDragged(Glib::RefPtr<Gdk::Paintable>);
        Piece* getActualPiece(int, int);
        bool getTurn();
        void setSeconds(int s){area.setSeconds(s);};
        void setGameType(){area.setGameType();};
        std::string getPictureResource(Piece*);
        void setPlayerType(){playerType=1;}
        void saveGame();

    protected:
        DisplayInfo area;
        Gtk::Grid squaresGrid, piecesGrid, promotionGrid;
        Gtk::Overlay overlay;
        Glib::RefPtr<Gdk::Paintable> paintable_dragged;
        Gtk::Button queen, knight, bishop, rook;

        Game game;
        Board* board;
        ComputerPlayer* computer;

        bool on_key_pressed(guint, guint, Gdk::ModifierType);
        void on_choice_queen();
        void on_choice_knight();
        void on_choice_bishop();
        void on_choice_rook();
        Move* addedMove = nullptr;

        bool playerType = 0;
        Gtk::Button donotremove;

};