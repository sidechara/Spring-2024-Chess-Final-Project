#include "../header/DisplayInfo.h"
#include <glibmm/main.h>

DisplayInfo::DisplayInfo() {
    
    set_content_width(1000);
    set_content_height(1300);

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &DisplayInfo::on_timeout), 1000);
    set_draw_func(sigc::mem_fun(*this, &DisplayInfo::on_draw));

}

void DisplayInfo::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    if (draw == 0) return;
    draw = 0;

    cr->set_source_rgb(0.0, 0.0, 0.0);

    Pango::FontDescription font;
    font.set_family("Monospace");
    font.set_weight(Pango::Weight::BOLD);

    auto layout = create_pango_layout("ESC to quit");
    layout->set_font_description(font);

    int text_width, text_height;
    layout->get_pixel_size(text_width, text_height);

    cr->move_to(width-text_width-100, 100);
    layout->show_in_cairo_context(cr);

    if (turn == 0) {
        layout->set_text("White to play");
    } else {
        layout->set_text("Black to play");
    }
    cr->move_to(100, (height/2)-200);
    layout->show_in_cairo_context(cr);

    if (seconds1 != -1 || seconds2 != -1) {
        std::string minutes1 = std::to_string(seconds1/60);
        std::string secs1 = std::to_string(seconds1%60);
        if (secs1.length() == 1) secs1 = "0" + secs1;
        std::string minutes2 = std::to_string(seconds2/60);
        std::string secs2 = std::to_string(seconds2%60);
        if (secs2.length() == 1) secs2 = "0" + secs2;
        layout->set_text("Time:   " + minutes1 + ":" + secs1 + "   " + minutes2 + ":" + secs2);
        cr->move_to(100, (height/2));
        layout->show_in_cairo_context(cr);
        if (turn == 0 && seconds1 > 0) {
            seconds1--;
        } else if (turn == 1 && seconds2 > 0) {
            seconds2--;
        }
    }

    if (gameType == 1) {
        std::string pts1 = std::to_string(points1);
        std::string pts2 = std::to_string(points2);
        layout->set_text("Points:   " + pts1 + "       " + pts2);
        cr->move_to(100, (height/2)+100);
        layout->show_in_cairo_context(cr);
    }

}

bool DisplayInfo::on_timeout() {
    draw = 1;
    queue_draw();
    return true;
}

void DisplayInfo::setSeconds(int s) {
    seconds1 = s;
    seconds2 = s;
}

void DisplayInfo::setGameType() {
    gameType = 1;
}

void DisplayInfo::setPoints(int points) {
    if (points > 0) points1 += points;
    else points2 -= points;
}