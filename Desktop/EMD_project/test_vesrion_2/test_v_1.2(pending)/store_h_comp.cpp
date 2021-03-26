////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#include "store_h_comp.h"
#include <iostream>
#include <cmath>


///////////////////////////////////////////////////////////////////////
//Class: store_h_comp
//Function: store_h_comp, ~store_h_comp
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
store_h_comp<T>::store_h_comp(std::vector<T> h_k){ 
set_h(h_k); 
}//end function
template<class T>
store_h_comp<T>::store_h_comp(){}



///////////////////////////////////////////////////////////////////////
//Class: store_h_comp
//Function: set_h
//Abstract: set the h component at list of vector resize list to remain fix 2 size only 
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void store_h_comp<T>::set_h(std::vector<T> h){ 
h_component.push_back(h); //set in list data
if (h_component.size()==3){h_component.pop_front();};
//debug//////////////////////////////////////////
std::cout<<h_component.size()<<"SIZE_H_LIST\n";
////////////////////////////////////////////////
if (h_component.size()==2){compute_SD();} 
else{set_SD(3);}
}//end function


///////////////////////////////////////////////////////////////////////
//Class: store_h_comp
//Function: store_h_comp_SD
//Abstract: compute the SD of h components of IMF canditate 
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void store_h_comp<T>::compute_SD(){
// Initialize section
c_h_k_1=h_component.front();
c_h_k=h_component.back();
T d_h_k[c_h_k.size()];//difene array of vector 
std::copy(c_h_k.begin(),c_h_k.end(),d_h_k); //copy in array the vector
T d_h_k_1[c_h_k_1.size()];//difene array of vector 
std::copy(c_h_k_1.begin(),c_h_k_1.end(),d_h_k_1); //copy in array the vector
T sum=0;
c_SD=0;
int o=0; // counter
// Compute h component
while(o<c_h_k.size()){
sum = ((pow(std::abs(d_h_k_1[o]-d_h_k[o]),2))/(pow(d_h_k_1[o],2)));
if(d_h_k_1[o]==0){sum=0;/*sum=d_h_k[o]*/;};
if(d_h_k[o]==0 && d_h_k_1[o]==0){sum=0;};
c_SD+=sum;
o++;
//debug//////////////////////////////////////////////////////////////////////////////////////////////////////
//std::cout<<sum<<" <--- sum-SD\n";
//std::cout<<c_SD<<" <--- SD\n";
//std::cout<<d_h_k[o]<<" <--d_h_k[o]\n";
//std::cout<<d_h_k_1[o]<<" <--- d_h_k_1[o]\n";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
}//end while
// store mean value
}//end function




