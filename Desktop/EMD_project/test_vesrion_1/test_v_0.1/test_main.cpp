////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.1

//////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <list>
#include "extrema_detect.h"
#include "extrema_detect.cpp"
#include "B_spline.h"
#include "B_spline.cpp"
#include "compute_components.h"
#include "compute_components.cpp"
#include "store_h_comp.h"
#include "store_h_comp.cpp"
#include "gnuplot-iostream.h"
#include "define.h"

//#define L_data 44

typedef double T;


int main(){

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                         TEST 1: verify that the methodology of an interval [-4,-3] works corect                  //
//Ref:example of 3.4 Spline interpolation literature data                                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Gnuplot gnu;//define object of GNUplot
//this is a test of b_spline

long double s[50];
long double xx[50];
 double fx1[50];
xx[0]=-4;
long double fv=0;
for ( int ig=0;ig<50;++ig){
long double a2=0.034336821;
long double a3=0.010180972;
long double a4=-0.12539589;
long double a1=0.058492670;
T y1=1.0000/6.0000;
T y2=2.0000/3.0000;
T y3=1.0000/2.0000;
fv+=1;
xx[ig]=-4+fv/49;
fx1[ig]=1/(1+pow(xx[ig],2))*sin(xx[ig]);
T y4=a1*(-y1*pow((xx[ig]+1)+2,3));
T y5=a2*(y2+y3*pow((xx[ig]+4),2)*(xx[ig]+2));
T y6=a3*(y2-y3*pow((xx[ig]-1)+4,2)*((xx[ig]-1+6)));
T y7=a4*(y1*pow(((xx[ig]-2)+6),3));
s[ig]=y4+y5+y6+y7;
}
std::vector<T> es;
es.insert(es.end(), &s[0], &s[50]);//create vector
std::vector<T> exx;
exx.insert(exx.end(), &xx[0], &xx[50]);//create vector
std::vector<std::pair<T, T> > test; //diffine pair of vector
for (unsigned int g=0;g<50;++g){
 test.push_back(std::make_pair(xx[g],s[g]));
}
std::vector<T> eifx;
eifx.insert(eifx.end(), &fx1[0], &fx1[50]);//create vector
std::vector<std::pair<T, T> > fun; //diffine pair of vector
for (unsigned int gs=0;gs<50;++gs){
 fun.push_back(std::make_pair(exx[gs],eifx[gs]));
}
gnu<< "set xrange [-4.5:-2.5]\nset yrange [-0.5:0.5]\n"; //define ranges

//gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum'\n";
//gnu.send1d(xy_pts_ECG);

gnu << "plot '-' with points title 'b_spline Interpolation','-' with lines title 'f(x)'\n";
gnu.send1d(test);
gnu.send1d(fun);
}

//TODO1///AREA/////////
//create only with vector remove array if you can...if you have issue with store..///


