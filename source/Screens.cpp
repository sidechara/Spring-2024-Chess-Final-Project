#include "../header/Screens.h"
#include <fstream>
#include <gtkmm/dragsource.h>
#include <gtkmm/droptarget.h>
#include <gdkmm/contentprovider.h>

Screens::Screens() :
    start("New Game"), load("Load Game"), cont("Continue Game"), quit("Quit to Desktop"),
    vsPlayer("Vs Player"), vsCPU("Vs CPU"),
    noTimer("No Timer"), customTimer("Custom Timer: "),
    useCheckmate("Checkmate"), usePoints("Points"),
    startGame("Start Game")
{
    set_title("Chess");
    set_default_size(2300, 1300);
    set_child(stack);
 
    switcher.set_stack(stack);
    
    stack.add(main_menu());
    stack.add(player_selection());
    stack.add(board_selection());
    stack.add(mode_selection());
    stack.add(save_screen());

    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(sigc::mem_fun(*this, &Screens::on_key_pressed), false);
    add_controller(controller);

    stack.set_visible_child(mainMenu);
    
}

Screens::~Screens() {
    delete gameScreen;
}

Gtk::Widget& Screens::main_menu() {
    mainMenu = Gtk::Box(Gtk::Orientation::VERTICAL, 80);

    start.set_margin_top(400);
    mainMenu.append(start);
    start.set_halign(Gtk::Align::CENTER);
    start.signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_player_new));

    mainMenu.append(load);
    load.set_halign(Gtk::Align::CENTER);
    load.signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_player_load));

    mainMenu.append(cont);
    cont.set_halign(Gtk::Align::CENTER);
    cont.signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_player_cont));

    mainMenu.append(quit);
    quit.set_halign(Gtk::Align::CENTER);
    quit.signal_clicked().connect(sigc::mem_fun(*this, &Screens::on_button_quit));

    return mainMenu;
}

void Screens::on_button_quit() {
    set_visible(false);
}

void Screens::switch_player_load() {
    stack.set_visible_child(playerSelection);
}

void Screens::switch_player_cont() {
    gameScreen = new GameScreen(numberOfSaves());
    stack.add(game_screen());
    contGame = 1;
    stack.set_visible_child(playerSelection);
}

void Screens::switch_player_new() {
    gameScreen = new GameScreen(-1);
    stack.add(game_screen());
    contGame = 2;
    stack.set_visible_child(playerSelection);
}

Gtk::Widget& Screens::player_selection() {
    playerSelection = Gtk::Box(Gtk::Orientation::HORIZONTAL, 200);

    vsPlayer.set_margin_start(400);
    playerSelection.append(vsPlayer);
    vsPlayer.signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_vs_player));

    playerSelection.append(vsCPU);
    vsCPU.signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_vs_CPU));

    return playerSelection;
}

void Screens::switch_vs_player() {
    if (contGame == 1) {
        stack.set_visible_child(*gameScreen);
        return;
    } else if (contGame == 2) {
        stack.set_visible_child(modeSelection);
        return;
    }
    stack.set_visible_child(boardSelection);

}

void Screens::switch_vs_CPU() {
    gameScreen->setPlayerType();
    if (contGame == 1) {
        stack.set_visible_child(*gameScreen);
        return;
    } else if (contGame == 2) {
        stack.set_visible_child(modeSelection);
        return;
    }
    stack.set_visible_child(boardSelection);
}

void Screens::saveGame() {
    gameScreen->saveGame();
    set_visible(false);
}

Gtk::Widget& Screens::board_selection() {
    int numberOfBoards = numberOfSaves();
    for (unsigned i = 0; i < numberOfBoards; i++) {
        boards.push_back(Gtk::Button("Save " + std::to_string(i+1)));
        boardsInfo.push_back(boardInfo());
        boards.at(i).signal_clicked().connect(sigc::mem_fun(boardsInfo.at(i), &boardInfo::setSelected));
        boards.at(i).signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_mode_screen));
    }

    for (unsigned i = 0; i < boards.size(); i++) {
        boardSelection.append(boards.at(i));
    }

    return boardSelection;
}

void Screens::switch_mode_screen() {
    for (unsigned i = 0; i < boardsInfo.size(); i++) {
        if (boardsInfo.at(i).selected == 1) {
            boardN = i;
            break;
        }
    }
    if (contGame == 0) {
        gameScreen = new GameScreen(boardN+1);
        stack.add(game_screen());
        stack.set_visible_child(*gameScreen);
        return;
    }
    stack.set_visible_child(modeSelection);
}

void Screens::click_cb() {
    customTimer.set_active();
}

Gtk::Widget& Screens::mode_selection() {
    modeSelection = Gtk::Box(Gtk::Orientation::VERTICAL, 100);

    noTimer.set_group(customTimer);
    modeSelection.append(noTimer);

    customTimerBox = Gtk::Box(Gtk::Orientation::HORIZONTAL, 100);
    customTimerBox.append(customTimer);

    controller->signal_enter().connect(sigc::mem_fun(*this, &Screens::click_cb));
    timerEntry.add_controller(controller);
    timerEntry.set_max_length(5);
    connect = timerEntry.signal_changed().connect(sigc::mem_fun(*this, &Screens::validateTimer));

    customTimerBox.append(timerEntry);
    modeSelection.append(customTimerBox);

    useCheckmate.set_group(usePoints);
    modeSelection.append(useCheckmate);
    modeSelection.append(usePoints);

    startGame.signal_clicked().connect(sigc::mem_fun(*this, &Screens::switch_game_screen));
    modeSelection.append(startGame);

    return modeSelection;
}

