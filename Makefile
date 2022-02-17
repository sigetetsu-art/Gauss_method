CC = g++
CFLAG = -O4 -Wall

all: gauss_method

gauss_method: Gauss_method.cpp
						$(CC) $(CFLAG) Gauss_method.cpp -o gauss_method

clean:
		rm -f gauss_method *.o*~