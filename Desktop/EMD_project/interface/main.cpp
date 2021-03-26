#include <gtkmm.h>
#include <iostream>
#include "define.h"


//g++ main.cpp -o my `pkg-config --cflags --libs gtkmm-3.0 gladeui-2.0`
typedef double T;
extern int change_phase=1;

Gtk::Window* pWindow = nullptr;

static
void on_button_clicked()
{  if(pWindow) {pWindow->hide();} //hide() will cause main::run() to end.
}

void lock_unlock(Gtk::Button* pButton,Gtk::Entry* Entry){
if(pButton->get_label()=="Unlock"){change_phase=0;};
if(pButton->get_label()=="Lock"){change_phase=1;};
switch(change_phase) {
case 1: pButton->set_label("Unlock");Entry->show(); Entry->set_visibility();change_phase=0; break;
case 0: pButton->set_label("Lock");Entry->hide(); change_phase=1; break;
}
}

void lock_unlock2(Gtk::Button* pButton,Gtk::ComboBoxText* pcombo){
if(pButton->get_label()=="Unlock"){change_phase=0;};
if(pButton->get_label()=="Lock"){change_phase=1;};
switch(change_phase) {
case 1: pButton->set_label("Unlock");pcombo->show(); change_phase=0; break;
case 0: pButton->set_label("Lock");pcombo->hide(); change_phase=1; break;
}
}

void on_entry_changed(Gtk::Entry* pcombo)
{ 
  auto entry = pcombo->get_text();
   if (pcombo->get_name()=="1")
    {
    std::cout <<"ID1= " << entry << std::endl;
    ECG_data entry;    
    }
   if (pcombo->get_name()=="2")
    {
    std::cout <<"ID2= " << entry << std::endl;
    L_data entry;
    }
   if (pcombo->get_name()=="3")
    {
    std::cout <<"ID3= " << entry << std::endl;
     start_reading entry;
    }
   if (pcombo->get_name()=="4")
    {
    std::cout <<"ID4= " << entry << std::endl;
    N_sample entry;
    }
   if (pcombo->get_name()=="5")
    {
    std::cout <<"ID5= " << entry << std::endl;
    cub_coef_a entry;
    }
   if (pcombo->get_name()=="6")
    {
    std::cout <<"ID6= " << entry << std::endl;
    cub_coef_b entry;
    }
   if (pcombo->get_name()=="7")
    {
    std::cout <<"ID7= " << entry << std::endl;
    cub_coef_c entry;
    }
   if (pcombo->get_name()=="8")
    {
    std::cout <<"ID8= " << entry << std::endl;
    increase_value entry;
    }
   if (pcombo->get_name()=="9")
    {
    std::cout <<"ID9= " << entry << std::endl;
    POINTS_OF_EVAL entry;
    }
   if (pcombo->get_name()=="10")
    {
    std::cout <<"ID10= " << entry << std::endl;
    ACCUR entry;
    }
   if (pcombo->get_name()=="11")
    {
    std::cout <<"ID11= " << entry << std::endl;
    PATH_OF_TXT entry;
    }
   if (pcombo->get_name()=="12")
    {
    std::cout <<"ID12= " << entry << std::endl;
    MAX_LOOP entry;
    }
   if (pcombo->get_name()=="13")
    {
    std::cout <<"ID13= " << entry << std::endl;
    MAX_INTLOOP entry;
    }
   if (pcombo->get_name()=="14")
    {
    std::cout <<"ID14= " << entry << std::endl;
    SDif1 entry;
    }
   if (pcombo->get_name()=="15")
    {
    std::cout <<"ID15= " << entry << std::endl;
    SDif2 entry;    
    }
   if (pcombo->get_name()=="16")
    {
    std::cout <<"ID16= " << entry << std::endl;
    FREQ entry;
    }
   if (pcombo->get_name()=="17")
    {
    std::cout <<"ID17= " << entry << std::endl;
    M_FREQ entry;
    }
   if (pcombo->get_name()=="18")
    {
    std::cout <<"ID18= " << entry << std::endl;
    VAR_ACCUR entry;
    }
}

void on_entry_changed2(Gtk::ComboBoxText* pcombo)
{

   if (pcombo->get_name()=="combotext1")
    {
    
    std::cout <<"CO1= " << pcombo->get_active_text() << std::endl;
    type_interpolation pcombo->get_active_text();   
    }
   if (pcombo->get_name()=="combotext2")
    {
    std::cout <<"CO2= " << pcombo->get_active_text() << std::endl;
    Critirio pcombo->get_active_text();
    }

   
}

void on_entry_activate(Gtk::ComboBoxText* pcombo)
{
  auto entry = pcombo->get_entry();
  if (entry)
  {
    std::cout << "ID= " << entry->get_text() << std::endl;
  }
}


