////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////


#include <string>

//Default values of GLOBAL variables

 int change_phase_lock=0;
 int start_reading=800; 
 std::string ECG_data="/home/mamalakis/ECG_partwo/EMD_project/collection_of_data/experimental/filtered.txt";
// B_spline parameters
 int N_sample=500;
  int L_data=500;
 double increase_value=0.01;
 double cub_coef_a=1.0000/6.0000;
 double cub_coef_b=2.0000/3.0000;
 double cub_coef_c=1.0000/2.0000;
 int type_interpolation=1;
 int MAX_LOOP=15;
//extrema define parameters
 int POINTS_OF_EVAL2=2;
 std::string PATH_OF_TXT="/home/mamalakis/Desktop/test.txt"; 
 double ACCUR=0.000001;
 int Critirio=1; 
//internal loop parameter 
 int MAX_INTLOOP=600;
 double SDif1=0.5;
 double SDif2=0.1;
//BW filter parameters
 double FREQ=0.8;
 double M_FREQ=20;
 double VAR_ACCUR=0.0000000001;
double GAIN=1;
int Shift_time=0;
 double Shift_value=0;
 int FILTER_TIME=1;




