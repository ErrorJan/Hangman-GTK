#include "GameManager.hpp"

#include <glibmm/regex.h>

#include "GameInitWindow.hpp"

GameInitWindow::GameInitWindow( Glib::RefPtr<Gtk::Builder> builder, GameManager* manager )
    : manager( manager )
{
    // needs to be deleted, since it's the root window
    builder->get_widget( "Game Init", this->window );
    builder->get_widget( "Quit", this->quit );
    builder->get_widget( "Start", this->start );
    builder->get_widget( "Word Input", this->wordInput );

    this->window->signal_delete_event().connect( sigc::mem_fun( *this, &GameInitWindow::OnPressClose ) );
    this->quit->signal_clicked().connect( sigc::mem_fun( *this, &GameInitWindow::OnPressQuit ) );
    this->start->signal_clicked().connect( sigc::mem_fun( *this, &GameInitWindow::OnPressStart ) );

    this->window->set_title( "Hangman in GTKmm!" );
}

GameInitWindow::~GameInitWindow()
{
    delete this->window;
}

void GameInitWindow::Show()
{
    this->wordInput->set_text( "" );
    this->window->set_size_request( 0, 0 );
    this->window->show();
}

bool GameInitWindow::OnPressClose( GdkEventAny* event )
{
    this->manager->SwitchState( GameState::Quit );

    // Ignore unused warning. Event might have something useful, but not rn
    (void)event; 

    return false;
}

void GameInitWindow::OnPressQuit()
{
    this->manager->SwitchState( GameState::Quit );
}

void GameInitWindow::OnPressStart()
{
    this->word = "";

    {
        bool addSpace = false;

        for ( gunichar uc : this->wordInput->get_text() )
        {
            if ( uc != ' ')
            {
                this->word += uc;
                addSpace = true;
            }
            else if ( addSpace )
            {
                this->word += uc;
                addSpace = false;
            }
        }
        if ( this->word.length() > 0 && this->word.at( this->word.length() - 1 ) == ' ' )
        {
            this->word = this->word.substr(0, this->word.length() - 1);
        }
    }

    if ( word.length() == 0 )
    {
        DialogWindow::ShowGlobal( "The guess word or sentence has to be longer than 0 letters! \n(Not counting Whitespaces)" );
        return;
    }

    this->window->hide();
    this->manager->SwitchState( GameState::Play );
}

Glib::ustring GameInitWindow::GetWord()
{
    return this->word;
}