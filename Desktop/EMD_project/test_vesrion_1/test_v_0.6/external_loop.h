///////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef EXTERNAL_LOOP_H
#define EXTERNAL_LOOP_H


#include <stdio.h>
#include <vector>
#include <list>
#include "store_IMF.h"
#include "compute_residue.h"
#include "store_IMF.cpp"
#include "compute_residue.cpp"
#include "extrema_detect.h"
#include "IMF_compute.h"
#include "IMF_compute.cpp"
//#include "define.h"
//#define L_data 100

template <class T>
class external_loop : public store_IMF<T>
{

public:
external_loop(std::vector<T> c_signal, std::vector<T> c_time) ; //initialize constructor
external_loop(); // constructor
~external_loop(); // destructor
//functions public
void run();
// get set functions
   inline std::shared_ptr<store_IMF<T>> get_IMF_store_obj(){return IMF_obj_external_loop;};  //get the array of interest
   //inline void set(){}; //store the array of interest in a vector
   
private:
std::vector<T> signal;
std::vector<T> time;
std::shared_ptr<store_IMF<T>> IMF_obj_external_loop;
};

#endif
