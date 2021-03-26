////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>
#include <new>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <memory>
#include <boost/scoped_ptr.hpp>
#include "B_spline.h"
//#include "define.hpp"


extern int N_sample;
extern double increase_value;
extern double increase_value;
extern double cub_coef_a;
extern double cub_coef_b;
extern double cub_coef_c;
extern int type_interpolation;

///////////////////////////////////////////////////////////////////////
//Class: B_spline
//Function: B_spline(), ~B_spline()
//Abstract: destructor, constructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
B_spline<T>::B_spline(){
/*default proceess*/}



///////////////////////////////////////////////////////////////////////
//Class: B_spline
//Function:  B_spline(std::vector<T> , std::vector<T> )
//Abstract: (step one) call the cubic_B_comp for determine of Bk, (step two) call the coeff_solver for  solving the a coefficient, , (step three) determine the B_spline interpolation points
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
B_spline<T>::B_spline(std::vector<T> t_extrema, std::vector<T> t_extrema_time, std::vector<T> t_time,T initial_signal) :
extrema(t_extrema), extrema_time(t_extrema_time), time_inter(t_time){
int dim = extrema.size();//dimention of vectors
//timestep_compute();// call timestep not use here pass the initial timestep of ECG better
std::copy(time_inter.begin(),time_inter.end(),time); //copy in array the vector

T d_extrema_time[extrema_time.size()];//difene array of vector a_coeff
std::copy(extrema_time.begin(),extrema_time.end(),d_extrema_time); //copy in array the vector
T d_extrema[extrema.size()];//difene array of vector a_coeff
std::copy(extrema.begin(),extrema.end(),d_extrema); //copy in array the vector
T h=(d_extrema_time[dim]-d_extrema_time[0])/N_sample;//h: time step between the intervals
//set the passing members in object
std::shared_ptr<B_spline<T>> BS1=std::make_shared<B_spline<T>>();
BS1->set_time(t_time);
BS1->set_h(h);
BS1->set_extrema(extrema);
BS1->set_extrema_time(extrema_time);

//linear interpolation
if (type_interpolation==1){
 int i=0;
 int counter=0;
 T slope=0;
 T offset=initial_signal;

 while (i<SAMPLE)
 {
  if((time[i]==d_extrema_time[counter])&&(counter<dim-1))
  {
   slope=(d_extrema[counter+1]-d_extrema[counter])/(d_extrema_time[counter+1]-    d_extrema_time[counter]); 
   offset=d_extrema[counter]; 
   counter++;
   //std::cout<<slope<<"slope\n";
   }//end if inside
  S_extrema[i]=offset+(time[i]-d_extrema_time[counter-1])*slope;
  //std::cout<<offset<<"offset\n";
  i++;
 }//end while
}//end if interpolation type

// Cubic_b_spline interpolation
if (type_interpolation==0){
/*               Step One                */
//Cubic_B_comp call//

Cubic_B_comp<T> cubic_B_com; //start the B coef compute
cubic_B_com.B_determine(BS1);
std::vector<T> v_B_k=cubic_B_com.get(); // get the results
T B_k[v_B_k.size()];//define array of vector a_coeff
std::copy(v_B_k.begin(),v_B_k.end(),B_k); //copy in array the vector

/*                Step Two              */
//call the coeff_solver//
int extrema_size=extrema.size();
Coeff_solver<T> coeff_s; //start the a coefficient compute
coeff_s.run(BS1);
//boost::scoped_ptr< Coeff_solver<T> > cp1(new Coeff_solver<T>); //shared pointer
std::vector<T> a_coeff=coeff_s.get(); // get the results
T array_a_coeff[a_coeff.size()];//difene array of vector a_coeff
std::copy(a_coeff.begin(),a_coeff.end(),array_a_coeff); //copy in array the vector
T a_minus_one=2*(array_a_coeff[0]-array_a_coeff[1]); //find the a(-1) coeff
T a_plus_n=2*(array_a_coeff[extrema_size-1]-array_a_coeff[extrema_size-2]);//find the a(n+1) coeff
//////debug///////////////////////////////
//for (int o=0;o<extrema_size;++o){
//  std::cout << array_a_coeff[o]<< ", ";}
// std::cout <<"\n";
/////////////////////////////////////////////

/*              Step Three               */
////Compute the S B_spline iterpolation points/////

int i=0;
int counter=0;
int position=0;
// B_spline points compute

while (i<N_sample){

int position=(i)*4;//counter to count the B_k 4*N_sample positions
if(time[i]==extrema_time[counter]){S_extrema[i]=extrema[counter]; counter++;}//end if inside

if (time[i]<extrema_time[1] && time[i]>extrema_time[0]){S_extrema[i]=a_minus_one*B_k[position]+array_a_coeff[0]*B_k[position+1]+array_a_coeff[1]*B_k[position+2]+array_a_coeff[2]*B_k[position+3];}//end if inside}//end if

if (time[i]<extrema_time[extrema_time.size()-2] && time[i]>extrema_time[1]){
	if (time[i]<extrema_time[counter]&& time[i]>extrema_time[counter-1]){S_extrema[i]=array_a_coeff[counter-2]*B_k[position]+array_a_coeff[counter-1]*B_k[position+1]+array_a_coeff[counter]*B_k[position+2]+array_a_coeff[counter+1]*B_k[position+3];}	
}//end if

if (time[i]<extrema_time[extrema_time.size()-1] && time[i]>extrema_time[extrema_time.size()-2]){S_extrema[i]=a_coeff[counter-2]*B_k[position]+array_a_coeff[counter-1]*B_k[position+1]+array_a_coeff[counter]*B_k[position+2]+a_plus_n*B_k[position+3];
}//end if

//bountary points initialization by the half of first and last of the extrema
if(time[i]<extrema_time[0]){
S_extrema[i]=extrema[0]/2;}
if (time[i]>extrema_time[extrema_time.size()-1]){
S_extrema[i]=extrema[extrema.size()-1]/2;}
////
i++;// increase counter
}//end while


//////debug///////////////////////////////
std::cout <<"\n";
std::cout <<"B_k: \n";
for (int o=0;o<v_B_k.size();++o){
  std::cout << B_k[o]<< ", ";}
std::cout<<v_B_k.size()<<" size \n";
 std::cout <<"\n";
/////////////////////////////////////////////

//////debug///////////////////////////////
std::cout <<"\n";
std::cout <<"a_coeff: \n";
for (int o=0;o<a_coeff.size();++o){
  std::cout << array_a_coeff[o]<< ", ";}
std::cout<<a_coeff.size()<<" size \n";
 std::cout <<"\n";
/////////////////////////////////////////////
}//end if interpolation type

//store vector
interp_data.insert(interp_data.end(),&S_extrema[0],&S_extrema[time_inter.size()]); //store the array in private vector


//////debug////////////////////////////////
//std::cout <<"\n";
//std::cout <<"S(t): \n";
//for (int o=0;o<interp_data.size();++o){
//  std::cout << S_extrema[o]<< ", ";}
//std::cout<<interp_data.size()<<" size \n";
// std::cout <<"\n";
/////////////////////////////////////////////

//////debug///////////////////////////////
//std::cout <<"\n";
//std::cout <<"time_interpolation: \n";
//for (int o=0;o<t_time.size();++o){
//  std::cout << time[o]<< ", ";}
//std::cout<<t_time.size()<<" size \n";
// std::cout <<"\n";
/////////////////////////////////////////////

//////debug///////////////////////////////
//std::cout <<"\n";
//std::cout <<"extrema(t): \n";
//for (int o=0;o<extrema.size();++o){
//  std::cout << d_extrema[o]<< ", ";}
//std::cout<<extrema.size()<<" size \n";
// std::cout <<"\n";
/////////////////////////////////////////////


}//end of constractor


