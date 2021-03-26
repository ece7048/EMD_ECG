////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////

#include "external_loop.h"
#include <iostream>
#include "define.h"

//#define MAX_LOOP 15

///////////////////////////////////////////////////////////////////////
//Class: external_loop
//Function: external_loop, ~external_loop
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
external_loop<T>::external_loop(std::vector<T> c_signal, std::vector<T> c_time) : signal(c_signal), time(c_time){}
template<class T>
external_loop<T>::external_loop(){}
template<class T>
external_loop<T>::~external_loop(){}

///////////////////////////////////////////////////////////////////////
//Class: external_loop
//Function: run
//Abstract: run external_loop for residual construction
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void external_loop<T>::run(){
std::cout<<" ///////////////////////"<<"\n";
T c_X[L_data]={0};
T c_T[L_data]={0};
std::copy(signal.begin(),signal.end(),c_X);
std::copy(time.begin(),time.end(),c_T);

//initialize parameters external loop
int i=0;//counter
std::shared_ptr< store_IMF<T> > IMF_p =std::make_shared<store_IMF<T>>(); //shared IMF object pointer
std::vector<T> IMF_comp;
std::vector<T> max;
std::vector<T> min;
std::vector<T> signal2;
//////////////////////////////////////////////////////////////////////////////////////////
//debug_perpuse call///////

//std::vector<T> bmax2;//test
//std::vector<T> bmin2;//test
//T b_max2[L_data];//test
//T b_min2[L_data];//test
//std::list<std::vector<T>> bspl;//test
//T x2[L_data];//test
/////////////////////////////////////////////////////////////////////////////////////////

//signal.insert(signal.end(),&c_X[0],&c_X[L_data]);
//time.insert(time.end(),&c_T[0],&c_T[L_data]);
int ext_size=0;
std::shared_ptr<extrema_detect<T>> ED_p1=std::make_shared<extrema_detect<T>>(c_X,c_T);//create shared object pointer
//max=ED_p1->get(MAX_VALUE);
//min=ED_p1->get(MIN_VALUE);
int one=ED_p1->test_point();
if(one==1){ext_size=1;};
if(one==0){ext_size=10;};

//external loop start
while (ext_size>=2){
//clear vector section
IMF_comp.clear();
max.clear();
min.clear();

///////////////////////
//signal2.clear();//test
//bmax2.clear();//test
//bmin2.clear();//test
//bspl.clear();//test
//////////////////////////////////

//while internal loop start
std::shared_ptr<IMF_compute<T>> IMF_comp_obj=std::make_shared<IMF_compute<T>>(signal,time);//create shared object pointer
IMF_comp_obj->run();
IMF_comp=IMF_comp_obj->get_IMF();//get IMF component result
signal2=IMF_comp_obj->get_IMF_k();

//debug_test_b-spline////
T imf_array[IMF_comp.size()];
std::copy(IMF_comp.begin(),IMF_comp.end(),imf_array);
//for(int o=0;o<signal.size();o++){std::cout<<imf_array[o]<<" IMF_output \n";}
//bspl=IMF_comp_obj->get_b_spline();
//bmin2=bspl.front();
//bmax2=bspl.back();
//std::copy(bmax2.begin(),bmax2.end(),b_max2);
//std::copy(bmin2.begin(),bmin2.end(),b_min2);
///////////////////////////////////

//store IMF
IMF_p->set_IMF_vector(IMF_comp);//add in list vector

//compute residual
std::shared_ptr<compute_residue<T>> CR=std::make_shared<compute_residue<T>>(IMF_comp,signal);//create shared object pointer
signal=CR->get_residual();

//take new extrema vector
std::copy(signal.begin(),signal.end(),c_X);

//debug output of residual//////////////////////////////////////////////////
//for(int o=0;o<signal.size();o++){std::cout<<c_X[o]<<" residual_output \n";}
////////////////////////////////////////////////////////////////////////////

std::shared_ptr<extrema_detect<T>> ED_p=std::make_shared<extrema_detect<T>>(c_X,c_T);//create shared object pointer
//max=ED_p->get(MAX_VALUE);
//min=ED_p->get(MIN_VALUE);
int one=ED_p->test_point();
if(one==1){ext_size=1;};
if(one==0){ext_size=10;};
//debug////////////////////////////////////////////////
std::cout<<"////////////////////////////////// \n";
std::cout<<i<<" EXTERNAL LOOP \n";
std::cout<<"//////////////////////////////////"<<"\n";
//std::cout<<max.size()<<" max\n";
//std::cout<<min.size()<<" min\n";
i++;
if(i>MAX_LOOP){ext_size=1;};
//signal=signal2;//set in initial signal the last IMF value
}//end while
IMF_obj_external_loop=IMF_p;//copy object
}//end function

 
