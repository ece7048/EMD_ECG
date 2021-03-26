////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <list>
#include "store_IMF.h"
#include "store_IMF.cpp"
#include "external_loop.h"
#include "external_loop.cpp"
#include "BW_filter.h"
#include "BW_filter.cpp"
#include "gnuplot-iostream.h"
#include "define.h"


//#define L_data 500

typedef double T;


int main(){

//import the data
T t[L_data];
T x[L_data];

///////////////////////////////////////////////////////////////////////////////////
//parser of data from txt
FILE *f;
f = fopen (ECG_data,"r");
//fix number of line 9 (first line 0-8) 2,11,
int num_of_colum=9;
int colum_t=1;
int colum_x=3;
int l=start_reading;
int count=0;
int count1=0;
int count2=0;
double x_p=0;
//access all the data of no detecting ECG
while (count< start_reading*num_of_colum){
fscanf (f, "%lf", &x_p);
count++; 
}
//passes 
while  (count< start_reading*num_of_colum+L_data*num_of_colum) {
fscanf (f, "%lf", &x_p);

//debug/////////////////////////////////////////  
//std::cout<<colum_x-1+num_of_colum*l<<" p test ";  
//std::cout<<colum_t-1+num_of_colum*l<<" t test ";  
//std::cout<<p<<" p \n";  
////////////////////////////////////////////////
if (count==colum_x-1+num_of_colum*l){
x[count1]=x_p; 
count1++;
}
if (count==colum_t-1+num_of_colum*l){
t[count2]=x_p; 
count2++;
}
if (count==num_of_colum*(l+1) -1){l++;}
count++;
 }
fclose(f);

//debug/////////////////////////////////////////  
int i=0;
T t0=t[0];
while  (i<L_data) {
t[i]=t[i]-t0;
t[i]=t[i]-t[0];
std::cout<<x[i]<<" :values ";  
std::cout<<t[i]<<" :time \n";   
i++;
}
////////////////////////////////////////////////

//detect max / min value
 T max_elem=*std::max_element(x,x+L_data);
 T min_elem=*std::min_element(x,x+L_data);
///////////////////////////////////////////////////////////////////////////////////////////////

//external loop run
std::vector<T> signal;
std::vector<T> time;
signal.insert(signal.end(),&x[0],&x[L_data]);
time.insert(time.end(),&t[0],&t[L_data]);
std::shared_ptr< external_loop<T> > E_l =std::make_shared<external_loop<T>>(signal,time); //shared IMF object pointer
E_l->run();
std::shared_ptr<store_IMF<T>> IMF_obj_ext;//take object store_IMF
IMF_obj_ext=E_l->get_IMF_store_obj();//take object store_IMF

std::list< std::vector<T> > IMF_list=IMF_obj_ext->get_IMF_list(-1);//test output

//BW_compute filter

std::vector<T> X_signal;
X_signal.insert(X_signal.end(),&x[0],&x[L_data]);
std::vector<T> t_time;
t_time.insert(t_time.end(),&t[0],&t[L_data]);
T omega=0.8;
int M=20;
T j=10;
std::shared_ptr< BW_filter<T> > BW =std::make_shared<BW_filter<T>>(X_signal,t_time,IMF_obj_ext); //shared IMF object pointer
std::vector<T> estimation_b;
estimation_b=BW->get_est_BW();//take the estimation of BW
T b_array[estimation_b.size()];
std::copy(estimation_b.begin(),estimation_b.end(),b_array); 
//estimation_b.insert(estimation_b.end(),&b_array[0],&b_array[L_data]);

//substruct the BW from signal

std::vector<T> filter_signal;

transform(X_signal.begin(), X_signal.end(), estimation_b.begin(),X_signal.begin(),  std::minus<T>());

T fs_array[L_data];
for (unsigned int i=0;i<L_data;++i){fs_array[i]=x[i]-b_array[i];}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////GNUplot.h/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Gnuplot gnu;//define object of GNUplot

std::vector<std::pair<T, T> > xy_pts_ECG2; //diffine pair of vector

///////////////b_comp////////////////////
std::vector<std::pair<T, T> > xy_b_comp; //diffine pair of vector

///////////////filter signal/////////////////////
std::vector<std::pair<T, T> > xy_fs_comp; //diffine pair of vector

///////////////////////////section for create pair vector for ploting by gnuplot/////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
for (unsigned int i=0;i<L_data;++i){
 xy_pts_ECG2.push_back(std::make_pair(t[i],x[i]));
//debug////////////////////////////////
//std::cout<<x[i]<<"  xxxxxxxx\n";
//std::cout<<b_array[i]<<"  bbbbb\n";
//std::cout<<fs_array[i]<<" ffffffff\n";
/////////////////////////////////////////////
}

for (unsigned int i=0;i<L_data;++i){
 xy_b_comp.push_back(std::make_pair(t[i],-b_array[i]));


}

for (unsigned int i=0;i<L_data;++i){
 xy_fs_comp.push_back(std::make_pair(t[i],fs_array[i]));

}

///////////////////////////////////////////////////////////////////////////////
gnu<< "set xrange [t[0]:t[L_data]]\nset yrange [min_elem:max_elem]\n"; //define ranges
gnu << "plot '-' with lines title 'initial signal', '-' with lines title ' BW_estimation', '-' with lines title ' filter_signal'\n";
gnu.send1d(xy_pts_ECG2);
gnu.send1d(xy_b_comp);
gnu.send1d(xy_fs_comp);


}//end function

//TODO1///AREA/////////
//create only with vector remove array if you can...if you have issue with store..///