///////////////////////////////////////////////////////////////////////
//Class: B_spline
//Function: get(STORE_KIND SK)
//Abstract: get vectors base an enum list
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
std::vector<T> B_spline<T>::get(STORE_KIND SK){
switch(SK){
case 0:
return interp_data; 
break; 
case 1: 
return time_inter;
break;}
};//end function


///////////////////////////////////////////////////////////////////////
//Class: B_spline
//Function: test_internal
//Abstract: test if b_spline interpolation include the initial signal
//Author: Michail Mamalakis
//Reference:  https://stackoverflow.com/questions/2114797/compute-median-of-values-stored-in-vector-c (median compute)
////////////////////////////////////////////////////////////////////
template<class T>
void B_spline<T>::test_internal(std::vector<T> initial_signal, std::vector<T> &b_spline_min, std::vector<T> &b_spline_max)
{
T new_value=0;
T value_initial=0;
T value_b_spline_max=0;
T value_b_spline_min=0;
T variance;

for(int i=0;i<initial_signal.size();++i){
new_value=0;
value_initial=initial_signal[i];
value_b_spline_min=b_spline_min[i];
value_b_spline_max=b_spline_max[i];
variance=(increase_value*value_initial);
if (value_initial>0 && value_b_spline_max>=0){
new_value=(value_initial>value_b_spline_max) ? value_initial+variance:value_b_spline_max;
};
//std::cout<< " value initial: "<<value_initial<< " max_before: "<<b_spline_max[i]<<" min_before: "<<b_spline_min[i]<<"\n";
//////////////mxa check///////////////////////////////
if (value_initial<0 && value_b_spline_max<=0){
new_value=(value_initial>value_b_spline_max) ? value_initial+variance:value_b_spline_max;};

if (value_initial<0 && value_b_spline_max>0){new_value=value_b_spline_max;};
if (value_initial>0 && value_b_spline_max<=0){new_value=value_initial+variance;};
if (value_initial==value_b_spline_min){new_value=value_b_spline_max;};

b_spline_max[i]=new_value;
////////////////min check///////////////////////////
if (value_initial>0 && value_b_spline_min>=0){
new_value=(value_initial<value_b_spline_min) ? value_initial-variance:value_b_spline_min;};

if (value_initial<0 && value_b_spline_min<=0){
new_value=(value_initial>value_b_spline_min) ? value_b_spline_min:value_initial-variance;};

if (value_initial>0 && value_b_spline_min<=0){new_value=value_b_spline_min;};
if (value_initial<0 && value_b_spline_min>0){new_value=value_initial-variance;};
if (value_initial==value_b_spline_min){new_value=value_b_spline_min;};
b_spline_min[i]=new_value;

//std::cout<< " value initial: "<<value_initial<<" max_after: "<<b_spline_max[i] <<" min_after: "<<b_spline_min[i]<<" \n";
}//end for
}//end function