int main (int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");


Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("interface.glade");

  // Prefer dark theme
  auto settings = Gtk::Settings::get_default();
  settings->property_gtk_application_prefer_dark_theme().set_value(true);


  //Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("interface.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  //Get the GtkBuilder-instantiated Dialog:

  refBuilder->get_widget("EMD parameters", pWindow);
  if(pWindow)
  {

    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    Gtk::Button* pButton = nullptr;
    Gtk::Entry* pEntry = nullptr;
    Gtk::ComboBoxText* tcombo=nullptr;
    Gtk::Spinner* pspin=nullptr;
    Gtk::Label m_label;
    //Signals<T>* signal=nullptr;

    //Button Events
    refBuilder->get_widget("quit", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }

    refBuilder->get_widget("stop", pButton);
    if(pButton)
    {   refBuilder->get_widget("spin",pspin);
    
     pButton->signal_clicked().connect(sigc::mem_fun(*pspin, &Gtk::Spinner::stop));
       
    //hide all the entry levels
    }


    refBuilder->get_widget("run", pButton);
    if(pButton)
    {
     
       
     //hide all the entry levels
    
      refBuilder->get_widget("spin",pspin);
      if(pspin)      
      {
      pButton->signal_clicked().connect(sigc::mem_fun(*pspin, &Gtk::Spinner::start));
       }
     }
 
    //Lock buttons Events

     refBuilder->get_widget("lock1", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry1",pEntry);
     //Default value
     pEntry->set_text("/home/mamalakis/Desktop/EMD_project/test_vesrion_2/experimental_data/filtered.dat");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("1");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock2", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry2",pEntry);
     //Default value
     pEntry->set_text("250");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("2");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }
    
    refBuilder->get_widget("lock3", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry3",pEntry);
     //Default value
     pEntry->set_text("0");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("3");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock4", pButton);
    if(pButton)
    {pButton->set_label("Lock");

     refBuilder->get_widget("entry4",pEntry);
     //Default value
     pEntry->set_text("250");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("4");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock6", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry5",pEntry);
     //Default value
     pEntry->set_text("1/6");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("5");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock7", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry6",pEntry);
     //Default value
     pEntry->set_text("2/3");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("6");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock8", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry7",pEntry);
     //Default value
     pEntry->set_text("1/2");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("7");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock9", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry8",pEntry);
     //Default value
     pEntry->set_text("0.01");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handlers:
     pEntry->set_name("8");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock10", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry9",pEntry);
     //Default value
     pEntry->set_text("2");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("9");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock12", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry10",pEntry);
     //Default value
     pEntry->set_text("0.000001");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("10");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock13", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry11",pEntry);
     //Default value
     pEntry->set_text("/home/mamalakis/Desktop/test.txt");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("11");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock14", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry12",pEntry);
     //Default value
     pEntry->set_text("15");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("12");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock15", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry13",pEntry);
     //Default value
     pEntry->set_text("15");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("13");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock16", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry14",pEntry);
     //Default value
     pEntry->set_text("0.3");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("14");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     auto entry = pEntry->get_text();
     SDif1 entry;
     }

     refBuilder->get_widget("lock17", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry15",pEntry);
     //Default value
     pEntry->set_text("0.1");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handler
     pEntry->set_name("15");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }
     
    refBuilder->get_widget("lock18", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry16",pEntry);
     //Default value
     pEntry->set_text("0.8");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("16");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock19", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry17",pEntry);
     //Default value
     pEntry->set_text("20");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
    //Connect signal handlers:
     pEntry->set_name("17");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

     refBuilder->get_widget("lock20", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry18",pEntry);
     //Default value
     pEntry->set_text("0.0000000001");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handlers:
     pEntry->set_name("18");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

//combo_text_button

    refBuilder->get_widget("lock5", pButton);
    if(pButton)
    {pButton->set_label("Lock");
      refBuilder->get_widget("combo",tcombo);
      tcombo->hide();
      pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock2),pButton,tcombo));
      if(tcombo)
      {
       //Fill the combo:
       tcombo->append("linear");
       tcombo->append("parametric");
       tcombo->append("b-spline");
       tcombo->set_active(0);
       //Connect signal handlers:
       tcombo->set_name("combotext1");
        // The Entry shall receive focus-out events.
        tcombo->add_events(Gdk::FOCUS_CHANGE_MASK);
        // Alternatively you can connect to m_Combo.signal_changed().
        tcombo->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed2),tcombo) );
      }//end if
     }//end if

    refBuilder->get_widget("lock11", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("combo2",tcombo);
     tcombo->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock2),pButton,tcombo));
     if(tcombo)
     {
      //Fill the combo:
      tcombo->append("extrema_difference");
      tcombo->append("average_difference");
      tcombo->set_active(1);
      //Connect signal handlers:
      tcombo->set_name("combotext2");
     //auto entry=tcombo->get_entry();
        // The Entry shall receive focus-out events.
        tcombo->add_events(Gdk::FOCUS_CHANGE_MASK);
        // Alternatively you can connect to m_Combo.signal_changed().
        tcombo->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed2),tcombo) );
       }//end if
    }//end if

// RUN window

app->run(*pWindow);
}//edn if window

delete pWindow;

return 0;
}
