#include <gtkmm-3.0/gtkmm/application.h>
#include <iostream>

#include "GameManager.hpp"

int main( int argc, char* argv[] )
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "errorjan.hangman" );

    GameManager gameManager( app );

    // Ready first Window
    gameManager.StartGame();

    // Create the Game and Show the prepared Window
    // Returns when the Game closes.
    app->hold();
    return app->run( argc, argv );
}