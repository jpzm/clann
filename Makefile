default: all

all:
	cd code; cc -ggdb -Wall `pkg-config --cflags gtk+-2.0` -c *.c
	cd test; cc -ggdb -Wall -lm matrix.c -o matrix.o \
		../code/matrix.o \
		../code/clann.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm fft.c -o fft.o \
		../code/fft.o \
		../code/matrix.o \
		../code/clann.o \
		../code/statistic.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm lms.c -o lms.o \
		../code/matrix.o \
		../code/clann.o \
		../code/function.o \
		../code/lms.o \
		../code/neuron.o
	cd test; cc -ggdb -Wall -lm rbf.c -o rbf.o \
		../code/rbf.o \
		../code/matrix.o \
		../code/neuron.o \
		../code/function.o \
		../code/clann.o \
		../code/lms.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm svm.c -o svm.o \
		../code/svm.o \
		../code/ilpso.o \
		../code/matrix.o \
		../code/neuron.o \
		../code/function.o \
		../code/clann.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm `pkg-config --cflags --libs gtk+-2.0` \
		gdraw.c -o gdraw.o \
		../code/tree.o \
		../code/graph.o \
		../code/clann.o \
		../code/gdraw.o
	cd test; cc -Wall som.c -lglut -o som.o \
		../code/clann.o \
		../code/som.o \
		../code/matrix.o \
		../code/metric.o \
		../code/reader.o
	cd bind; python setup.py build_ext -f -b clann

clean:
	cd code; rm -rf *.o
	cd test; rm -rf *.o
	cd bind; rm -rf clann/*.so \
		rm -rf build/

