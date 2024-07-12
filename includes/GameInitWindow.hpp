#ifndef GameInitWindow_HPP
#define GameInitWindow_HPP

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/entry.h>

#include "GameManager.hpp"

class GameInitWindow
{
    public:
        GameInitWindow( Glib::RefPtr<Gtk::Builder> builder, GameManager* manager );
        ~GameInitWindow();
        void Show();
        Glib::ustring GetWord();

    private:
        GameManager* manager;
        Gtk::Window* window;
        Gtk::Button* quit;
        Gtk::Button* start;
        Gtk::Entry* wordInput;
        Glib::ustring word;

        bool OnPressClose( GdkEventAny* event );
        void OnPressQuit();
        void OnPressStart();
};

#endif