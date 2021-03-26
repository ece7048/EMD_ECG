
#ifndef DEFINE_H
#define DEFINE_H

//purser parameters
#define start_reading  //the columm that will start to pass data of ECG
#define L_data   //the number of the data of ECG
#define ECG_data //"/home/mamalakis/Desktop/EMD_project/test_vesrion_2/experimental_data/filtered.dat" //path of ECG file

// B_spline parameters
#define N_sample  //b_spline interpolation namber
#define increase_value  //the number of stadar deviation for the extrema where left the signal out of the interpolation max/min boundaries
#define cub_coef_a  //default 1/6
#define cub_coef_b  //default 2/3
#define cub_coef_c  //default 1/2
#define type_interpolation  //linear (1), cubic_spline (0)

//extrema define parameters
#define POINTS_OF_EVAL  //point of slope evaluation
#define PATH_OF_TXT  //path for store the extrema txt number I have to remove it
#define ACCUR  // the accurate which determine the extrema critirio IMF extract stop depends the scale of signal measurement
#define Critirio // the critirio (1) is the absolute difference of min-max for all the extrema lower from ACCUR, the critirio (2) is the mean value <ACCUR.=
#define variation // the variance of the extremaof initial and final value of signal

//internal loop parameter 
#define MAX_INTLOOP  //maximun internal loops IMF SD<0.3
#define SDif1  //the upper limite of sum differences between the h computed
#define SDif2  //the down limite of sum differences between the h computed

// external loop detection 
#define MAX_LOOP  // IMF max number extrema detection rule depentend


//BW filter parameters
#define FREQ  // the low pass frequency cut
#define M_FREQ  // freq/M_FREQ^(k-1) portion of the FREQ change through the k IMF
#define VAR_ACCUR  //VARIANCE aacurance critirio VAR_k<VAR_ACCUR, VAR_k-1>VAR_ACCUR

//DEBUG////////////////////////////////////////////////////
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
///use DEBUG(value_need_to_check)//////////////////////

#endif