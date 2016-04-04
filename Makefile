CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXX=g++

OBJ1 =		main.o

OBJ2 = fks.o 

OBJ3 = test.o

SRC1=  $(OBJ1:.o=.cpp)

SRC2=  $(OBJ2:.o=.cpp)

SRC3=  $(OBJ3:.o=.cpp)

OBJS= $(OBJ1) $(OBJ2) $(OBJ3)

LIBS =   

TARGET =	a.exe

$(TARGET):	$(OBJS)
	$(CXX) $(OBJS) 

all:	$(TARGET)

$(OBJ1): $(SRC1)
	$(CXX) -c  -std=c++11 -x c++ $(SRC1)

$(OBJ2): $(SRC2) fks.h
	$(CXX) -c  -std=c++11 -x c++ $(SRC2)

$(OBJ3): $(SRC3) test.h
	$(CXX) -c  -std=c++11 -x c++ $(SRC3)
	