///////////////////////////////////////////////////////////////////////
//Class: Cubic_B_comp
//Function: B_determine()
//Abstract: determine the Bk (for each timestep need  four Bk cubic-spline)
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void Cubic_B_comp<T>::B_determine(std::shared_ptr<B_spline<T>> &BS1){
//initialize values
std::vector<T> c_extrema_time=BS1->get_extrema_time();//take protected values
std::vector<T> c_timest=BS1->get_time();//take protected values
T array_extrema_time[c_extrema_time.size()]; //determine T array
T timestep[c_timest.size()];
std::copy(c_timest.begin(), c_timest.end(), timestep); //copy the c_extrema_timw  vector in array
std::copy(c_extrema_time.begin(),c_extrema_time.end(), array_extrema_time); //copy the protected 

//compute Bk of all the interpolation points
int dim = c_extrema_time.size();//dimention of vectors
//T c_h=(array_extrema_time[1]-array_extrema_time[0]);//h: time step between the intervals
T c_h=(array_extrema_time[dim-1]-array_extrema_time[0])/dim;//h: time step between the intervals
T xo=timestep[0];
int i=0; //count the number of intervals for interpolation 
int element_array=0; //count the number of Bk created
int count=0;
int count2=0;
std::cout<<"extrema: "<<count<<"\n";
while (i<N_sample){

if(timestep[i]==array_extrema_time[count]&&(count<dim-1)){
c_h=array_extrema_time[count+1]-array_extrema_time[count];
count++;
//xo=array_extrema_time[count]/* evaluation around the initial time of interval*/;
//std::cout<<"extrema: "<<count<<"\n";
}
B_array[count2+3]=test_B_case(c_h,timestep[i]-(count+1)*c_h,'u',xo);
B_array[count2+2]=test_B_case(c_h,timestep[i]-(count)*c_h,'d',xo);
B_array[count2+1]=test_B_case(c_h,timestep[i]-(count-1)*c_h,'t',xo);
B_array[count2]=test_B_case(c_h,timestep[i]-(count-2)*c_h,'f',xo);
count2+=4;
i++;}//end while first


// store vector
B_k_coeff.insert(B_k_coeff.end(),&B_array[0],&B_array[4*c_timest.size()]); //set the array in private vector
set_B_kcoeff(B_k_coeff);//store vector ,to be honest no need

///////debug///////////////////////////////
//for (int o=0;o<N_sample;++o){
//  std::cout << B_array[o]<< ", ";}
// std::cout <<"\n";
/////////////////////////////////////////////


}//end function


