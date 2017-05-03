CC=g++
CXXFLAGS= -Wall -g -std=c++11

main: main.cpp regexMatcher.cpp parser.cpp tree.cpp
	$(CC) main.cpp $(CXXFLAGS) -o $@ -ldl
