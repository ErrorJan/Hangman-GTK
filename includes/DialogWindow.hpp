#ifndef GWDialogLogic_HPP
#define GWDialogLogic_HPP

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/dialog.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <string>

class DialogWindow
{
    public:
        DialogWindow( Glib::RefPtr<Gtk::Builder> builder );
        ~DialogWindow();

        void Show( const std::string& text ) const;
        static void SetGlobal( DialogWindow& dialogLogic );
        static void ShowGlobal( const std::string& text );
        static void HideGlobal();

    private:
        
        Gtk::Dialog* window;
        Gtk::Label* text;
        Gtk::Button* button;

        static DialogWindow* instance;

        void OnButtonClicked();
};

#endif