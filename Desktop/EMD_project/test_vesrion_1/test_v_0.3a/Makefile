# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = c++
OBJS = store_h_comp.o extrema_detect.o B_spline.o compute_components.o test_main.o 
CC = g++ -std=c++11
CFLAGS  = -g -Wall
LFLAGS = -Wall $(DEBUG)
#PYTHONDEPHEAD = -I/usr/include/python3.6 -lpython3.6
#LIBDEP= -L/usr/lib/x86_64-linux-gnu/ 
LIB=-lboost_iostreams -lboost_system -lboost_filesystem
#INPATH= -I/usr/include/

#Path dependences
run: all
	-gdb ./test_run

all: test_run

#
default: test_run

# extrema_detect.o, test_main.o,:
#
test_run: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@ $(LIB) 

libmine.a: $(LDFLAGS)
# files extrema_detect.cpp, extrema_detect.h:
#
store_h_comp.o: store_h_comp.cpp store_h_comp.h define.h
	$(CC) $(CFLAGS) -c $< 

# files extrema_detect.cpp, extrema_detect.h:
#
extrema_detect.o: extrema_detect.cpp extrema_detect.h define.h
	$(CC) $(CFLAGS) -c $< 

# files B_spline.cpp, B_spline.h:
#
B_spline.o: B_spline.cpp B_spline.h extrema_detect.cpp extrema_detect.h define.h
	$(CC) $(CFLAGS) -c $< 

# compute h component
compute_components.o: compute_components.cpp compute_components.h define.h
	$(CC) $(CFLAGS) -c $< 


# test_main.cpp and test_main.h:
# the cpp needed?

test_main.o:  test_main.cpp store_h_comp.cpp store_h_comp.h extrema_detect.h extrema_detect.cpp B_spline.cpp B_spline.h compute_components.cpp compute_components.h define.h gnuplot-iostream.h
	$(CC) $(CFLAGS) -c $< $(LIB) 
 

#clean section
#
.PHONY: clean
clean: 
	$(RM) count *.o *~ test_run



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
