#!/bin/bash

./clear.sh
cd bin

echo "Building the enviroment..."
echo

g++ -c ../src/*.cpp
g++ *.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system # to link.

./main.exe 

cd ..
ls src