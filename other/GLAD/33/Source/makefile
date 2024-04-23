
sourse = src/glad.c
includes = include\

flags = -m64 
flags = -m32

name = output/glad.o
name = output/glad-x32.o

all:
	g++   $(flags) -g3 -Wall -Wextra -c $(sourse) -I$(includes) -o $(name).o
	g++   $(flags32) -g3 -Wall -Wextra -c $(sourse) -I$(includes) -o $(name32).o