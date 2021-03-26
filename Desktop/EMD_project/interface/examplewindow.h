#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:

  ExampleWindow();
  virtual ~ExampleWindow();

private:
  //Override default signal handler:
  bool on_key_release_event(GdkEventKey* event) override;

  bool entryKeyRelease(GdkEventKey* event);
  bool gridKeyRelease(GdkEventKey* event);
  bool windowKeyReleaseBefore(GdkEventKey* event);
  bool windowKeyRelease(GdkEventKey* event);

  Gtk::Grid m_container;

  Gtk::Label m_label;
  Gtk::Entry m_entry;
  Gtk::CheckButton m_checkbutton_can_propagate;
};

#endif //GTKMM_EVENT_PROPAGATION_H
