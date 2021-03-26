////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef SIGNALS_H
#define SIGNALS_H

#include <stdio.h>
#include <iostream>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>

template <class T>
class Signals: public Gtk::Window
{

public:

Signals(){};

   
void store_value(T value){std::cout<<value<<" GIA PAME";}
T value;

};

#endif


