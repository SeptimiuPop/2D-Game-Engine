#!/bin/bash

./clear.sh

cd src

g++ -c *.cpp
g++ *.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system # to link.

./main.exe 

cd ..
