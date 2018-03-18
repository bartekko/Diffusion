all: diffuse23

diffuse23: diffuse23.cpp
	g++ diffuse23.cpp -o diffuse23 -O2 -std=c++17
