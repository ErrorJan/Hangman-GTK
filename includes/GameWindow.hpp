#ifndef GameWindow_HPP
#define GameWindow_HPP

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/box.h>

#include <iostream>

#include "GameManager.hpp"

class GameWindow
{
    public:
        GameWindow( Glib::RefPtr<Gtk::Builder> builder, GameManager* manager );
        ~GameWindow();
        void Show();
        void SetWord( Glib::ustring word );

    private:
        GameManager* manager;
        Glib::ustring word;
        Glib::ustring hiddenWord;
        Glib::ustring usedLetters;
        Gtk::Image* image;
        unsigned int wrongGuesses;
        unsigned int guessesLeft;
        bool gameFinished;
        const unsigned int maxBadGuesses = 10;

        Gtk::Window* window;
        Gtk::Box* imageContainer;
        Gtk::Button* guess;
        Gtk::Label* usedLettersLabel;
        Gtk::Label* unfinishedWord;
        Gtk::Entry* inputChar;
        Gtk::Button* gameRestart;

        bool OnPressClose( GdkEventAny* event );
        void OnGuessLetter();
        void LoadNewImage( int imgNum );
        void OnGameRestart();
};

#endif