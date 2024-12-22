#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

class DisplayInfo : public Gtk::DrawingArea {

    public:
        DisplayInfo();
        void setSeconds(int);
        void setGameType();
        bool getGameType(){return gameType;}
        void switchTurn(){turn=!turn;};
        void setPoints(int);
        int getSeconds1(){return seconds1;}
        int getSeconds2(){return seconds2;}
        int getPoints1(){return points1;}
        int getPoints2(){return points2;}

    protected:
        void on_draw(const Cairo::RefPtr<Cairo::Context>&, int, int);
        bool on_timeout();
        bool turn = 0;
        int seconds1, seconds2;
        bool draw = 0;
        bool gameType = 0;
        int points1 = 0;
        int points2 = 0;
};