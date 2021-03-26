////////////////////////////////////////////////////////////////////////////////////

//Copyright (C) 2017 Michail Mamalakis

//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
//Keywords: Implementation ECG filters
//Version: 0.3

//////////////////////////////////////////////////////////////////////////////////

#include<fstream>
#include "extrema_detect.h"
#include <iostream>
#include "define.h"
#include <cmath>
//#define POINTS_OF_EVAL 2
//#define PATH_OF_TXT "/home/mamalakis/Desktop/test.txt"
//#define ACCUR 0.0001

///////////////////////////////////////////////////////////////////////
//Class: extrema_detect
//Function: extrema_detect, ~extrema_detect
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
extrema_detect<T>::extrema_detect(){}



///////////////////////////////////////////////////////////////////////
//Class: extrema_detect
//Function: extrema_detect(T [], T [])
//Abstract: destructor costructor
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
extrema_detect<T>::extrema_detect(T xin[], T time[])
{ 
//LENGTH L=LENGTH_BASIC; //set length of data
extrema_detect(); //initialize with default max,min array
int cmax=0; //counter of maximum
int cmin=0; //counter of minimum
T x[POINTS_OF_EVAL]; 
T t[POINTS_OF_EVAL];

// Initialize parameters :initial step
T previous_slope=0 ; // take first slope value from data
int i=1; //initialize counter i

// define array for the extrema of values of a function
T minimum_array[L_data ];
T maximum_array[L_data ];
T minimum_time_array[L_data ];
T maximum_time_array[L_data ];

while (i<L_data ){
x[1]= xin[i];
x[0]= xin[i-1];
t[0]=time[i-1];
t[1]=time[i];
T new_slope=forward_differentiation(x,t); //compute slope
// check the first point
if(i==1){
if (new_slope > 0 && xin[i-1]>0){ maximum_array[cmax]=x[0]; maximum_time_array[cmax]=t[0]; cmax++; minimum_array[cmin]=x[0]-x[0]*variation; minimum_time_array[cmin]=t[0]; cmin++;}; //maximum 
if (new_slope < 0 && xin[i-1]<0){ maximum_array[cmax]=x[0]; maximum_time_array[cmax]=t[0]; cmax++; minimum_array[cmin]=x[0]-x[0]*variation; minimum_time_array[cmin]=t[0]; cmin++;}; //maximum 
if (new_slope < 0 && xin[i-1]>0){ minimum_array[cmin]=x[0]; minimum_time_array[cmin]=t[0]; cmin++; maximum_array[cmax]=x[0]+x[0]*variation; maximum_time_array[cmax]=t[0]; cmax++;}; //minimum 
if (new_slope > 0 && xin[i-1]<0){ minimum_array[cmax]=x[0]; minimum_time_array[cmax]=t[0]; cmin++; maximum_array[cmax]=x[0]+x[0]*variation; maximum_time_array[cmax]=t[0]; cmax++;}; //minimum 
}
if(i!=1 && i!=L_data -1){
// check the extrema points
if (previous_slope >= 0){if (new_slope < 0){ maximum_array[cmax]=x[0]; maximum_time_array[cmax]=t[0]; cmax++;}} //maximum point
if (previous_slope <= 0){if (new_slope > 0){ minimum_array[cmin]=x[0]; minimum_time_array[cmin]=t[0]; cmin++;}} //minimum point
}
// check the last point
if(i==L_data -1){
if (new_slope > 0 && xin[i]>0){ maximum_array[cmax]=x[1]; maximum_time_array[cmax]=t[1]; cmax++; minimum_array[cmin]=x[1]-x[1]*variation; minimum_time_array[cmin]=t[1]; cmin++;}; //maximum 
if (new_slope < 0 && xin[i]<0){ maximum_array[cmax]=x[1]; maximum_time_array[cmax]=t[1]; cmax++; minimum_array[cmin]=x[1]-x[1]*variation; minimum_time_array[cmin]=t[1]; cmin++;}; //maximum 
if (new_slope < 0 && xin[i]>0){ minimum_array[cmin]=x[1]; minimum_time_array[cmin]=t[1]; cmin++; maximum_array[cmax]=x[1]+x[1]*variation; maximum_time_array[cmax]=t[1]; cmax++;}; //minimum 
if (new_slope > 0 && xin[i]<0){ minimum_array[cmax]=x[1]; minimum_time_array[cmax]=t[1]; cmin++; maximum_array[cmax]=x[1]+x[1]*variation; maximum_time_array[cmax]=t[1]; cmax++;}; //minimum 
}
previous_slope=new_slope; //store previous value of slope
i++; //increase counter
} //while end
//store extrema data
set(MAX_VALUE, maximum_array, cmax);
set(MIN_VALUE, minimum_array, cmin);
set(MAX_TIME, maximum_time_array, cmax);
set(MIN_TIME, minimum_time_array, cmin);

//write a .txt file
 std::ofstream ofs; 
ofs.open (PATH_OF_TXT, std::ofstream::out | std::ofstream::app);
ofs << " MINIMUM_VALUES ";
for (int o=0;o<cmin;++o){
  ofs << minimum_array[o]<< ", ";
}
ofs << "\n MINIMUM_TIME_VALUES ";
for (int o=0;o<cmin;++o){
  ofs << minimum_time_array[o]<< ", ";
}
ofs << "\n MAX_VALUES ";
for (int o=0;o<cmax;++o){
  ofs << maximum_array[o]<< ", ";
}
ofs << "\n MAX_TIME_VALUES ";
for (int o=0;o<cmax;++o){
  ofs << maximum_time_array[o]<< ", ";
}
  ofs.close();
}//end function


