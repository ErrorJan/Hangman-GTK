#include "DialogWindow.hpp"

#include <gtkmm-3.0/gtkmm/builder.h>
#include <string>
#include <iostream>

DialogWindow* DialogWindow::instance = nullptr;

DialogWindow::DialogWindow( Glib::RefPtr<Gtk::Builder> builder )
{
    // needs to be deleted, since it's the root window
    builder->get_widget( "DialogBox", this->window );

    builder->get_widget( "Message", this->text );
    builder->get_widget( "Button", this->button );

    this->button->signal_clicked().connect( sigc::mem_fun( *this, &DialogWindow::OnButtonClicked ) );

    this->window->set_title( "Hangman in GTKmm!" );
}

DialogWindow::~DialogWindow()
{
    delete this->window;
}

void DialogWindow::Show( const std::string& text ) const
{
    this->window->hide();
    this->text->set_text( text );
    this->window->set_size_request( 0, 0 );
    this->window->show();
}

void DialogWindow::SetGlobal( DialogWindow& dialogLogic )
{
    DialogWindow::instance = &dialogLogic;
}

void DialogWindow::ShowGlobal( const std::string& text )
{
    if ( DialogWindow::instance == nullptr )
    {
        std::cerr << "ERROR: No global dialog set!!\n";
        return;
    }

    DialogWindow::instance->Show( text );
}

void DialogWindow::OnButtonClicked()
{
    this->window->hide();
}

void DialogWindow::HideGlobal()
{
    DialogWindow::instance->window->hide();
}