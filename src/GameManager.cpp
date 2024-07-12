#include "GameManager.hpp"

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/application.h>
#include <iostream>

#include "DialogWindow.hpp"
#include "GameInitWindow.hpp"
#include "GameWindow.hpp"

GameManager::GameManager( Glib::RefPtr<Gtk::Application> app ) : app( app )
{
    currentState = GameState::CleanStart;

    this->builder = Gtk::Builder::create();
    try 
    { 
        builder->add_from_file( "resources/ui/HangmanUI.glade" ); 
    }
    catch ( const std::exception& e ) 
    {
        std::cerr << e.what() << '\n';
        exit( 2 );
    }

    this->dialog = new DialogWindow( builder );
    DialogWindow::SetGlobal( *dialog );
    
    this->init = new GameInitWindow( builder, this );
    this->game = new GameWindow( builder, this );
}

GameManager::~GameManager()
{
    delete this->dialog;
    delete this->init;
    delete this->game;
}

void GameManager::SwitchState( GameState newState )
{
    if ( currentState == newState )
        return;

    DialogWindow::HideGlobal();

    switch ( newState )
    {
        case GameState::CleanStart:
            break;
        case GameState::GetString:
            this->init->Show();
            break;
        case GameState::Play:
            this->game->SetWord( this->init->GetWord() );
            this->game->Show();
            break;
        case GameState::Quit:
            // Quits the App
            this->app->quit();
            break;
        default:
            std::cerr << "ERROR: WRONG STATE FOUND!!\n";
            exit( 2 ); // Will this cause issues??
            // this->app->quit();
    }

    if ( currentState == GameState::GetString )
    {
        // Some easter egg stuff
        if ( this->init->GetWord().uppercase() == "LINUX" )
            DialogWindow::ShowGlobal( "The best GNU/Linux OS on the planet!" );
        else if ( this->init->GetWord().uppercase() == "FURRY" )
            DialogWindow::ShowGlobal( "Me too!" );
        else if ( this->init->GetWord().uppercase() == "BOWSER" )
            DialogWindow::ShowGlobal( "Is the coolest!" );
        else if ( this->init->GetWord().uppercase() == "PORTAL" )
            DialogWindow::ShowGlobal( "[GLaDOS] Aperture Science wants to remind you, that thinking with portals can and has made the world a better place." );
    }

    currentState = newState;
}

void GameManager::StartGame()
{
    SwitchState( GameState::GetString );
}

GameState GameManager::GetCurrentState()
{
    return this->currentState;
}