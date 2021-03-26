#include "examplewindow.h"
#include <gtkmm/application.h>


//g++ main2.cpp examplewindow.cc examplewindow.h -o ex `pkg-config --cflags --libs gtkmm-3.0 gladeui-2.0`


int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  ExampleWindow window;

  //Shows the window and returns when it is closed.
  return app->run(window);
}
