default: all

all:
	cd code; cc -ggdb -Wall -shared -fPIC `pkg-config --cflags gtk+-2.0` -c *.c
	cd test; cc -ggdb -Wall -lm matrix.c -o matrix \
		../code/matrix.o \
		../code/clann.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm fft.c -o fft \
		../code/fft.o \
		../code/matrix.o \
		../code/clann.o \
		../code/statistic.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm lms.c -o lms \
		../code/matrix.o \
		../code/clann.o \
		../code/function.o \
		../code/lms.o \
		../code/neuron.o
	cd test; cc -ggdb -Wall -lm rbf.c -o rbf \
		../code/rbf.o \
		../code/kmeans.o \
		../code/matrix.o \
		../code/metric.o \
		../code/neuron.o \
		../code/function.o \
		../code/clann.o \
		../code/lms.o \
		../code/reader.o
	cd test; cc -ggdb -Wall -lm svm.c -o svm \
		../code/svm.o \
		../code/ilpso.o \
		../code/matrix.o \
		../code/neuron.o \
		../code/function.o \
		../code/clann.o \
		../code/reader.o
	cd test; cc -Wall som.c -lpthread -lglut -o som \
		../code/clann.o \
		../code/som.o \
		../code/matrix.o \
		../code/metric.o \
		../code/reader.o
	cd bind; python setup.py build_ext -f -b clann

clean:
	cd code; rm -rf *.o
	cd test; rm -rf \
		fft \
		lms \
		matrix \
		rbf \
		svm \
		som
	cd bind; rm -rf clann/*.so \
		rm -rf build/

