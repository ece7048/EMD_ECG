#////////////////////////////////////////////////////////////////////////////////////

#//Copyright (C) 2017 Michail Mamalakis

#//Author: Michail Mamalakis <mixalis.mamalakis@gmail.com>
#//Maintainer: Michail Mamalakis <mixalis.mamalakis@gmail.com>
#//Keywords: Implementation ECG filters
#//Version: 0.3

#//////////////////////////////////////////////////////////////////////////////////


# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = c++
OBJS = variables.o store_h_comp.o extrema_detect.o B_spline.o compute_components.o IMF_compute.o store_IMF.o compute_residue.o BW_filter.o external_loop.o main_run.o EMD.o 
CC = g++
CFLAGS  = -g -Wall
GTK_FLAG_LIB = `pkg-config --cflags --libs gtkmm-3.0 gladeui-2.0`
LFLAGS = -Wall $(DEBUG)
#PYTHONDEPHEAD = -I/usr/include/python3.6 -lpython3.6
#LIBDEP= -L/usr/lib/x86_64-linux-gnu/ 
LIB=-lboost_iostreams -lboost_system -lboost_filesystem
#INPATH= -I/usr/include/

#Path dependences
run: all
	-gdb ./EMD

all: EMD

#
default: EMD

# extrema_detect.o, test_main.o,:
#
EMD: $(OBJS)
	$(CC) $^ -o $@ $(LIB) $(GTK_FLAG_LIB)
   

libmine.a: $(LDFLAGS)
# files extrema_detect.cpp, extrema_detect.h:
#
store_h_comp.o: store_h_comp.cpp store_h_comp.h 
	$(CC) $(CFLAGS) -c $^ $(LIB)  

# files extrema_detect.cpp, extrema_detect.h:
#
extrema_detect.o: extrema_detect.cpp extrema_detect.h 
	$(CC) $(CFLAGS) -c $^ $(LIB)  

# files B_spline.cpp, B_spline.h:
#
B_spline.o: B_spline.cpp B_spline.h 
	$(CC) $(CFLAGS) -c $^ $(LIB) 

# compute h component
compute_components.o: compute_components.cpp compute_components.h 
	$(CC) $(CFLAGS) -c $^ $(LIB)  
 
# store_IMF.h
store_IMF.o: store_IMF.cpp store_IMF.h 
	$(CC) $(CFLAGS) -c $^ $(LIB)  

# compute_residue.h
compute_residue.o: compute_residue.cpp compute_residue.h 
	$(CC) $(CFLAGS) -c $^ $(LIB) 

# test_main.cpp and test_main.h:
# the cpp needed?
IMF_compute.o: IMF_compute.cpp IMF_compute.h 
	$(CC) $(CFLAGS) -c $^ $(LIB) 

# BW_filter.h BW_filter.cpp

BW_filter.o: BW_filter.cpp BW_filter.h 
	$(CC) $(CFLAGS) -c $^ $(LIB)
#external_loop.h external_loop.cpp
external_loop.o: external_loop.cpp external_loop.h 
	$(CC) $(CFLAGS) -c $^ $(LIB)
 
variables.o: variables.cpp 
	$(CC) $(CFLAGS) -c $^ $(LIB) 

# test_main.cpp and test_main.h:
# the cpp needed?
main_run.o:  main_run.cpp main_run.h 
	$(CC) $(CFLAGS) -c $^ $(LIB) 

EMD.o: EMD.cpp main_run.h  
	$(CC) $(CFLAGS) -c $^ $(GTK_FLAG_LIB)


#clean section
#
.PHONY: clean
clean: 
	$(RM) count *.o *~ EMD *.gch



##############################################################################################
#seperate classes file for b_splines######################################################
# cubic_b_comp.cpp and cubic_b_comp.h:
#
#cubic_b_comp.o: cubic_b_comp.cpp cubic_b_comp.h b_spline.cpp b_spline.h
#	$(CC) $(CFLAGS) -c $<

# coeff_solver.cpp and coeff_solver.h:
#
#coeff_solver.o: coeff_solver.cpp coeff_solver.h b_spline.cpp b_spline.h
#	$(CC) $(CFLAGS) -c $<

# b.spline.cpp and b.spline.h:
#
#b_spline.o: b_spline.cpp b_spline.h coeff_solver.h cubic_b_comp.h cubic_b_comp.cpp cubic_b_comp.h coeff_solver.cpp coeff_solver.h
#	$(CC) $(CFLAGS) -c $<
