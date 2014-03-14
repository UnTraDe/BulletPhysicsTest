#pragma once
#include <stdlib.h>
#include <glm/glm.hpp>

typedef unsigned char byte;

#define PERM_LENGTH 512
static int Seed = 0;
static byte perm[PERM_LENGTH];

int FastFloor(float x);
float grad1D(int hash, float x);
float grad2D(int hash, float x, float y);
float grad3D(int hash, float x, float y, float z);
int InitSimplex(int seed);
float Generate1D(float x);
float Generate2D(float x, float y);
float Generate3D(float x, float y, float z);
double findnoise2(double x, double y);
double interpolate(double a, double b, double x);
double noise(double x, double y);