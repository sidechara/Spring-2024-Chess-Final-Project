#include "../header/Screens.h"
#include <gtkmm/application.h>

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("");
    return app->make_window_and_run<Screens>(argc, argv);
}