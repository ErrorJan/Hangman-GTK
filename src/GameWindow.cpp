#include "GameManager.hpp"

#include <string>

#include "GameWindow.hpp"

GameWindow::GameWindow( Glib::RefPtr<Gtk::Builder> builder, GameManager* manager )
    : manager( manager )
{
    // needs to be deleted, since it's the root window
    builder->get_widget( "Game", this->window );
    builder->get_widget( "Image Container", this->imageContainer );
    builder->get_widget( "Guess", this->guess );
    builder->get_widget( "Used Letters", this->usedLettersLabel );
    builder->get_widget( "Output", this->unfinishedWord );
    builder->get_widget( "Letter", this->inputChar );
    builder->get_widget( "Game Restart", this->gameRestart );

    this->window->signal_delete_event().connect( sigc::mem_fun( *this, &GameWindow::OnPressClose ) );
    this->guess->signal_clicked().connect( sigc::mem_fun( *this, &GameWindow::OnGuessLetter ) );
    this->gameRestart->signal_clicked().connect( sigc::mem_fun( *this, &GameWindow::OnGameRestart ) );

    this->image = nullptr;
    this->window->set_title( "Hangman in GTKmm!" );
}

GameWindow::~GameWindow()
{
    delete this->window;
}

void GameWindow::Show()
{
    LoadNewImage( 0 );
    this->window->set_size_request( 0, 0 );
    this->usedLettersLabel->set_text( "" );
    this->usedLetters = "";
    this->inputChar->set_text( "" );
    this->wrongGuesses = 0;
    this->gameFinished = false;
    this->window->show();
}

void GameWindow::SetWord( Glib::ustring word )
{
    this->word = word.uppercase();

    this->hiddenWord = "";
    this->guessesLeft = 0;
    for ( gunichar uc : word )
    {
        if ( uc == ' ' )
            this->hiddenWord += " ";
        else
        {
            this->guessesLeft++;
            this->hiddenWord += "_";
        }
    }

    this->unfinishedWord->set_text( this->hiddenWord );
}

bool GameWindow::OnPressClose( GdkEventAny* event )
{
    this->manager->SwitchState( GameState::Quit );

    (void) event;

    return false;
}

void GameWindow::OnGuessLetter()
{
    if ( gameFinished )
        return;

    if ( this->inputChar->get_text().length() == 0 )
    {
        DialogWindow::ShowGlobal( "Please input a letter next to the button!" );
        this->inputChar->set_text( "" );
        this->inputChar->grab_focus();
        return;
    }

    gunichar input = this->inputChar->get_text().uppercase().at(0);

    if ( this->usedLetters.find( input ) != std::string::npos )
    {
        DialogWindow::ShowGlobal( "You have already used this letter!" );
        this->inputChar->set_text( "" );
        this->inputChar->grab_focus();
        return;
    }

    if ( input == ' ' )
    {
        DialogWindow::ShowGlobal( "You can't guess an empty letter!" );
        this->inputChar->grab_focus();
        return;
    }

    Glib::ustring inputAsUStr = "";
    inputAsUStr += input;
    
    bool correctGuess = false;

    for ( unsigned int i = 0; i < this->word.length(); i++ )
    {
        if ( input == this->word.at( i ) )
        {
            this->hiddenWord.replace( i, 1, inputAsUStr );
            guessesLeft--;
            correctGuess = true;
        }
    }

    if ( !correctGuess )
        wrongGuesses++;

    usedLetters += input;

    Glib::ustring formattedUsedLetters = "";
    for ( gunichar uc : usedLetters )
    {
        formattedUsedLetters += uc;
        formattedUsedLetters += " ";
    }

    if ( wrongGuesses == maxBadGuesses )
    {
        Glib::ustring s = "You lost :( \nThe correct word was: \"";
        s += this->word;
        s += "\"";

        DialogWindow::ShowGlobal( s );

        this->gameFinished = true;
    }
    else if ( guessesLeft == 0 )
    {
        Glib::ustring s = "Congratulations! You won! :)";

        DialogWindow::ShowGlobal( s );

        this->gameFinished = true;
    }

    LoadNewImage( wrongGuesses );
    this->usedLettersLabel->set_text( formattedUsedLetters );
    this->unfinishedWord->set_text( this->hiddenWord );
    this->inputChar->set_text( "" );
    this->inputChar->grab_focus();
}

void GameWindow::LoadNewImage( int imgNum )
{
    if ( this->image != nullptr )   
    {
        this->imageContainer->remove( *this->image );
        delete this->image; // This needed, when I remove?
    }

    std::string path = "resources/images/Hangman/";
    path += std::to_string( imgNum );
    path += ".jpg";

    image = Gtk::make_managed<Gtk::Image>( path );
    this->imageContainer->add( *this->image );
    image->show();
}

void GameWindow::OnGameRestart()
{
    this->manager->SwitchState( GameState::GetString );
    this->window->hide();
}