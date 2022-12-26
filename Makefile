default: all

all:
	cd code; cc -ggdb -Wall -shared -fPIC -c *.c
	cd test; cc -ggdb -Wall matrix.c -o matrix \
		../code/matrix.o \
		../code/clann.o \
		../code/io.o -lm
	cd test; cc -ggdb -Wall kalman.c -o kalman \
		../code/kalman.o \
		../code/matrix.o \
		../code/clann.o \
		../code/io.o -lm
	cd test; cc -ggdb -Wall fft.c -o fft \
		../code/fft.o \
		../code/matrix.o \
		../code/clann.o \
		../code/statistic.o \
		../code/io.o -lm
	cd test; cc -ggdb -Wall lms.c -o lms \
		../code/matrix.o \
		../code/clann.o \
		../code/function.o \
		../code/lms.o \
		../code/neuron.o -lm
	cd test; cc -ggdb -Wall rbf.c -o rbf \
		../code/rbf.o \
		../code/kmeans.o \
		../code/matrix.o \
		../code/metric.o \
		../code/neuron.o \
		../code/function.o \
		../code/clann.o \
		../code/lms.o \
		../code/io.o -lm
	cd test; cc -ggdb -Wall svm.c -o svm \
		../code/svm.o \
		../code/ilpso.o \
		../code/matrix.o \
		../code/neuron.o \
		../code/function.o \
		../code/clann.o \
		../code/io.o -lm
	cd test; cc -Wall som.c -lpthread -lGL -lglut -o som \
		../code/clann.o \
		../code/som.o \
		../code/matrix.o \
		../code/metric.o \
		../code/io.o -lm

clean:
	cd code; rm -rf *.o
	cd test; rm -rf \
		fft \
		lms \
		matrix \
		rbf \
		svm \
		som \
		kalman

