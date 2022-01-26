#!/bin/bash

g++ -c Node.cpp -lsfml-system -lsfml-graphics -lsfml-window
g++ main.cpp Node.o -lsfml-system -lsfml-graphics -lsfml-window -o curves.exe
./curves.exe
