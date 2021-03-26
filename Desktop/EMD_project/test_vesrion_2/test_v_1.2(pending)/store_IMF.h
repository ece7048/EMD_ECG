////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef STORE_IMF_H
#define STORE_IMF_H


#include <stdio.h>
#include <vector>
#include <list>




//////////////////////////////////////////////////////////////////////////////
/////////////////////store_h_components///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template <class T>
class store_IMF
{

public:
store_IMF(){}; // constructor
~store_IMF(){IMF_list.clear();}; // destructor
// get set functions
inline std::list< std::vector<T> > get_IMF_list(int list_size){IMF_list.reverse(); if (list_size==-1){list_size=IMF_list.size();}; IMF_list.resize(list_size); return IMF_list; }; //get the T of interest

inline void set_IMF_vector(std::vector<T> IMF_v){IMF_list.push_back(IMF_v);};//set the vector of 
//set functions
private:
std::list< std::vector<T> > IMF_list;
//boost::shared_ptr<BW_filter<T>> c_BW_p (new BW_filter<T>);

};

#endif