void Screens::validateTimer() {
    std::string text = timerEntry.get_text();
    std::string numbers = "0123456789:";
    if (numbers.find(text.at(text.length()-1)) == std::string::npos) {
        connect.block();
        timerEntry.set_text(text.substr(0, text.length()-1));
        connect.unblock();
    }

}

void Screens::switch_game_screen() {
    if (noTimer.get_active() || customTimer.get_active()) {
        if (noTimer.get_active()) {
            seconds = -1;
            gameScreen->setSeconds(-1);
        } else {
            std::string time = timerEntry.get_text();
            seconds = std::stoi(time.substr(0, 2))*60 + std::stoi(time.substr(3, 2));
            gameScreen->setSeconds(seconds);
        }
        if (useCheckmate.get_active() || usePoints.get_active()) {
            if (useCheckmate.get_active()) {
                gameType = 0;
            } else {
                gameType = 1;
                gameScreen->setGameType();
            }
            stack.set_visible_child(*gameScreen);
            return;
        }
    }
}

Gtk::Widget& Screens::game_screen() {

    source->set_actions(Gdk::DragAction::MOVE);
    source->signal_prepare().connect(sigc::mem_fun(*this, &Screens::on_drag_prepare_data), false);
    source->signal_drag_end().connect(sigc::mem_fun(*this, &Screens::on_drag_end));
    source->signal_drag_cancel().connect(sigc::mem_fun(*this, &Screens::on_drag_cancel), false);

    gameScreen->getPieces()->add_controller(source);

    const GType ustring_type = Glib::Value<Glib::ustring>::value_type();
    target = Gtk::DropTarget::create(ustring_type, Gdk::DragAction::MOVE);
    target->signal_drop().connect(sigc::mem_fun(*this, &Screens::on_drop), false);

    gameScreen->getPieces()->add_controller(target);
    return *gameScreen;
    
}

Glib::RefPtr<Gdk::ContentProvider> Screens::on_drag_prepare_data(double x, double y) {

    drag_col = x/162;
    drag_row = y/162;

    Glib::Value<Glib::ustring> ustring_value;
    ustring_value.init(ustring_value.value_type());
    ustring_value.set("");
    source->set_icon(nullptr, 81, 81);

    Piece* piece = gameScreen->getActualPiece(drag_row, drag_col);
    if (piece == nullptr) {
        invalidDrag = 1;
        return Gdk::ContentProvider::create(ustring_value);
    } else {
        Color color = piece->getColor();
        bool turn = gameScreen->getTurn();
        if ((color == White && turn == 1) || (color == Black && turn == 0)) {
            invalidDrag = 1;
            return Gdk::ContentProvider::create(ustring_value);
        }
    }

    Gtk::Picture* p = dynamic_cast<Gtk::Picture*>(gameScreen->getPiece(drag_col, drag_row));
    source->set_icon(p->get_paintable(), 81, 81);
    gameScreen->setDragged(p->get_paintable());

    gameScreen->hidePieceAt(drag_col, drag_row);
    return Gdk::ContentProvider::create(ustring_value);
}

void Screens::on_drag_end(const std::shared_ptr<Gdk::Drag>&, const bool&) {
}

bool Screens::on_drag_cancel(const std::shared_ptr<Gdk::Drag>&, Gdk::DragCancelReason) {
    if (invalidDrag == 1) {
        invalidDrag = 0;
        return true;
    }
    gameScreen->showHiddenPiece(drag_col, drag_row);
    return true;
}

bool Screens::on_drop(const Glib::ValueBase& value, double x, double y) {
    if (invalidDrag == 1) {
        invalidDrag = 0;
        return true;
    }

    drop_col = x/162;
    drop_row = y/162;

    Piece* piece = gameScreen->getActualPiece(drag_row, drag_col);
    std::vector<Square> validSquares = piece->validMoves();
    bool isValid = 0;
    for (unsigned i = 0; i < validSquares.size(); i++) {
        if (validSquares.at(i).get_row() == drop_row && validSquares.at(i).get_col() == drop_col) {
            isValid = 1;
            break;
        }
    }
    if (isValid) {
        gameScreen->movePiece(drag_col, drag_row, drop_col, drop_row);
        return true;
    }
    target->reject();
    gameScreen->showHiddenPiece(drag_col, drag_row);
    return false;
}

Gtk::Widget& Screens::save_screen() {
    saveScreen = Gtk::Box(Gtk::Orientation::VERTICAL, 300);
    Gtk::Label message("Do you want to save before quitting?");
    message.set_margin_top(400);
    yes.set_label("Yes");
    yes.signal_clicked().connect(sigc::mem_fun(*this, &Screens::saveGame));
    no.set_label("No");
    no.signal_clicked().connect(sigc::mem_fun(*this, &Screens::on_button_quit));
    Gtk::Box options(Gtk::Orientation::HORIZONTAL, 200);
    options.append(yes);
    options.append(no);
    options.set_halign(Gtk::Align::CENTER);
    saveScreen.append(message);
    saveScreen.append(options);

    return saveScreen;
}

bool Screens::on_key_pressed(guint keyval, guint, Gdk::ModifierType) {
    if (keyval == GDK_KEY_Escape) {
        if (stack.get_visible_child() == gameScreen) {
            stack.set_visible_child(saveScreen);
            return true;
        }
    }
    return false;
}

int Screens::numberOfSaves(){
  std::ifstream inFS;
  inFS.open("save.txt");
  if(!inFS.is_open())
    return 0;
  int counter=0;
  while(1){
    //++counter;
    inFS.ignore(999,'\n');
    if(inFS.eof())
      return counter;
    else ++counter;
  }
}



