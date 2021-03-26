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
//                             TEST 2: Evaluate the corect solve of b_spline    (verification)                       //
//Ref:example of 3.4 Spline interpolation literature data                                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Gnuplot gnu2;//define object of GNUplot
//this is a test of b_spline

 double ix[393];
 double fx[393];
 double tt[9]={-4,-3,-2,-1,0,1,2,3,4};
 long double ff[9]={1.0000/17.0000*sin(-4),1.0000/10.0000*sin(-3),1.0000/5.0000*sin(-2),1.0000/2.0000*sin(-1),1.0000*sin(0),1.0000/2.0000*sin(1)
, 1.0000/5.0000*sin(2), 1.0000/10.0000*sin(3), 1.0000/17.0000*sin(4)};

ix[0]=-4;
long double o=-4;
long double w=1;
long double fv2=0;
for ( int ig=0;ig<393;++ig){

ix[ig]=o+fv2/49;
if (ig==49*w){o+=1;fv2=1;w++;};
fx[ig]=1/(1+pow(ix[ig],2))*sin(ix[ig]);
std::cout<<ix[ig]<<" ix\n";
//std::cout<<ig<<" ig\n";
//std::cout<<o<<" o\n";
//std::cout<<fv2<<" fv2\n";
//std::cout<<w<<" w\n";
fv2+=1;
}
std::vector<T> eix;
std::vector<T> eff;
std::vector<T> ett;
std::vector<T> efx;
efx.insert(efx.end(), &fx[0], &fx[393]);//create vector
eix.insert(eix.end(), &ix[0], &ix[393]);//create vector
eff.insert(eff.end(), &ff[0], &ff[9]);//create vector
ett.insert(ett.end(), &tt[0], &tt[9]);//create vector
B_spline<T> bs(eff,ett ,eix, fx[0] );//call spine constractor
std::vector<T> spline=bs.get(VALUE); //get result
std::vector<T> spline_time=bs.get(TIME); //get result

std::vector<std::pair<T, T> > test2; //diffine pair of vector
std::vector<std::pair<T, T> > fun2; //diffine pair of vector
for (unsigned int g=0;g<393;++g){
 test2.push_back(std::make_pair(spline_time[g],spline[g]));
}
for (unsigned int gs=0;gs<393;++gs){
 fun2.push_back(std::make_pair(eix[gs],efx[gs]));
}
gnu2<< "set xrange [-4.5:4.5]\nset yrange [-0.5:0.5]\n"; //define ranges

//gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum'\n";
//gnu.send1d(xy_pts_ECG);

gnu2 << "plot '-' with points title 'b_spline Interpolation','-' with lines title 'f(x)'\n";
gnu2.send1d(test2);
gnu2.send1d(fun2);
}

//TODO1///AREA/////////
//create only with vector remove array if you can...if you have issue with store..///


