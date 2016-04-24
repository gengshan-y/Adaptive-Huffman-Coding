# A simple makefile for CSE 100 PA2

CC= g++
CXXFLAGS= -std=c++11 -gdwarf-3 -Wall
LDFLAGS= -g

all: compress uncompress

compress: BitInputStream.o BitOutputStream.o AHCNode.o AHCTree.o

uncompress: BitInputStream.o BitOutputStream.o AHCNode.o AHCTree.o

# should use .hpp instead of .o ??
AHCTree.o: BitInputStream.hpp BitOutputStream.hpp AHCNode.hpp AHCTree.hpp

AHCNode.o: AHCNode.hpp

BitOutputStream.o: BitOutputStream.hpp

BitInputStream.o: BitInputStream.hpp

# A core file is created when a program crashed/stoped abnormally.
clean:
	rm -f compress uncompress *.o core*