///////////////////////////////////////////////////////////////////////
//Class: Cubic_B_comp
//Function: test_B_case()
//Abstract: test case of Bk
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
T Cubic_B_comp<T>::test_B_case(T h, T time, char type, T xo){
T Bk=0;

std::cout<<"case: ";

if(type=='u'){Bk=(cub_coef_a)*pow(2*h+(time-xo),3);};
if(type=='d'){Bk=(cub_coef_b*(pow(h,3)))-(cub_coef_c)*pow((time-xo),2)*(2*h+(time-xo));};
if(type=='t'){Bk=(cub_coef_b*(pow(h,3)))-(cub_coef_c)*pow((time-xo),2)*(2*h-(time-xo));};
if(type=='f'){Bk=(cub_coef_a)*pow((2*h-(time-xo)),3);};

return Bk;
}//end function


///////////////////////////////////////////////////////////////////////
//Class: Cubic_B_comp
//Function: Cubic_B_comp(), ~Cubic_B_comp()
//Abstract: destructor, constructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
Cubic_B_comp<T>::Cubic_B_comp(){
/*default proceess*/}//end function



///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: run()
//Abstract: run the solving of a LU triangular compute of AX=B
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void Coeff_solver<T>::run(std::shared_ptr<B_spline<T>> &BS2){
//call protected member from basic class 
std::vector<T> c_extrema=BS2->get_extrema();//take protected values
std::vector<T> c_extrema_time=BS2->get_extrema_time();//take protected values
c_dim = c_extrema.size();//dimention of vectors
T array_extrema[c_dim];
T array_extrema_time[c_dim];
std::copy(c_extrema.begin(),c_extrema.end(), array_extrema); //copy the c_extrema vector in array
std::copy(c_extrema_time.begin(),c_extrema_time.end(), array_extrema_time); //copy the c_extrema vector in array
T c_h=(array_extrema_time[c_extrema_time.size()-1]-array_extrema_time[0])/c_extrema_time.size();//h: time step between the intervals

int i=1,j=1; 
//compute A-coeff matrix
T percent=0;
A[0][0]=1;
//A[1][0]=1;
//A[c_dim-2][c_dim-1]=1;
A[c_dim-1][c_dim-1]=1;
while (i<c_dim-1){
percent=(i*100/c_dim-2);
//std::cout<<percent<<"%"" construction of A matrix \n";
A[i][i]=4;
A[i-1][i]=1;
A[i+1][i]=1;
i++;}//end while
//std::cout<<"100""%"" construction of A matrix \n";
///////debug///////////////////////////////
std::cout <<"\n";
std::cout<<"A_coeff is :\n";
for (int o=0;o<c_dim;++o){
for (int p=0;p<c_dim;++p){
  std::cout << A[p][o]<< " ";}
 std::cout <<"\n";}
std::cout <<"\n";
/////////////////////////////////////////////
// store A
//store(A, A_coeff);
//compute B (signal output)
c_h=(array_extrema_time[1]-array_extrema_time[0]);
B[0]=1.0000/pow(c_h,3)*array_extrema[0];
c_h=((array_extrema_time[c_dim-1]-array_extrema_time[0])/c_dim);
B[c_dim-1]=1.0000/pow(c_h,3)*array_extrema[c_dim-1];
while (j<c_dim-1){c_h=(array_extrema_time[j+1]-array_extrema_time[j]);//h: time step between the intervals
B[j]=(6.0000/pow(c_h,3))*array_extrema[j];j++;}// end while
///////debug///////////////////////////////
//std::cout <<"\n";
//std::cout<<"B vector is :\n";
//for (int o=0;o<c_dim;++o){
//  std::cout << B[o]<< " ";
//  std::cout <<"\n";}
//std::cout <<"\n";
/////////////////////////////////////////////

compute_LU();//call the compute of LU

} //end function