///////////////////////////////////////////////////////////////////////
//Class: extrema_detect
//Function: get(EXTREMA_KIND E)
//Abstract:get the set vectors
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>  
std::vector<T> extrema_detect<T>::get(EXTREMA_KIND E) { //get the array of interest
//EXTREMA_KIND E=choice;  //call enumarates
switch(E){
case 0:
return maximum;
break;
case 1:
return minimum;
break;
case 2:
return maximum_time;
break;
case 3:
return minimum_time;
break;
default:
    std::cout << "extrema store unknown";
}
}//end function


///////////////////////////////////////////////////////////////////////
//Class: extrema_detect
//Function: set(EXTREMA_KIND E,T [], int)
//Abstract: store the vectors
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
void extrema_detect<T>::set(EXTREMA_KIND E, T extrema_data[], int size_extrema){  //store the array of interest in a vector

//EXTREMA_KIND E=choice;  //call enumarates
switch(E){
case 0:
std::copy(&extrema_data[0], &extrema_data[size_extrema], back_inserter(maximum));
//std::cout<< "maximum, ";
break;
case 1:
minimum.insert(minimum.end(), &extrema_data[0], &extrema_data[size_extrema]);
//std::cout<< "minimum, ";
break;
case 2:
std::copy(&extrema_data[0],&extrema_data[size_extrema],back_inserter(maximum_time));
//std::cout<< "minimum_tim, ";
break;
case 3:
std::copy(&extrema_data[0],&extrema_data[size_extrema],back_inserter(minimum_time));
//std::cout<< "minimum_uu, ";
break;
default:
   std::cout << "extrema store unknown";
}
}//end function



//////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//Class: extrema_detect
//Function: test_point(T extrem[])
//Abstract: test if const
//Author: Michail Mamalakis
//Reference: 
////////////////////////////////////////////////////////////////////
template<class T>
int extrema_detect<T>::test_point(){
int count=0;//counter
int count2=0;//counter
T max[maximum.size()];
T min[minimum.size()];
std::min(maximum.size(),minimum.size());
std::copy(maximum.begin(),maximum.end(),max);
std::copy(minimum.begin(),minimum.end(),min);
int size= (maximum.size()<minimum.size()) ? maximum.size():minimum.size(); 
T diff[size];
for(int i=0;i<size;++i){
diff[i]=std::abs(max[i]-min[i]);

if(diff[i]<=ACCUR){count2++;}
count++;
//debug//////////////////////
//std::cout<<max[i]<<" max ";
//std::cout<<min[i]<<" min";
//std::cout<<diff[i]<<" diff\n";
//////////////////////////////
}//end for
switch(Critirio){
case 1://average difference
if(count2==count){return 1;};
if(count2!=count){return 0;};
std::cout<<count2<<"count2...\n";
break;
case 2://mean accur
T sum=0;
for(int i=0;i<size;++i){
sum += diff[i];
}//end for
T mean_extrema=sum/size;
std::cout<<mean_extrema<<"mean extrema...\n";
if(mean_extrema<=ACCUR){return 1;};
if(mean_extrema>ACCUR){return 0;};
break;
}
//std::cout<<count<<", "<<count2;

}
 

//#undef PATH_OF_TXT
//#undef POINTS_OF_EVAL
//#undef ACCUR

