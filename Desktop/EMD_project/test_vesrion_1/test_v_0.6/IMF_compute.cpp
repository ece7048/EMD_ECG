////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////

#include "IMF_compute.h"
#include "extrema_detect.h"
#include "extrema_detect.cpp"
#include "B_spline.h"
#include "B_spline.cpp"
#include "compute_components.h"
#include "compute_components.cpp"
#include "store_h_comp.h"
#include "store_h_comp.cpp"
#include <iostream>
#include "define.hpp"

//extern const int L_data;
extern double SDif1;
extern double SDif2;
extern int MAX_INTLOOP;
extern int L_data;
///////////////////////////////////////////////////////////////////////
//Class: IMF_compute
//Function: IMF_compute, ~IMF_compute
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
IMF_compute<T>::IMF_compute(std::vector<T> signal, std::vector<T> time) : c_X(signal), c_T(time){}
template<class T>
IMF_compute<T>::IMF_compute(){}
template<class T>
IMF_compute<T>::~IMF_compute(){ c_T.clear();c_X.clear(); IMF.clear(); bS_l.clear(); c_SD=0;}

///////////////////////////////////////////////////////////////////////
//Class: IMF_compute
//Function: run
//Abstract: run internal loop of IMF construction
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void IMF_compute<T>::run(){
std::cout<<" ///////////////////////"<<"\n";
std::cout<<" START INTERNAL LOOP"<<"\n";
//initialize internal loop parameters
c_SD=0; //Standar deviation initial value
std::vector<T> h_comp2=c_X;
std::shared_ptr<store_h_comp<T>> SCH=std::make_shared<store_h_comp<T>>();
SCH->set_h(c_X);//set initial signal as first h_comp
T x[c_X.size()];
T t[c_T.size()];
std::copy(c_X.begin(),c_X.end(),x);
std::copy(c_T.begin(),c_T.end(),t);
int i=1;
//initialize vectors
std::vector<T> max;//max vector
std::vector<T> max_time;//max time vector
std::vector<T> min;//min vector
std::vector<T> min_time;//min time vector
std::vector<T> time_ecg; //time of initial signal
std::vector<T> spline_min; //b_spline minimum
std::vector<T> spline_min_time;//b_spline minimum time
std::vector<T> spline_max;//b_spline maximum 
std::vector<T> spline_max_time;//b_spline maximum time
std::vector<T> signal2;
T h_comp2_array[c_X.size()];
bool test_point=false;
//internal loop
//c_X.insert(c_X.end(), &x[0], &x[44]);//create the signal vector

while (test_point==false){
//clear area vector
max.clear();//max vector
max_time.clear();//max time vector
min.clear();//min vector
min_time.clear();//min time vector
time_ecg.clear(); //time of initial signal
spline_min.clear(); //b_spline minimum
spline_min_time.clear();//b_spline minimum time
spline_max.clear();//b_spline maximum 
spline_max_time.clear();//b_spline maximum time
bS_l.clear();
signal2.clear();
//////////////////////////////////////////////////////
//IMF_k_1=c_X;//test vector deletee in real application
//call extrema detector
extrema_detect<T> ext(x,t);

max= ext.get(MAX_VALUE);

max_time= ext.get(MAX_TIME);

min= ext.get(MIN_VALUE);

min_time= ext.get(MIN_TIME);
//ext.~extrema_detect();
//b-splines compute

time_ecg.insert(time_ecg.end(), &t[0], &t[c_X.size()]);//create vector


signal2.insert(signal2.end(), &x[0], &x[c_X.size()]);//create vector

B_spline<T> bs(min, min_time, time_ecg,x[0]);//call spine constractor
//std::shared_ptr<B_spline<T>> bs=std::make_shared<B_spline<T>>(min, min_time, time_ecg);
spline_min=bs.get(VALUE); //get result
spline_min_time=bs.get(TIME); //get result

////////////debug//////////////////////////////////////
//for (unsigned int d=0;d<spline_min.size();++d){
// std::cout<<spline_min[d]<<",bs, \n";
//}//end for
//std::cout<<c_X.size()<<" c_X size \n";
//////////////////////////////////////////////////////////

B_spline<T> bs2(max, max_time, time_ecg,x[0]);//call spine constractor
//std::shared_ptr<B_spline<T>> bs2=std::make_shared<B_spline<T>>(max, max_time, time_ecg);
spline_max=bs2.get(VALUE); //get result
spline_max_time=bs2.get(TIME); //get result
bs2.test_internal(signal2, spline_min, spline_max); //check if internal the initial signal
////////////debug//////////////////////////////////////
// std::cout<<"AFTER,";
//for (unsigned int d=0;d<spline_min.size();++d){
// std::cout<<spline_min[d]<<",bsa,\n";
//}//end for
//std::cout<<spline_min.size()<<" size \n";
/////////////////////////////////////////////////

//bs2.~B_spline();
// h-compute
bS_l.push_back(spline_min);
bS_l.push_back(spline_max);
compute_components<T> CH(bS_l,signal2);
//std::shared_ptr<compute_components<T>> CH=std::make_shared<compute_components<T>>(bS_l,ecg);
h_comp2=CH.get_h_comp();

////////////debug//////////////////////////////////////
//for (unsigned int d=0;d<h_comp2.size();++d){
// std::cout<<h_comp2[d]<<",h_comp2,\n";//
//std::cout<<c_X[d]<<",cX\n";
//}//end for
//std::cout<<h_comp2.size()<<" size \n";
/////////////////////////////////////////////////
SCH->set_h(h_comp2);
c_SD=SCH->get_SD();
////////////debug//////////////////////////////////////
std::cout<<i<<" itteration of IMF compute"<<"\n";
std::cout<<"the SD of h is: "<<c_SD<<"\n";
i++;
//////////////////////////////////////////////////////////////
//initialize new h_comp for next loop
std::copy(h_comp2.begin(),h_comp2.end(),h_comp2_array);
for ( int o=0;o<L_data;++o){
 x[o]=h_comp2_array[o];
}//end for

if(c_SD<=SDif1&&c_SD>=SDif2){test_point=true;};//test critirio
if(i>MAX_INTLOOP){test_point=true;};//maximum loops

}//end while

IMF=h_comp2;//copy vector in private vector
h_comp2.clear();
}//end function



