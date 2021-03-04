#!/bin/bash

cd build
clear

g++ -c ../src/*.cpp
g++ *.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system # to link.

./main.exe 

cd ..
ls src