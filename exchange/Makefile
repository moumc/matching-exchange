GG = g++
CFLAGS = -g 
CXXFLAGS = -fPIC -O2 -g -Wall -std=c++11

INC = -I./
LIBS := -lpthread -lglog -lconfig++ -ljsoncpp -lnanomsg


TARGET = ex_match

all: ${TARGET}    

SRC = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o,$(SRC) )

${TARGET}: ${OBJS} 
	${GG} ${CXXFLAGS} ${INC} $^ -o $@  ${LIBS} 

%.o: %.cpp
	$(GG) $(CXXFLAGS) ${INC} -c $< -o $@
	
#.PHONE
clean:
	rm *.o;rm ${TARGET}