///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: compute_LU()
//Abstract: compute the L(lower-matrix) and U(upper-matrix)
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void Coeff_solver<T>::compute_LU() 
{
int i = 0;
int j = 0;
int k = 0;

 for (int i = 0; i < c_dim; i++) {
 
        // Upper Triangular
        for (int k = i; k < c_dim; k++) {
 
            // Summation of L(i, j) * U(j, k)
            T sum = 0.0000;
            for (int j = 0; j < i; j++){
                sum += (L[i][j] * U[j][k]);
              }
            // Evaluating U(i, k)
            U[i][k] = A[i][k] - sum;
		
        }
 
        // Lower Triangular
        for (int k = i; k < c_dim; k++) {
            if (i == k){
                L[i][i] = 1; // Diagonal as 1
                 }//end if
            else {
 
                // Summation of L(k, j) * U(j, i)
                T sum = 0.0000;
                for (int j = 0; j < i; j++){
                    sum += (L[k][j] * U[j][i]);
                 }//end for
                // Evaluating L(k, i)
                L[k][i] = (A[k][i] - sum) / U[i][i];
           
          }//end else
        }//end for

}//end for


///////debug///////////////////////////////
//std::cout <<"\n";
//std::cout<<"L is :\n";
//for (int o=0;o<c_dim;++o){
//for (int p=0;p<c_dim;++p){std::cout << L[o][p]<< " ";}
//  std::cout <<"\n";}
//std::cout <<"\n";
/////////////////////////////////////////////
///////debug/////////////////////////////////
//std::cout <<"\n";
//std::cout<<"U is :\n";
//for (int o=0;o<c_dim;++o){
//for (int p=0;p<c_dim;++p){std::cout << U[o][p]<< " ";}
//std::cout <<"\n";}
//std::cout <<"\n";
/////////////////////////////////////////////

//store L,U
//store(L, L_comp); //store the L matrix
//store(U, U_comp);  //store the U matrix

// solve LY=B
solver_LY(); //solve LY=B

}// end function


///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: solver_LY()
//Abstract: solve LY=B 
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void Coeff_solver<T>::solver_LY(){
/* LU=B solver logic
Y[0]=B[0]/L[0][0]
Y[1]=B[1]-L[0][1]*Y[0]/L[1][1]
Y[2]=(B[2]-L[1][2]*Y[1]-L[0][2]*Y[0])/L[2][2]
Y[3]=(B[3]-L[2][3]*Y[2]-L[1][3]*Y[1]-L[0][3]*Y[0])/L[3][3]
*/
T Y[c_dim-1];//define Y vector
int i=0,j=0;
Y[0]=0;
T sum=0.0000;
T F=0.0000;
while (i<c_dim){
F=0;
sum=0;
j=0;
while(j<i){
sum=F-L[i][j]*Y[j];
F=sum;
j++;}//end j while

Y[i]=(B[i]+F)/L[i][i];
i++;}//end i while

/////////////////////////////////////////////
///////debug///////////////////////////////
//std::cout <<"\n";
//std::cout<<"Y is :\n";
//for (int o=0;o<c_dim;++o){
//std::cout << Y[o]<< "\n ";
//}
//std::cout <<"\n";
/////////////////////////////////////////////

solver_UX(Y);
}//end function


