////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef IMF_COMPUTE_H
#define IMF_COMPUTE_H


#include <stdio.h>
#include <vector>
#include <list>
//#include "define.h"


template <class T>
class IMF_compute
{

public:
IMF_compute(std::vector<T> signal, std::vector<T> time); //initialize constructor
IMF_compute(); // constructor
~IMF_compute(); // destructor
//functions public
void run();
// get set functions
   inline std::vector<T> get_IMF(){return IMF;};  //get the array of interest
 inline std::vector<T> get_IMF_k(){return IMF_k_1;};  //test get delete in real application
   inline void set(std::vector<T> signal, std::vector<T> time){c_X=signal;c_T=time;}; //store the array of interest in a vector
   inline std::list<std::vector<T>> get_b_spline(){return bS_l;};  //get the array of interest

private:
std::vector<T> c_T;
std::vector<T> c_X;
std::vector<T> IMF;
std::vector<T> IMF_k_1;//test vector delete in real application
std::list< std::vector<T> >  bS_l;
T c_SD;
};

#endif
