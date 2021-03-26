
#ifndef DEFINE_H
#define DEFINE_H

//purser parameters
#define start_reading 800 //the columm that will start to pass data of ECG
#define L_data 250  //the number of the data of ECG
#define ECG_data "/home/mamalakis/Desktop/EMD_project/test_vesrion_1/experimental_data/filtered.dat" //path of ECG file

// B_spline parameters
#define N_sample 250 //b_spline interpolation namber
#define increase_value 0.01 //the number of stadar deviation for the extrema where left the signal out of the interpolation max/min boundaries
#define cub_coef_a 1.0000/6.0000 //default 1/6
#define cub_coef_b 2.0000/3.0000 //default 2/3
#define cub_coef_c 1.0000/2.0000 //default 1/2
#define type_interpolation 1 //linear (1), cubic_spline (0)

// external loop detection 
#define MAX_LOOP 10 // IMF max number extrema detection rule depentend

//extrema define parameters
#define POINTS_OF_EVAL 2 //point of slope evaluation
#define PATH_OF_TXT "/home/mamalakis/Desktop/test.txt" //path for store the extrema txt number I have to remove it
#define ACCUR 0.0001 // the accurate which determine the extrema critirio IMF extract stop
#define Critirio 2// the critirio 1 is the absolute difference of min-max for all the extrema lower from ACCUR, the critirio 2 is the mean value <ACCUR.=
#define variation 0.01// the variance of the extremaof initial and final value of signal
//internal loop parameter 
#define MAX_INTLOOP 10 //maximun internal loops IMF SD<0.2

//BW filter parameters
#define FREQ 0.2 // the low pass frequency cut
#define M_FREQ 20 // freq/M_FREQ^(k-1) portion of the FREQ change through the k IMF
#define VAR_ACCUR 0.000000000002 //VARIANCE aacurance critirio VAR_k<VAR_ACCUR, VAR_k-1>VAR_ACCUR

//DEBUG////////////////////////////////////////////////////
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
///use DEBUG(value_need_to_check)//////////////////////

#endif
