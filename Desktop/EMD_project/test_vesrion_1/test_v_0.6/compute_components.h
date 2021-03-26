////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef COMPUTE_COMPONENTS_H
#define COMPUTE_COMPONENTS_H


#include <stdio.h>
#include <vector>
#include <list>
//#include "define.h"

//////////////////////////////////////////////////////////////////////////////
/////////////////////compute_components///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template <class T>
class compute_components
{

public:
compute_components(); 
compute_components(std::list< std::vector<T> > b_spline,std::vector<T> Xo_signal); // constractor 
~compute_components(){
c_mean_value.clear();
c_h_comp.clear();
c_Xo_signal.clear();
c_b_spline_min.clear() ;
c_b_spline_max.clear() ;
c_b_spline.clear();
c_SD=0 ;}; // destructor
// get set functions
inline T get_SD(){return c_SD;};  //get the T of interest
inline std::vector<T> get_h_comp(){return c_h_comp;};  //get the vector of interest
//set functions
private:
std::vector<T> c_mean_value;
std::vector<T> c_h_comp;
std::vector<T> c_Xo_signal;
std::vector<T> c_b_spline_min ;
std::vector<T> c_b_spline_max ;
std::list< std::vector<T> > c_b_spline;
T c_SD ;
//functions
inline std::vector<T> get_mean_value(){return c_mean_value;};  //get the vector of interest
inline void set_h_comp(std::vector<T> h_comp){c_h_comp=h_comp;};//set the vector of interest
inline void set_SD(T SD){c_SD=SD;};//set the vector of interest
void compute_mean_value();
void compute_h_comp();    
//inline void set_mean_value(std::vector<T> mean_value):c_mean_value(mean_value){};
};

#endif
