#!/bin/bash

./clear.sh

g++ -c main.cpp 
g++ main.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system # to link.

./main.exe 


