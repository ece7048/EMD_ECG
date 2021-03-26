////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include "main_run.h"
//#include "define.hpp"
//g++ main.cpp -o my `pkg-config --cflags --libs gtkmm-3.0 gladeui-2.0`

//Global variables
typedef double T;
extern int change_phase_lock;
extern int start_reading; 
extern int L_data; 
extern std::string ECG_data;
// B_spline parameters
extern int N_sample;
//extern const int N_sample=250;
extern double increase_value;
extern double cub_coef_a;
extern double cub_coef_b;
extern double cub_coef_c;
extern int type_interpolation;
extern int MAX_LOOP;
//extrema define parameters
extern std::string PATH_OF_TXT; 
extern double ACCUR;
extern int Critirio; 
//internal loop parameter 
extern int MAX_INTLOOP;
extern double SDif1;
extern double SDif2;
//BW filter parameters
extern double FREQ;
extern double M_FREQ;
extern double VAR_ACCUR;
extern double GAIN; 
extern int Shift_time;
extern double Shift_value; 
extern int FILTER_TIME; 
////////////////////////////////////////////////////////////////


Gtk::Window* pWindow = nullptr;

static
void on_button_clicked()
{  if(pWindow) {pWindow->hide();} //hide() will cause main::run() to end.
}

void lock_unlock(Gtk::Button* pButton,Gtk::Entry* Entry){
if(pButton->get_label()=="Unlock"){change_phase_lock=0;};
if(pButton->get_label()=="Lock"){change_phase_lock=1;};
switch(change_phase_lock) {
case 1: pButton->set_label("Unlock");Entry->show(); Entry->set_visibility();change_phase_lock=0; break;
case 0: pButton->set_label("Lock");Entry->hide(); change_phase_lock=1; break;
}
}

void lock_unlock2(Gtk::Button* pButton,Gtk::ComboBoxText* pcombo){
if(pButton->get_label()=="Unlock"){change_phase_lock=0;};
if(pButton->get_label()=="Lock"){change_phase_lock=1;};
switch(change_phase_lock) {
case 1: pButton->set_label("Unlock");pcombo->show(); change_phase_lock=0; break;
case 0: pButton->set_label("Lock");pcombo->hide(); change_phase_lock=1; break;
}
}

void on_entry_changed(Gtk::Entry* pcombo)
{ 
  auto entry = pcombo->get_text();
   if (pcombo->get_name()=="1")
    {
    std::cout <<"ID1= " << entry << std::endl;
    ECG_data=entry;    
    }
   if (pcombo->get_name()=="3")
    {
    std::cout <<"ID3= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     int st = atof(UStringToCharArray);
     start_reading=st;
    }
   if (pcombo->get_name()=="5")
    {
    std::cout <<"ID5= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double cca = atof(UStringToCharArray);
    cub_coef_a=cca;
    }
   if (pcombo->get_name()=="6")
    {
    std::cout <<"ID6= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double ccb = atof(UStringToCharArray);
    cub_coef_b=ccb;
    }
   if (pcombo->get_name()=="7")
    {
    std::cout <<"ID7= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double ccc = atof(UStringToCharArray);
    cub_coef_c=ccc;
    }
   if (pcombo->get_name()=="8")
    {
    std::cout <<"ID8= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double iv = atof(UStringToCharArray);
    increase_value=iv;
    }
   if (pcombo->get_name()=="9")
    {
    std::cout <<"ID9= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     int poe = atof(UStringToCharArray);
    //POINTS_OF_EVAL=poe;
    }
   if (pcombo->get_name()=="10")
    {
    std::cout <<"ID10= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double a = atof(UStringToCharArray);
    ACCUR=a;
    }
   if (pcombo->get_name()=="11")
    {
    std::cout <<"ID11= " << entry << std::endl;
    PATH_OF_TXT=entry;
    }
   if (pcombo->get_name()=="12")
    {
    std::cout <<"ID12= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     int ml = atof(UStringToCharArray);
    MAX_LOOP=ml;
    }
   if (pcombo->get_name()=="13")
    {
    std::cout <<"ID13= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     int mi = atof(UStringToCharArray);
    MAX_INTLOOP=mi;
    }
   if (pcombo->get_name()=="14")
    {
    std::cout <<"ID14= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double sd1 = atof(UStringToCharArray);
    SDif1=sd1;
    }
   if (pcombo->get_name()=="15")
    {
    std::cout <<"ID15= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double sd2 = atof(UStringToCharArray);
    SDif2=sd2;    
    }
   if (pcombo->get_name()=="16")
    {
    std::cout <<"ID16= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double f = atof(UStringToCharArray);
    FREQ=f;
    }
   if (pcombo->get_name()=="17")
    {
    std::cout <<"ID17= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double mf = atof(UStringToCharArray);
    M_FREQ=mf;
    }
   if (pcombo->get_name()=="18")
    {
    std::cout <<"ID18= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double va = atof(UStringToCharArray);
    VAR_ACCUR=va;
    }
     if (pcombo->get_name()=="19")
    {
    std::cout <<"ID19= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double ga = atof(UStringToCharArray);
    GAIN=ga;
    }
     if (pcombo->get_name()=="20")
    {
    std::cout <<"ID20= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     int st = atof(UStringToCharArray);
    Shift_time=st;
    }
     if (pcombo->get_name()=="21")
    {
    std::cout <<"ID21= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     double va = atof(UStringToCharArray);
    Shift_value=va;
    }
     if (pcombo->get_name()=="22")
    {
    std::cout <<"ID22= " << entry << std::endl;
     const char * UStringToCharArray = entry.c_str(); 
     int fp = atof(UStringToCharArray);
    FILTER_TIME=fp;
    }
}

