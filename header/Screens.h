#include "GameScreen.h"
#include "boardInfo.h"
#include <gtkmm.h>
#include <vector>

class Screens : public Gtk::Window {

    public:
        Screens();
        ~Screens();

    private:
        Gtk::Stack stack;
        Gtk::StackSwitcher switcher;

        Gtk::Widget& main_menu();
        Gtk::Box mainMenu;
        Gtk::Button start, load, cont, quit;
        int contGame = 0;

        void on_button_quit();

        void switch_player_load();
        void switch_player_cont();
        void switch_player_new();

        void saveGame();

        Gtk::Widget& player_selection();
        Gtk::Box playerSelection;
        Gtk::Button vsPlayer, vsCPU;

        void switch_vs_player();
        void switch_vs_CPU();

        Gtk::Widget& board_selection();
        Gtk::Box boardSelection;
        std::vector<Gtk::Button> boards;
        int boardN = -1;

        std::vector<boardInfo> boardsInfo;

        void switch_mode_screen();

        Gtk::Widget& mode_selection();
        Gtk::Box modeSelection;
        Gtk::ToggleButton noTimer, customTimer, useCheckmate, usePoints;
        Gtk::Entry timerEntry;
        Glib::RefPtr<Gtk::EventControllerFocus> controller = Gtk::EventControllerFocus::create();
        void click_cb();
        Gtk::Box customTimerBox;
        void validateTimer();
        sigc::connection connect;
        int seconds;
        bool gameType;
        Gtk::Button startGame;

        void switch_game_screen();

        Gtk::Widget& game_screen();
        GameScreen* gameScreen;
        
        Glib::RefPtr<Gtk::DragSource> source = Gtk::DragSource::create();
        Glib::RefPtr<Gtk::DropTarget> target;

        Glib::RefPtr<Gdk::ContentProvider> on_drag_prepare_data(double x, double y);
        bool invalidDrag = 0;
        void on_drag_end(const std::shared_ptr<Gdk::Drag>&, const bool&);
        bool on_drag_cancel(const std::shared_ptr<Gdk::Drag>&, Gdk::DragCancelReason);
        bool on_drop(const Glib::ValueBase&, double, double);
        int drag_col, drag_row, drop_col, drop_row;

        Gtk::Widget& save_screen();
        Gtk::Box saveScreen;
        Gtk::Button yes, no;
        bool on_key_pressed(guint, guint, Gdk::ModifierType);

        int numberOfSaves();

};