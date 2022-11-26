LIBDIR = .
export LIBDIR

TARGET = main

CPPFLAGS = -g -Wall -fPIC -finline-functions -fexceptions -std=c++11 -I/usr/include -I../utils/
export CPPFLAGS

#LDFLAGS = -L/usr/lib64 -lboost_serialization -lpthread
LDFLAGS = -L/usr/lib64 -lpthread -L../lib/ -lrx_utils
export LDFLAGS

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) 
export OBJECTS

all: ${OBJECTS}
	echo ${OBJECTS}
	g++ ${OBJECTS} -o ${TARGET} $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f ${OBJECTS} ${TARGET}
