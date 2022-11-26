TARGET = librx_utils.so
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CPPFLAGS+= -g  -shared -Wall -fPIC -finline-functions -fexceptions -std=c++11 -I ./ -I /usr/local/include
LDFLAGS+=

all: ${OBJECTS}
	echo ${OBJECTS}
	g++ ${OBJECTS} -o ../lib/${TARGET} $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f ${OBJECTS} ../lib/${TARGET}
