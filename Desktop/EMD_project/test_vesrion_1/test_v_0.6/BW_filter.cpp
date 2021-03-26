////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

///////////////////////////////////////////////////////////////////////////////

#include "BW_filter.h"
#include "store_IMF.h"
#include "store_IMF.cpp"
#include <iostream>
#include <numeric>
#include "define.hpp"

extern double FREQ;
extern double M_FREQ;
extern double VAR_ACCUR;

///////////////////////////////////////////////////////////////////////
//Class: BW_filter
//Function: BW_filter, ~BW_filter
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
BW_filter<T>::BW_filter(std::vector<T> X_signal, std::vector<T> time, std::shared_ptr<store_IMF<T>>  &IMF) : c_X_signal(X_signal), c_time(time), IMF_obj(IMF) {c_omega=FREQ; c_M=M_FREQ; c_j=VAR_ACCUR; compute_signal();}
template<class T>
BW_filter<T>::BW_filter(){}


///////////////////////////////////////////////////////////////////////
//Class: BW_filter
//Function: compute_signal
//Abstract: addiction of the noise signal with the IMF order which need to remove
//Author: Michail Mamalakis
//Reference: 
///////////////////////////////////////////////////////////////////

template<class T>
void BW_filter<T>::compute_signal(){
std::cout<<"//////////////////////////////////////////////////////////////////\n";
std::cout<<"///////////////////////BW_FILTER//////////////////////////////////\n";
std::list< std::vector<T> > IMF_list;
IMF_list=IMF_obj->get_IMF_list(1);
IMF_list.reverse();
int list_size=IMF_list.size();
int k=1;
T var=0;
c_i=IMF_list.front();
IMF_list.pop_front();
bool test=false;
if (k>=list_size-1){test=true;};
///debug
//std::cout<<var_1<<" variance of "<<k<<" IMF\n";
////////////////////////////////
//debug
for(auto c_t : c_i)
{
std::cout<<c_t<<" c_t\n";
}
//for(auto b_t : b_i)
//{
//std::cout<<b_t<<" b_t\n";
//}
//std::cout<<b_i.size()<<" b_i.size\n";
//std::cout<<c_i.size()<<" c_i.size\n";
//std::cout<<h_i.size()<<" h_i.size\n";
//std::cout<<list_size<<" list size\n";
///////////
c_i.clear();
h_i.clear();
b_i.clear();
T store[SAMPLE];
T C[SAMPLE];
std::copy(c_i.begin(),c_i.end(),C);
for (int i=0; i<SAMPLE; ++i){
store[i]=C[i];}
while(test==false){
k++;
c_i=IMF_list.front();
IMF_list.pop_front();
std::copy(c_i.begin(),c_i.end(),C);
for (int i=0; i<SAMPLE; ++i){
store[i]+=C[i];}

//the estimated b_i
if (k>=list_size-1){test=true;};
//debug
//std::cout<<k<<" BW_FILTER loop\n";
/////////////////////////////////////
///debug
//std::cout<<var_1<<" variance of "<<k<<" IMF\n";
////////////////////////////////
//debug
//for(auto c_t : c_i)
//{
//std::cout<<c_t<<" c_t\n";
//}
//for(auto h_t : h_i)
//{
//std::cout<<h_t<<" h_t\n";
//}
//for(auto b_t : b_i)
//{
//std::cout<<b_t<<" b_t\n";
//}
//std::cout<<b_i.size()<<" b_i.size\n";
//std::cout<<c_i.size()<<" c_i.size\n";
//std::cout<<h_i.size()<<" h_i.size\n";
//////////
c_i.clear();
h_i.clear();
b_i.clear();
}//end while
estim_b_i.insert(estim_b_i.end(), &store[0],&store[SAMPLE]);

}//end function
///////////////////////////////////////////////////////////////////////
//Class: BW_filter
//Function: cycle_convolution
//Abstract: full convolution of two signals
//Author: Michail Mamalakis
//Reference: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.115.967&rep=rep1&type=pdf
///////////////////////////////////////////////////////////////////

template<typename T>
void BW_filter<T>::cycle_convolution() {
  int  nf = c_i.size();
/*
T out;
T sum;
T p_sum;
T h_array[nf];
T c_array[nf];
T output[nf]={0};
std::copy(h_i.begin(),h_i.end(),h_array);
std::copy(c_i.begin(),c_i.end(),c_array);
for(int i=0; i < nf; ++i) {
std::rotate(c_i.begin(),c_i.begin()+1,c_i.end());
sum=0;
int count=0;
for(auto c_t:c_i){
//std::cout<<c_t<< " signal output \n";
//std::cout<<h_array[count]<< " sys output \n";
 out=c_t*h_array[count];
sum+=out;
//std::cout<<sum<< " sum \n"; 
count++;
}
output[i]=sum; 
//std::cout<<output[i]<< " cycle convolution output \n"; 
}
b_i.insert(b_i.begin(),&output[0],&output[nf]);
*/
//debug for test the correct decomposition process
b_i=c_i;
}

///////////////////////////////////////////////////////////////////////
//Class: BW_filter
//Function: variance_b
//Abstract: compute variance of b
//Author: Michail Mamalakis
//Reference: 
///////////////////////////////////////////////////////////////////

template<typename T>
T BW_filter<T>::variance_b() {
T sum=0;
long double sum_var=0;
T sum_var2=0;
T mean_value;
long double var;
for(auto b_t : b_i)
{
    sum+=b_t;
//std::cout<<b_t<<" b_t \n";
//std::cout<<sum<<" sum_mean \n";
}
mean_value=sum/b_i.size();
b_i.pop_back();//reduce by one the length L-1
for(auto b_t_a : b_i)
{
    sum_var2=pow((b_t_a-mean_value),2);
    sum_var+=sum_var2;
//std::cout<<b_t_a<<" bt \n";
//std::cout<<sum_var<<" sum_var \n";
//std::cout<<sum_var2<<" sum_var2 \n";
}
var=sum_var/(b_i.size()-1);
//debug
//std::cout<<mean_value<<"mean value\n";
//std::cout<<sum<<" sum \n";
////////////////////////////////
return var;
}


///////////////////////////////////////////////////////////////////////
//Class: BW_filter
//Function: sinc_low_pass
//Abstract: sinc low pass filter compute impulse response
//Author: Michail Mamalakis
//Reference: https://en.wikipedia.org/wiki/Sinc_filter
///////////////////////////////////////////////////////////////////

template<typename T>
void BW_filter<T>::sinc_low_pass(int k) {
std::vector<T> output;
T omega_k=c_omega/pow(c_M,k-1);
omega_k=omega_k;///c_time.size();// fsample=fo/sample_rate
for(auto t_time : c_time)

{ 
    output.push_back((2*omega_k)*(sin(t_time*2*M_PI *omega_k)/(2*M_PI*(t_time+0.000000000001)*omega_k)));
}
h_i=output;
}


///////////////////////////////////////////////////////////////////////
//Class: BW_filter
//Function: test_critirio
//Abstract: check the critirio of Q
//Author: Michail Mamalakis
//Reference: 
///////////////////////////////////////////////////////////////////

template<typename T>
bool BW_filter<T>::test_critirio(T var, T var_1) {
if(var_1<=c_j && var>c_j ){ return true;}
else{return false;}
}


