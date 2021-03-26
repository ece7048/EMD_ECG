////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////

#include "compute_components.h"
#include <iostream>



///////////////////////////////////////////////////////////////////////
//Class: compute_components
//Function: compute_components, ~compute_components
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
compute_components<T>::compute_components(std::list< std::vector<T> > b_spline,std::vector<T> Xo_signal) : c_b_spline(b_spline), c_Xo_signal(Xo_signal){compute_mean_value(); compute_h_comp();}



///////////////////////////////////////////////////////////////////////
//Class: compute_components
//Function: compute_mean_value
//Abstract: compute the mean value of the two extrema
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void compute_components<T>::compute_mean_value(){
// Initialize section
c_b_spline_min=c_b_spline.front();
c_b_spline_max=c_b_spline.back();
T d_mean_value[c_b_spline_max.size()];//difene array of vector 
T maximum_array[c_b_spline_min.size()];//difene array of vector 
std::copy(c_b_spline_max.begin(),c_b_spline_max.end(),maximum_array); //copy in array the vector
T minimum_array[c_b_spline_min.size()];//difene array of vector 
std::copy(c_b_spline_min.begin(),c_b_spline_min.end(),minimum_array); //copy in array the vector
int i=0; // counter
// Compute mean value
while(i<c_b_spline_max.size()){
d_mean_value[i]=(maximum_array[i]+minimum_array[i])/2;
i++;
}//end while
// store mean value
c_mean_value.insert(c_mean_value.end(),&d_mean_value[0],&d_mean_value[L_data]);
}//end function


///////////////////////////////////////////////////////////////////////
//Class: compute_components
//Function: compute_h_comp
//Abstract: compute the h components of IMF canditate 
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void compute_components<T>::compute_h_comp(){
// Initialize section
T d_mean_value_array[c_mean_value.size()];
std::copy(c_mean_value.begin(),c_mean_value.end(),d_mean_value_array); //copy in array the vector
T d_h_comp[c_Xo_signal.size()]; //difene array of vector 
T Xo_signal_array[c_Xo_signal.size()];//difene array of vector 
std::copy(c_Xo_signal.begin(),c_Xo_signal.end(),Xo_signal_array); //copy in array the vector
int o=0; // counter
// Compute h component
while(o<c_mean_value.size()){
d_h_comp[o]=(Xo_signal_array[o]-d_mean_value_array[o]);
o++;
//debug//////////////////////////////////////////////////////////////////////////////////////////////////////
//std::cout<<Xo_signal_array[o]<<" <--- Xo_signal\n";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//debug//////////////////////////////////////////////////////////////////////////////////////////////////////
//std::cout<<d_h_comp[o]<<" <--- h_comp\n";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//debug///////////////////////////////////////////////////
//std::cout<<d_mean_value_array[o]<<" <--- mean_value\n";
////////////////////////////////////////////////////////
}//end while
// store mean value
c_h_comp.insert(c_h_comp.end(),&d_h_comp[0],&d_h_comp[L_data]);
}//end function



