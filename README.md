# Etude8

Authors: Daniel Prvanov and Nicky Patterson

## Start Up

For the program to work these packages need to be included
```
#include <iostream>
#include <string>
```

The program can be run by typing the following commands into the Studio Visual Code console:
```
g++ main.cpp Integer.cpp Rational.cpp -o main
./main
```
This will do whatever math has been set up in main.

## How The Program Works

The inputted number added is stored in an array, with one number corresponding to one position in the array. If a mathemtical expression is called the entire array is looped through and the expression is called on the entire array, resulting in the correct output.
