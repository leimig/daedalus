# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L/usr/local/lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS =

# the build target executable:
TARGET = daedalus

# src folders
SRC = ./lib/*.cc \
	./src/*.cpp \
	./src/network/*.cpp \
	./src/network/node/*.cpp \

	# ./src/network/protocol/*.cpp

default: all

all: clean $(TARGET) run

$(TARGET): ./src/$(TARGET).cpp
	$(CC) -std=c++11 $(CFLAGS) -o ./bin/$(TARGET) $(SRC) $(LFLAGS) $(LIBS) -O0

run:
	./bin/$(TARGET)

clean:
	$(RM) $(TARGET)