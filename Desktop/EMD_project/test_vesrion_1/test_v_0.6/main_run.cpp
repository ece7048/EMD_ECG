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
#include <numeric>
#include <list>
#include "store_IMF.h"
#include "store_IMF.cpp"
#include "external_loop.h"
#include "external_loop.cpp"
#include "BW_filter.h"
#include "BW_filter.cpp"
#include "gnuplot-iostream.h"
#include "define.hpp"
#include "main_run.h"


extern int L_data;
extern std::string ECG_data;
extern int start_reading;
extern double GAIN; 
extern int Shift_time;
extern double Shift_value;
extern int FILTER_TIME;
extern double FREQ;

main_run::main_run(){};
main_run::~main_run(){};

int main_run::run(){
typedef double T;
//import the data
T t[SAMPLE];
T x[SAMPLE];
T x1[SAMPLE];

///////////////////////////////////////////////////////////////////////////////////
//parser of data from txt
FILE *f;
const char* ECG=ECG_data.c_str();
f = fopen (ECG,"r");
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
//scenaria of different sin
x[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//x[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//x[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//x[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//without noise signals
x1[i]=2*sin(t[i]*2*M_PI *50)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//x1[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//x1[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);
//x1[i]=2*sin(t[i]*2*M_PI *50)+5*sin(t[i]*2*M_PI *3)+1*sin(t[i]*2*M_PI *10)+2*sin(t[i]*2*M_PI *20)+3*sin(t[i]*2*M_PI *120);


std::cout<<x[i]<<" :values ";  
std::cout<<t[i]<<" :time \n";   
i++;
}
////////////////////////////////////////////////

//detect max / min value
 T max_elem=*std::max_element(x,x+L_data);
 T min_elem=*std::min_element(x,x+L_data);
///////////////////////////////////////////////////////////////////////////////////////////////
int pass_times=0;
while (pass_times<FILTER_TIME){
//external loop run
std::vector<T> signal;
std::vector<T> time;
signal.insert(signal.end(),&x[0],&x[L_data]);
time.insert(time.end(),&t[0],&t[L_data]);
std::shared_ptr< external_loop<T> > E_l =std::make_shared<external_loop<T>>(signal,time); //shared IMF object pointer
E_l->run();
std::shared_ptr<store_IMF<T>> IMF_obj_ext;//take object store_IMF
IMF_obj_ext=E_l->get_IMF_store_obj();//take object store_IMF

std::list< std::vector<T> > IMF_list=IMF_obj_ext->get_IMF_list(1);//test output

//BW_compute filter

std::vector<T> X_signal;
X_signal.insert(X_signal.end(),&x[0],&x[L_data]);
std::vector<T> t_time;
t_time.insert(t_time.end(),&t[0],&t[L_data]);
std::shared_ptr< BW_filter<T> > BW =std::make_shared<BW_filter<T>>(X_signal,t_time,IMF_obj_ext); //shared IMF object pointer
std::vector<T> estimation_b;
estimation_b=BW->get_est_BW();//take the estimation of BW
T b_array[estimation_b.size()];
//shifting on time
if(Shift_time>L_data){Shift_time=L_data-1;}
if (Shift_time>=0){std::rotate(estimation_b.begin(),estimation_b.begin()+Shift_time,estimation_b.end());}
if (Shift_time<0){std::reverse(estimation_b.begin(),estimation_b.end()); std::rotate(estimation_b.begin(),estimation_b.begin()-Shift_time,estimation_b.end());std::reverse(estimation_b.begin(),estimation_b.end());} 
std::copy(estimation_b.begin(),estimation_b.end(),b_array); 
std::vector<T> filter_signal;
//Gain of BW_filter
//Shift of value of BW
T fs_array[estimation_b.size()];
for (unsigned int i=0;i<L_data;++i){b_array[i]=GAIN*b_array[i]+Shift_value;}
//substruct the BW from signal
for (unsigned int i=0;i<L_data;++i){fs_array[i]=x[i]-b_array[i]; }



//shifting on values of ECG




////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////GNUplot.h/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Gnuplot gnu;//define object of GNUplot

std::vector<std::pair<T, T> > xy_pts_ECG2; //diffine pair of vector

///////////////b_comp////////////////////
std::vector<std::pair<T, T> > xy_b_comp; //diffine pair of vector

///////////////filter signal/////////////////////
std::vector<std::pair<T, T> > xy_fs_comp; //diffine pair of vector
//correct signal
std::vector<std::pair<T, T> > xy1_fs_comp; //diffine pair of vector

///////////////////////////section for create pair vector for ploting by gnuplot/////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
for (unsigned int i=0;i<L_data;++i){
 xy_pts_ECG2.push_back(std::make_pair(t[i],x[i]));
//debug////////////////////////////////
//std::cout<<x[i]<<"  xxxxxxxx\n";
//std::cout<<b_array[i]<<"  bbbbb\n";
//std::cout<<fs_array[i]<<" ffffffff\n";
/////////////////////////////////////////////
x[i]=fs_array[i];
}

for (unsigned int i=0;i<L_data;++i){
 xy_b_comp.push_back(std::make_pair(t[i],b_array[i]));


}

for (unsigned int i=0;i<L_data;++i){
 xy_fs_comp.push_back(std::make_pair(t[i],fs_array[i]));
xy1_fs_comp.push_back(std::make_pair(t[i],x1[i]));

}

///////////////////////////////////////////////////////////////////////////////
gnu<< "set xrange [t[0]:t[L_data]]\nset yrange [min_elem:max_elem]\n"; //define ranges
gnu << "plot '-' with lines title 'initial signal', '-' with lines title ' BW_estimation', '-' with lines title ' filter_signal'\n";
gnu.send1d(xy_pts_ECG2);
gnu.send1d(xy_b_comp);
gnu.send1d(xy_fs_comp);
///////////////FINAL SIGNAL PLOT/////////////////////
Gnuplot gnu2;//define object of GNUplot
gnu2<< "set xrange [t[0]:t[L_data]]\nset yrange [min_elem:max_elem]\n"; //define ranges
gnu2 << "plot '-' with lines title 'final signal', '-' with lines title ' correct_signal'\n";
gnu2.send1d(xy_fs_comp);
gnu2.send1d(xy1_fs_comp);
pass_times++;
if (FILTER_TIME>1){
FREQ=FREQ-FREQ*0;//reduce frequency cut in each loop
}
}//end while


}//end function




//TODO1///AREA/////////
//create only with vector remove array if you can...if you have issue with store..///


