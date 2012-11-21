CC=/usr/bin/gcc
CFLAGS=-m32 -Wall -O2
CXX=/usr/bin/g++
CXXFLAGS=-m32 -Wall -O2
LD=/usr/bin/ld

TARGET = starsign.so
OBJ = starsign.o loader.o

all: $(TARGET) starsign-linux

clean:
	rm -f *.o adom-linux-starsign ${TARGET}

starsign-linux: starsign-linux.cc
	$(CXX) ${CXXFLAGS} -o adom-linux-starsign starsign-linux.cc

starsign.so: $(OBJ)
	$(CXX) $(CXXFLAGS) -o ${TARGET} ${OBJ} -ldl -shared

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
