// File: main.cpp

#include "mainwindow.h"
#include <gtkmm/application.h>

int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create();
    
    MainWindow mainwindow;

    //Shows the window and returns when it is closed.
    return app->run(mainwindow);
  
}

