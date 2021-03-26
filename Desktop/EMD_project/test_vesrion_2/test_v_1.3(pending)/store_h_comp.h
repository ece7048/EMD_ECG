////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef STORE_H_COMP_H
#define STORE_H_COMP_H


#include <stdio.h>
#include <vector>
#include <list>
#include "define.h"


//////////////////////////////////////////////////////////////////////////////
/////////////////////store_h_components///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template <class T>
class store_h_comp
{

public:
store_h_comp(std::vector<T> h_k); // constructor 
store_h_comp(); // constructor
~store_h_comp(){c_h_k.clear(); c_h_k_1.clear(); h_component.clear();}; // destructor
// get set functions
inline T get_SD(){return c_SD;};  //get the T of interest
inline std::vector<T> get_stored_h(){return c_h_k;};  //get the vector of interest
inline void set_SD(T SD){c_SD=SD;};//set the vector of interest
void set_h(std::vector<T> h);//set the vector of interest in list
//set functions
private:
std::list< std::vector<T> > h_component;
std::vector<T> c_h_k;
std::vector<T> c_h_k_1;
T c_SD ;
//functions  
void compute_SD();  

};

#endif
