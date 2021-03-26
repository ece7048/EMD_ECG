////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#ifndef COMPUTE_RESIDUE_H
#define COMPUTE_RESIDUE_H


#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
//#include "define.h"


//////////////////////////////////////////////////////////////////////////////
/////////////////////compute_residue///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template <class T>
class compute_residue
{

public:
compute_residue(std::vector<T> IMF, std::vector<T> X_signal){ 
//std::set_difference(X_signal.begin(), X_signal.end(), IMF.begin(), IMF.end(),std::inserter(c_residual, c_residual.begin()));
transform(X_signal.begin(), X_signal.end(), IMF.begin(),X_signal.begin(),  std::minus<T>()); 
c_residual=X_signal;
};//end function // constructor 
compute_residue(){}; // constructor
~compute_residue(){c_residual.clear();}; // destructor
// get set functions
inline std::vector<T> get_residual(){return c_residual;}; //get the T of interest
//set functions
private:
std::vector<T> c_residual;


};

#endif