void on_entry_changed2(Gtk::ComboBoxText* pcombo)
{

   if (pcombo->get_name()=="combotext1")
    {
    
    std::cout <<"CO1= " << pcombo->get_active_text() << std::endl;
    if(pcombo->get_active_text()=="linear"){type_interpolation=1;};  
    if(pcombo->get_active_text()=="b-spline"){type_interpolation=0;}; 
    if(pcombo->get_active_text()=="parametric"){type_interpolation=1;};  
    }
   if (pcombo->get_name()=="combotext2")
    {
    std::cout <<"CO2= " << pcombo->get_active_text() << std::endl;
    if(pcombo->get_active_text()=="extrema_difference"){Critirio=1;}; 
    if(pcombo->get_active_text()=="average_difference"){Critirio=2;}; 
    }

   if (pcombo->get_name()=="combotext3")
    {
    
    std::cout <<"CO3= " << pcombo->get_active_text() << std::endl;
    if(pcombo->get_active_text()=="10"){L_data=10;};  
    if(pcombo->get_active_text()=="25"){L_data=25;}; 
    if(pcombo->get_active_text()=="50"){L_data=50;};  
    if(pcombo->get_active_text()=="100"){L_data=100;}; 
    if(pcombo->get_active_text()=="150"){L_data=150;};  
    if(pcombo->get_active_text()=="200"){L_data=200;}; 
    if(pcombo->get_active_text()=="250"){L_data=250;};  
    if(pcombo->get_active_text()=="300"){L_data=300;}; 
    if(pcombo->get_active_text()=="350"){L_data=350;};  
    if(pcombo->get_active_text()=="400"){L_data=400;}; 
    if(pcombo->get_active_text()=="450"){L_data=450;};  
    if(pcombo->get_active_text()=="500"){L_data=500;};  
    }
   if (pcombo->get_name()=="combotext4")
    {
    
    std::cout <<"CO4= " << pcombo->get_active_text() << std::endl;
    if(pcombo->get_active_text()=="10"){N_sample=10;};  
    if(pcombo->get_active_text()=="25"){N_sample=25;}; 
    if(pcombo->get_active_text()=="50"){N_sample=50;};  
    if(pcombo->get_active_text()=="100"){N_sample=100;}; 
    if(pcombo->get_active_text()=="150"){N_sample=150;};  
    if(pcombo->get_active_text()=="200"){N_sample=200;}; 
    if(pcombo->get_active_text()=="250"){N_sample=250;};  
    if(pcombo->get_active_text()=="300"){N_sample=300;}; 
    if(pcombo->get_active_text()=="350"){N_sample=350;};  
    if(pcombo->get_active_text()=="400"){N_sample=400;}; 
    if(pcombo->get_active_text()=="450"){N_sample=450;};  
    if(pcombo->get_active_text()=="500"){N_sample=500;};   
    }

   
}

void run_on_click( std::shared_ptr< main_run> m_r)
{
  m_r->run();
}

