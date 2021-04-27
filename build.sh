#!/bin/bash

clear
cd bin

echo "Building the enviroment..."
echo

g++ -c ../src/*.cpp -I ../External/SFML/include
g++ *.o -o main.exe -L ../External/SFML/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system # to link.

./main.exe 

cd ..
ls src
