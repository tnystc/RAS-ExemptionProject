# RAS-ExemptionProject
This is an exemption project for IEEE RAS Team. 

## Outline
A C program that displays a number of colored circles, each connected to each other with a solid line and each rotating around the previous circle such that the visualization results in a chaotic structure that resembles a multi-arm pendulum. Circles’ data are held in a linked list. User can add and remove circles.

### Important Note
Due to some technical issues on my local computer, I was unable to add find_package or FetchContent functions to my CMake configuration. This means you need to manually add your local Raylib path in the CMakeLists.txt file for the program to work.

## Prerequisites
- CMake (version 3.11 or higher)
- A C compiler like GCC or MinGW
- Raylib

## Usage

### 
```bash
mkdir build
cd build
cmake ..
make
./RotatingCircles
