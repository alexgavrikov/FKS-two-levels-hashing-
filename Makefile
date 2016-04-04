CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXX=g++

OBJ1 =		main.o

OBJ2 = core_function.o 

OBJ3 = fks.o 

OBJ4 = test.o

SRC1=  $(OBJ1:.o=.cpp)

SRC2=  $(OBJ2:.o=.cpp)

SRC3=  $(OBJ3:.o=.cpp)

SRC4=  $(OBJ4:.o=.cpp)

OBJS= $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

LIBS =   

TARGET =	a.exe

$(TARGET):	$(OBJS)
	$(CXX) $(OBJS) 

all:	$(TARGET)

$(OBJ1): $(SRC1)
	$(CXX) -c  -std=c++11 -x c++ $(SRC1)

$(OBJ2): $(SRC2) core_function.h
	$(CXX) -c  -std=c++11 -x c++ $(SRC2)

$(OBJ3): $(SRC3) fks.h
	$(CXX) -c  -std=c++11 -x c++ $(SRC3)

$(OBJ4): $(SRC4) test.h
	$(CXX) -c  -std=c++11 -x c++ $(SRC4)
	