///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: solver_UX(T [])
//Abstract: solve UX=Y 
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void Coeff_solver<T>::solver_UX(T Y[]){
/* UX=Y solver logic
X[0]=(Y[0]-X[0][2]*X[1]-U[0][2]*X[2]-U[0][3]*X[3])/U[0][0]
X[1]=(Y[1]-U[1][2]*X[2]-U[1][3]*X[3])/U[1][1]
X[2](Y[2]-U[2][0]*X[2])/U[2][2]
X[3]=Y[3]/U[3][3]
4x4 matrix example
*/
T X[c_dim-1];//define Y vector
int i=c_dim-1;
int j=c_dim-1;
T sum=0;
T F=0;
while (i>-1){
sum=0;
F=0;
j=c_dim-1;
while(j>i){
sum=U[i][j]*X[j];
F-=sum;
j--;}//end j while
X[i]=(Y[i]+F)/U[i][i]; //no need of ./U[i][i] because is always equal with 1
i--;}//end i while
a_coeff.insert(a_coeff.end(), &X[0], &X[c_dim]); //insert the results in a coefficient vector
set_acoeff(a_coeff); //store vector
/////////////////////////////////////////////
///////debug///////////////////////////////
//std::cout <<"\n";
//std::cout<<"a_coeff is :\n";
//for (int o=0;o<c_dim;++o){
//std::cout << X[o]<< " \n";
// }
//std::cout <<"\n";
/////////////////////////////////////////////
}//end function


///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: store(T [][], MATRIX_KIND M)
//Abstract: store matrix base a enum list (not sure if need it)
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void Coeff_solver<T>::store(T matrix[][SAMPLE], MATRIX_KIND M){

switch(M){
case 0:
matrix=this->L;
//std::cout<< "L stored \n";
break;
case 1:
matrix=this->U;
//std::cout<< "U stored \n";
break;
case 2:
matrix=this->A;
//std::cout<< "A-coef stored \n ";
break;
default:
   std::cout << "ERROR-> unknown matrix";
}
}//end function


///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: get_matrix(MATRIX_KIND M)
//Abstract: get matrix base a enum list (not sure if need it)
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
T Coeff_solver<T>::get_matrix(MATRIX_KIND M){
switch(M){
case 0:
return L;
//std::cout<< "L get ";
break;
case 1:
return U;
//std::cout<< "U get, ";
break;
case 2:
return A;
//std::cout<< "A-coef get, ";
break;
case 3:
return B;
//std::cout<< "B-vector get, ";
break;
default:
std::cout << "ERROR-> unknown matrix";
}
}//end function

///////////////////////////////////////////////////////////////////////
//Class:Coeff_solver
//Function: Coeff_solver(), ~Coeff_solver()
//Abstract: destructor, constructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
Coeff_solver<T>::Coeff_solver(){}


