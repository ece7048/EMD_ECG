////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef BW_FILTER_H
#define BW_FILTER_H


#include <stdio.h>
#include <vector>
#include <list>
#include <memory>
#include <math.h>
#include <algorithm>
#include "store_IMF.h"
#include "store_IMF.cpp"
#include "define.h"

template <class T>
class BW_filter: public store_IMF<T>
{

public:
BW_filter(std::vector<T> X_signal, std::vector<T> time, std::shared_ptr<store_IMF<T>> &IMF);//constructor
BW_filter(); // constructor
~BW_filter(){estim_b_i.clear(); c_X_signal.clear(); c_time.clear(); filter_signal.clear(); b_i.clear(); c_i.clear(); h_i.clear(); c_omega=0; c_M=0; c_j=0;}; // destructor
// get set functions
   inline std::vector<T> get_est_BW(){return estim_b_i;};  //get the array of interest
     
private:
std::vector<T> estim_b_i;
std::vector<T> c_X_signal;
std::vector<T> c_time;
std::vector<T> filter_signal;
std::vector<T> b_i;
std::vector<T> c_i;
std::vector<T> h_i;
std::shared_ptr<store_IMF<T>> IMF_obj;
T c_omega;
int c_M;
T c_j;
//functions private
void compute_signal();
void cycle_convolution();
T variance_b();
void sinc_low_pass(int k);
bool test_critirio(T var, T var_1); 
};

#endif
