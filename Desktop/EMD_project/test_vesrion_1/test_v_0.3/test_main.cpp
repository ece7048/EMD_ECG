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
//                             TEST 3: Evaluate the ECG b_spline interpolation                                       //
//Ref:our data                                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//import the data
  T t[L_data]={0};
  T x[L_data]={0}; 
//while internal loop start
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
double x_p=0.0000;
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
std::cout<<x[i]<<" :values ";  
std::cout<<t[i]<<" :time \n";   
i++;
}
////////////////////////////////////////////////
//initialize internal loop parameters
T SD2=10; 
std::vector<T> h_comp2;
boost::shared_ptr<store_h_comp<T>> SCH(new store_h_comp<T>);
std::vector<T> ecg;
ecg.insert(ecg.end(), &x[0], &x[L_data]);//create vector
//
while (SD2>=0.3){
//call extrema detector

extrema_detect<T> ext(x,t);

std::vector<T> max;//max vector
max= ext.get(MAX_VALUE);

std::vector<T> max_time;//max time vector
max_time= ext.get(MAX_TIME);

std::vector<T> min;//min vector
min= ext.get(MIN_VALUE);

std::vector<T> min_time;//min time vector
min_time= ext.get(MIN_TIME);

// save the data points in a .txt file
std::ofstream ofs; 
ofs.open ("/home/mamalakis/Desktop/test_main.txt", std::ofstream::out | std::ofstream::app);

ofs << "MINIMUM_VALUES ";
for (unsigned int o=0;o<min.size();++o){
  ofs << min[o]<< ", ";
}
ofs << "MINIMUM_TIME_VALUES ";
for (unsigned int o=0;o<min_time.size();++o){
  ofs << min_time[o]<< ", ";
}
ofs << "MAX_VALUES ";
for (unsigned int o=0;o<max.size();++o){
  ofs << max[o]<< ", ";
}
ofs << "MAX_TIME_VALUES ";
for (unsigned int o=0;o<max_time.size();++o){
  ofs << max_time[o]<< ", ";
}
  ofs.close();

//b-splines compute
std::vector<T> time_ecg;
time_ecg.insert(time_ecg.end(), &t[0], &t[L_data]);//create vector
std::vector<T> signal;
signal.insert(signal.end(), &x[0], &x[L_data]);//create vector
B_spline<T> bs(min, min_time, time_ecg, x[0]);//call spine constractor
std::vector<T> spline_min=bs.get(VALUE); //get result
std::vector<T> spline_min_time=bs.get(TIME); //get result
 
B_spline<T> bs2(max, max_time, time_ecg, x[0]);//call spine constractor

std::vector<T> spline_max=bs2.get(VALUE); //get result
std::vector<T> spline_max_time=bs2.get(TIME); //get result
bs2.test_internal(signal, spline_min, spline_max); //check if internal the initial signal
std::cout<<"\n";
////////////debug//////////////////////////////////////
//for (unsigned int d=0;d<spline_max.size();++d){
// std::cout<<spline_max[d]<<",";
//}


// h-compute

std::list< std::vector<T> >  bS_l;
bS_l.push_back(spline_min);
bS_l.push_back(spline_max);
compute_components<T> CH(bS_l,signal);
h_comp2=CH.get_h_comp();
//boost::shared_ptr<store_h_comp<T>>
SCH->set_h(h_comp2);
SD2=SCH->get_SD();


////////////debug//////////////////////////////////////
std::cout<<"the SD of h is: "<<SD2;
//////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/////////// Visualization of test_number_one//////////////
/////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////GNUplot.h/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


Gnuplot gnu;//define object of GNUplot
Gnuplot gnu2;//define object of GNUplot

std::vector<std::pair<T, T> > xy_pts_ECG; //diffine pair of vector
std::vector<std::pair<T, T> > xy_pts_max; //diffine pair of vector
std::vector<std::pair<T, T> > xy_pts_min; //diffine pair of vector

///////////////splines of min-max/////////////////////
std::vector<std::pair<T, T> > xy_pts_max_sp; //diffine pair of vector
std::vector<std::pair<T, T> > xy_pts_min_sp; //diffine pair of vector

///////////////h_comp/////////////////////
std::vector<std::pair<T, T> > xy_h; //diffine pair of vector



///////////////////////////section for create pair vector for ploting by gnuplot/////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
for (unsigned int i=0;i<L_data;++i){
 xy_pts_ECG.push_back(std::make_pair(t[i],x[i]));
}

for (unsigned int o=0;o<min.size();++o){
 xy_pts_min.push_back(std::make_pair(min_time[o],min[o]));
}

for (unsigned int n=0;n<max.size();++n){
 xy_pts_max.push_back(std::make_pair(max_time[n],max[n]));
}

/////////////////////////////////////splines of min-max/////////////////////
for (unsigned int c=0;c<spline_min.size();++c){
 xy_pts_min_sp.push_back(std::make_pair(spline_min_time[c],spline_min[c]));
}

for (unsigned int d=0;d<spline_max.size();++d){
 xy_pts_max_sp.push_back(std::make_pair(spline_max_time[d],spline_max[d]));
}


/////////////////////////////////////h_comp/////////////////////
for (unsigned int e=0;e<h_comp2.size();++e){
 xy_h.push_back(std::make_pair(t[e],h_comp2[e]));
}


//detect max / min value
 T max_elem=*std::max_element(x,x+L_data);
 T min_elem=*std::min_element(x,x+L_data);
///////////////////////////////////////////////////////////////////////////////
gnu<< "set xrange [t[0]:t[L_data]]\nset yrange [min_elem:max_elem]\n"; //define ranges

//gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum'\n";
//gnu.send1d(xy_pts_ECG);

gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum', '-' with points title 'maximum'\n";
gnu.send1d(xy_pts_ECG);
gnu.send1d(xy_pts_min);
gnu.send1d(xy_pts_max);

std::cout<<"Do you want to visualize the splines of extrema? (y/n)";
char d;
std::cin>>d;
switch(d){
case 'y':
gnu<< "set xrange [t[0]:t[L_data]]\nset yrange [min_elem:max_elem]\n"; //define ranges

//gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum'\n";
//gnu.send1d(xy_pts_ECG);

gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum', '-' with points title 'maximum', '-' with points title 'min_spline', '-' with points title 'max_spline'\n";
gnu.send1d(xy_pts_ECG);
gnu.send1d(xy_pts_min);
gnu.send1d(xy_pts_max);
gnu.send1d(xy_pts_min_sp);
gnu.send1d(xy_pts_max_sp);

break;
case 'n':
std::cout<<"No prob mate... :( \n";
break;
}

std::cout<<"Do you want to visualize h_comp? (y/n)";
char d2;
std::cin>>d2;
switch(d2){
case 'y':
gnu<< "set xrange [t[0]:t[L_data]]\nset yrange [min_elem:max_elem]\n"; //define ranges

//gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum'\n";
//gnu.send1d(xy_pts_ECG);

gnu << "plot '-' with lines title 'initial signal', '-' with points title 'minimum', '-' with points title 'maximum', '-' with points title 'min_spline', '-' with points title 'max_spline','-' with points title 'h_comp'\n";
gnu.send1d(xy_pts_ECG);
gnu.send1d(xy_pts_min);
gnu.send1d(xy_pts_max);
gnu.send1d(xy_pts_min_sp);
gnu.send1d(xy_pts_max_sp);
gnu.send1d(xy_h);

break;
case 'n':
std::cout<<"No prob mate... :( \n";
break;
}

//initialize new h_comp for next loop
T h_comp2_array[L_data];
std::copy(h_comp2.begin(),h_comp2.end(),h_comp2_array);

for (unsigned int o=0;o<L_data;++o){
 x[o]=h_comp2_array[o];
}
if(d2=='n'){SD2=0.2;};//end loop
}//end while

///////////////////////////////////////////

}



