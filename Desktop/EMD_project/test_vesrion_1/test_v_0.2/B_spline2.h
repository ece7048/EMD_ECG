////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.1

//////////////////////////////////////////////////////////////////////////////////


#ifndef B_SPLINE_H
#define B_SPLINE_H

#include <stdio.h>
#include <vector>
#include "extrema_detect.h"
#define N_sample 44 //define the number of total points for interpolation


//////////////////////////////////////////////////////////////////////////////
/////////////////////CLASS: B_spline///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

enum STORE_KIND{
VALUE=0,
TIME=1,
};

enum EXTREMA{
MAXIMUM=0,
MINIMUM=1
};

template <class T>
class B_spline{

public:
B_spline();
~B_spline();
B_spline(std::vector<T> t_extrema, std::vector<T> t_extrema_time,std::vector<T> t_time);//initialize the interpolation cubic spline method
std::vector<T> get(STORE_KIND SK);
//get functions
 std::vector<T> get_extrema(){return extrema;}
 std::vector<T> get_extrema_time(){return extrema_time;}
 std::vector<T> get_time(){return time_inter;}
T get_h(){return h;}
//TODO1 set functions for pass extrema from extrema_detect.h
void set_h(T b_h){h=b_h;}
void set_extrema(std::vector<T> t_extrema){extrema=t_extrema;}
void set_extrema_time(std::vector<T> t_extrema_time){extrema_time=t_extrema_time;}
void set_time(std::vector<T> t_time_inter){time_inter=t_time_inter;}
void test_internal(std::vector<T> initial_signal, std::vector<T> &b_spline_min, std::vector<T> &b_spline_max);
protected:
std::vector<T> extrema;
std::vector<T> extrema_time; //can i do them references to change by default?
std::vector<T> time_inter;
T h;

private:
T S_extrema[N_sample];
T B_time[N_sample];
T timestep[N_sample]; //timestep of intervals of time
T time[N_sample]; 
std::vector<T> interp_data;
//void timestep_compute();//not used here
//std::vector<T> interp_data_time;//not used here, used from timestep_compute() function
//std::vector<T> point_inter;//not used here used from timestep_compute() function
//unsigned int point_of_interval[N_sample];//number of points in each interval of time, used from timestep_compute() function

};

//////////////////////////////////////////////////////////////////////////////
/////////////////////CLASS: Cubic_B_comp///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

template <class T>
class Cubic_B_comp: public B_spline<T> {
public:
Cubic_B_comp(); // take time step to compute the 4 Bo points of cubic interpolation
~Cubic_B_comp();
void B_determine(B_spline<T> &);
//get function
inline std::vector<T> get(){return B_k_coeff;};//get  B coef which ditermated
//set function
void set_B_kcoeff(std::vector<T> t_B_k_coeff){B_k_coeff=t_B_k_coeff;}

private:
T B_array[4*N_sample]; // all the interpolation B coeff
std::vector<T>  B_k_coeff; //the vector of B coeff of all interpolation points
T test_B_case(T h, T time, T xo);
};

//////////////////////////////////////////////////////////////////////////////
/////////////////////CLASS: Coeff_solver///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

enum MATRIX_KIND{
L_comp=0,
U_comp=1,
A_coeff=2,
B_vec=3,
};

template <class T>
class Coeff_solver: public B_spline<T>{
public:
Coeff_solver();
void run(B_spline<T> &);
~Coeff_solver();
//get function
inline std::vector<T> get(){return a_coeff;};//get  B coef of the area of ditermination
//set function
void set_acoeff(std::vector<T> t_a_coeff){a_coeff=t_a_coeff;}

private:
void solver_UX(T Y[]);
void compute_LU();
void solver_LY();
void store(T matrix[][N_sample], MATRIX_KIND M); //store matrix
T get_matrix(MATRIX_KIND M);//get matrix
std::vector<T> a_coeff;
unsigned int c_dim;
unsigned int c_h;
T L[N_sample][N_sample]; // L component matrix
T U[N_sample][N_sample]; // U component matrix
T A[N_sample][N_sample]; // A matrix coefficient
T B[N_sample]; //B vector

};

///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#undef N_sample
#endif

