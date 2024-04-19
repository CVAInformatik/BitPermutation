
CC = g++
CFLAGS = -g 
CPPFLAGS =  -O3

%.o  :  %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	rm *.o


BitPermutation.o : BitPermutation.cpp  BitPermutation.h 


BitPermutation          : BitPermutation.o