//////////////////////TODO_section//////////////////////////////////
//TODO1: make one function the SolverUX,LY, if you can.
//TODO2: remove the outlayer for better distribution
//TODO3: timestep and Bo timestep do a shift >> operation and do not use timestep[] ,only Bo_timestep!!
//TODO4: boundary dealing when stop the maximum with respect of time vector
//////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////UNUSED FUNCTIONS_CLASS////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//Class: B_spline
//Function: timestep_compute()
//Abstract: a function for determine the time-values of interpolation points base the N_sample 
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
/*
template<class T>
void B_spline<T>::timestep_compute(){

// initial compute /
int dim = extrema_time.size();//dimention of vectors
int inter_point=N_sample-dim;// compute interpolation points
///////debug/////////////////////////////////////////////////
//std::cout << inter_point<<"-> points for interpolation\n";
/////////////////////////////////////////////////////////////////
T aver_number_point=inter_point/dim; //compute mean value of inter points
///////debug///////////////////////////////////////////////////////////////////////////
//std::cout <<aver_number_point <<"-> average number of interpolation points\n";
////////////////////////////////////////////////////////////////////////////////////
int o=2;
int ext_time_size=extrema_time.size();
T d_extrema_time[extrema_time.size()];//difene array of vector a_coeff
T d_extrema[extrema.size()];//difene array of vector a_coeff
std::copy(extrema.begin(),extrema.end(),d_extrema); //copy in array the vector
std::copy(extrema_time.begin(),extrema_time.end(),d_extrema_time); //copy in array the vector

//  compute differences of intervals  /
T time_diff[ext_time_size];
time_diff[0]=d_extrema[1]-d_extrema[0];//initialize time_difference of ecg value array
T time_diff2[ext_time_size];
time_diff2[0]=d_extrema_time[1]-d_extrema_time[0];//initialize tim_diff of time array
T sum=time_diff[0];

// 
while (o<ext_time_size){
time_diff[o-1]=d_extrema[o]-d_extrema[o-1];
time_diff2[o-1]=d_extrema_time[o]-d_extrema_time[o-1];
sum=time_diff[o-1]+sum; ++o;}  //end while

//  compute interval number of points  /
T aver_time_diff=sum/dim ;//mean value of time differences
///////debug////////////////////////////////
//std::cout << aver_time_diff<<"-> average of time interval\n";
////////////////////////////////////////////

// evaluate the rounding of points /
int i=0;
unsigned int point;
T sum_p=0;
while (i<ext_time_size-1){
T point_for_evaluation= (time_diff[i]/aver_time_diff)*aver_number_point;
if(point_for_evaluation*10>=5){ point=point_for_evaluation+1;}
else{point=point_for_evaluation;}
if (point==0 | point==1){point=1;timestep[i]=time_diff2[i]/2;} //strengthen no zero point
else{
timestep[i]=time_diff2[i]/point;}//compute timestep;}
point_of_interval[i]=point;
///////debug////////////////////////////////
//std::cout << timestep[i]<<"->timesteps\n";
////////////////////////////////////////////////////
sum_p=point_of_interval[i]+sum_p;
//check overflow of interpolation point number
int check_point=sum_p+(time_diff[i+1]/aver_time_diff)*aver_number_point;
if(check_point>inter_point){
 //take itteration
unsigned int itter=std::distance(point_of_interval,std::max_element(point_of_interval,point_of_interval+i));  //take value
unsigned int reduce= check_point-inter_point-1;//define the value of reduce max point
point_of_interval[itter]=point_of_interval[itter]-reduce; //reduce max point
sum_p=sum_p-reduce; //update sum_p
}//end_if
if(i==(ext_time_size-3) && sum_p<inter_point){point_of_interval[i+1]=inter_point-sum_p;}
///////debug////////////////////////////////
//std::cout << point<<"-> number of interpolation points\n";
////////////////////////////////////////////
 i++;} //end while
//-second check if overflow?
if(sum_p>inter_point){
int reduce_2=sum_p-inter_point;
unsigned int itter2=std::distance(point_of_interval,std::max_element(point_of_interval,point_of_interval+dim-1));  //take max_value;
point_of_interval[itter2]=point_of_interval[itter2]-reduce_2; //reduce max point
///////debug////////////////////////////////
//std::cout <<reduce_2<< "-> reduce max point\n";
//////////////////////////////////////////
}//end_if
point_inter.insert(point_inter.end(),&point_of_interval[0],&point_of_interval[dim-2]); //store the array in protected vector

// define time vector /
unsigned int itter=0;
unsigned int count=0;
while (itter<ext_time_size-1){
time[count]=d_extrema_time[itter];//time of lower boundary
///////debug////////////////////////////////
//std::cout <<time[count]<< "-> time\n";
/////////////////////////////////////////
count++;
while (point_of_interval[itter]>0){
time[count]=time[count-1]+timestep[itter];
point_of_interval[itter]--;
///////debug////////////////////////////////
//std::cout <<time[count]<< "-> time_inter\n";
////////////////////////////////////////////
count++;
}//end while internal point
//time[count]=d_extrema_time[itter+1];//time of upper boundary
itter++;
}//end while extrema point
time[N_sample-1]=d_extrema_time[ext_time_size-1];


// store in vector  
time_inter.insert(time_inter.end(),&time[0],&time[N_sample]); //store the array in proteccted vector
interp_data_time.insert(interp_data_time.end(),&time[0],&time[N_sample]); //store the array private vector

}//end function
*/
//#undef N_sample
//#undef increase_value

