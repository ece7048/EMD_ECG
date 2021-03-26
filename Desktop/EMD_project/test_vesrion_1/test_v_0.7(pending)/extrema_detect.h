////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef EXTREMA_DETECT_H
#define EXTREMA_DETECT_H


#include <stdio.h>
#include <vector>
//#include "define.hpp"
//#define LENGTH_DATA 250
//#define POINTS_OF_EVAL 2

//////////////////////////////////////////////////////////////////////////////
/////////////////////CLASS: extrema_detect///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

enum EXTREMA_KIND {
MAX_VALUE=0,
MIN_VALUE=1,
MAX_TIME=2,
MIN_TIME=3
};

template <class T>
class extrema_detect
{

public:
extrema_detect(); 
extrema_detect(T xin[],T time[]); // constractor which take the ecg signal (xin) and the time (time)
~extrema_detect(){minimum.clear(); maximum.clear(); minimum_time.clear(); maximum_time.clear();}; // destructor
// get set functions
     std::vector<T> get(EXTREMA_KIND E);  //get the array of interest
     void set(EXTREMA_KIND E, T extrema_data[], int size_extrema);  //store the array of interest in a vector
     int test_point();
protected:
T forward_differentiation(T x[], T t[]);  // first order 

private:
std::vector<T> minimum;
std::vector<T> maximum;
std::vector<T> minimum_time;
std::vector<T> maximum_time;

//////////////////////////////////////TODO_SECT////////////////////////////////////////////////////////
//TODO1 add a backward or middle estimation of differentiation for better dettection of slope
// TODO2 set the get,set function in protected area only for inheretate classes 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////


};
//#undef LENGTH_DATA
//#undef POINTS_OF_EVAL
#endif
