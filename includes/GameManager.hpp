#ifndef GameManager_HPP
#define GameManager_HPP

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/application.h>

class GameManager;

#include "DialogWindow.hpp"
#include "GameInitWindow.hpp"
#include "GameWindow.hpp"

enum class GameState
{
    CleanStart,
    GetString,
    Play,
    Quit,
};

class GameManager
{
    public:
        GameManager( Glib::RefPtr<Gtk::Application> app );
        ~GameManager();

        void SwitchState( GameState newState );
        void StartGame();
        GameState GetCurrentState();
    
    private:
        GameState currentState;
        Glib::RefPtr<Gtk::Application> app;
        Glib::RefPtr<Gtk::Builder> builder;
        DialogWindow* dialog;
        GameInitWindow* init;
        GameWindow* game;
};

#endif