void stop_on_click(  std::shared_ptr< main_run> m_r,Gtk::Entry* pEntry)
{
  m_r->~main_run();
     pEntry->set_text("6");
     FREQ=6;
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
  std::shared_ptr< main_run> m_r ;//=std::make_shared<main_run>;
  refBuilder->get_widget("EMD parameters", pWindow);
  if(pWindow)
  {

    //fix demensions
    pWindow->resize(400, 400); // find the correct order...

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
    {   //set default value freq
       refBuilder->get_widget("entry16",pEntry);
      pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(stop_on_click),m_r,pEntry));
     
     
     
    }


    refBuilder->get_widget("run", pButton);
    if(pButton)
    {  
     //hide all the entry levels
      //refBuilder->get_widget("spin",pspin);
      //if(pspin)      
      //{ 
      //pButton->signal_clicked().connect(sigc::mem_fun(*pspin, &Gtk::Spinner::start));
      pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(run_on_click),m_r));
       //}
     }
 
    //Lock buttons Events

     refBuilder->get_widget("lock1", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry1",pEntry);
     //Default value
     pEntry->set_text("/home/mamalakis/ECG_partwo/EMD_project/collection_of_data/experimental/filtered.txt");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("1");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

 /*    refBuilder->get_widget("lock2", pButton);
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
   */ 
    refBuilder->get_widget("lock3", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry3",pEntry);
     //Default value
     pEntry->set_text("800");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("3");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }

 /*    refBuilder->get_widget("lock4", pButton);
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
*/
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
     pEntry->set_text("0");
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
     pEntry->set_text("600");
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
     pEntry->set_text("0.5");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
      //Connect signal handlers:
     pEntry->set_name("14");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
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
    refBuilder->get_widget("lock21", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry19",pEntry);
     //Default value
     pEntry->set_text("1");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handlers:
     pEntry->set_name("19");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }
    refBuilder->get_widget("lock22", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry20",pEntry);
     //Default value
     pEntry->set_text("0");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handlers:
     pEntry->set_name("20");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }
    refBuilder->get_widget("lock23", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry21",pEntry);
     //Default value
     pEntry->set_text("0");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handlers:
     pEntry->set_name("21");
     pEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
     pEntry->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed),pEntry) );
     }
    refBuilder->get_widget("lock24", pButton);
    if(pButton)
    {pButton->set_label("Lock");
     refBuilder->get_widget("entry22",pEntry);
     //Default value
     pEntry->set_text("1");
     pEntry->hide();
     pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock),pButton,pEntry));
     //Connect signal handlers:
     pEntry->set_name("22");
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
    refBuilder->get_widget("lock2", pButton);
    if(pButton)
    {pButton->set_label("Lock");
      refBuilder->get_widget("combo4",tcombo);
      tcombo->hide();
      pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock2),pButton,tcombo));
      if(tcombo)
      {
       //Fill the combo:
       tcombo->append("10");
       tcombo->append("25");
       tcombo->append("50");
       tcombo->append("100");
       tcombo->append("150");
       tcombo->append("200");
       tcombo->append("250");
       tcombo->append("300");
       tcombo->append("350");
       tcombo->append("400");
       tcombo->append("450");
       tcombo->append("500");
       tcombo->set_active(11);
       //Connect signal handlers:
       tcombo->set_name("combotext3");
        // The Entry shall receive focus-out events.
        tcombo->add_events(Gdk::FOCUS_CHANGE_MASK);
        // Alternatively you can connect to m_Combo.signal_changed().
        tcombo->signal_changed().connect(sigc::bind(sigc::ptr_fun(on_entry_changed2),tcombo) );
      }//end if
     }//end if

    refBuilder->get_widget("lock4", pButton);
    if(pButton)
    {pButton->set_label("Lock");
      refBuilder->get_widget("conbo3",tcombo);
      tcombo->hide();
      pButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(lock_unlock2),pButton,tcombo));
      if(tcombo)
      {
       //Fill the combo:
       tcombo->append("10");
       tcombo->append("25");
       tcombo->append("50");
       tcombo->append("100");
       tcombo->append("150");
       tcombo->append("200");
       tcombo->append("250");
       tcombo->append("300");
       tcombo->append("350");
       tcombo->append("400");
       tcombo->append("450");
       tcombo->append("500");
       tcombo->set_active(11);
       //Connect signal handlers:
       tcombo->set_name("combotext4");
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
