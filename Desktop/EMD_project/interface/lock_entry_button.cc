#include "lock_entry_button.h"
#include <iostream>

lock_entry_button::lock_entry_button()
{
  add(m_container);
  set_title("Event Propagation");
  set_border_width(10);

  m_label.set_label("A label");
  m_checkbutton_can_propagate.set_label("Can Propagate");
  m_checkbutton_can_propagate.set_active();

  // Main Container
  m_container.set_orientation(Gtk::ORIENTATION_VERTICAL);
  m_container.add(m_label);
  m_container.add(m_entry);
  m_container.add(m_checkbutton_can_propagate);

  // Events
  add_events(Gdk::KEY_RELEASE_MASK);

  m_entry.signal_key_release_event().connect(
    sigc::mem_fun(*this, &ExampleWindow::entryKeyRelease));

  m_container.signal_key_release_event().connect(
    sigc::mem_fun(*this, &ExampleWindow::gridKeyRelease));

  // Called before the default event signal handler.
  signal_key_release_event().connect(
    sigc::mem_fun(*this, &ExampleWindow::windowKeyReleaseBefore), false);

  // Called after the default event signal handler.
  signal_key_release_event().connect(
    sigc::mem_fun(*this, &ExampleWindow::windowKeyRelease));

  show_all_children();
}

//By changing the return value we allow, or don't allow, the event to propagate to other elements.
bool lock_entry_button::entryKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Entry" << std::endl;

  if(m_checkbutton_can_propagate.get_active())
  {
    return false;
  }

  return true;
}

bool lock_entry_button::gridKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Grid" << std::endl;

  //Let it propagate:
  return false;
}

bool lock_entry_button::windowKeyReleaseBefore(GdkEventKey* /* event */ )
{
  std::cout << "Window before" << std::endl;
  return false;
}

bool lock_entry_button::on_key_release_event(GdkEventKey* key_event)
{
  std::cout << "Window overridden" << std::endl;

  // call base class function (to get the normal behaviour)
  return Gtk::Window::on_key_release_event(key_event);
}

// This will set the entry's text in the label, every time a key is pressed.
bool lock_entry_button::windowKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Window after";

  //checking if the entry is on focus, otherwise the label would get changed by pressing keys
  //on the window (when the entry is not on focus), even if m_checkbutton_can_propagate wasn't active
  if(m_entry.has_focus())
  {
    m_label.set_text(m_entry.get_text());
    std::cout << ", " << m_entry.get_text();
  }
  std::cout << std::endl;

  return true;
}

ExampleWindow::~ExampleWindow()
{
}
