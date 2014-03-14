#include "SimplexNoise.h"

int FastFloor(float x)
{
    return (x > 0) ? ((int)x) : (((int)x) - 1);
}

float grad1D(int hash, float x) 
{
    int h = hash & 15;
    float grad = 1.0f + (h & 7);
    if ((h & 8) != 0) grad = -grad;
    return (grad * x);
}

float grad2D(int hash, float x, float y)
{
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) != 0 ? -u : u) + ((h & 2) != 0 ? -2.0f * v : 2.0f * v);
}

float grad3D(int hash, float x, float y, float z)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) != 0 ? -u : u) + ((h & 2) != 0 ? -v : v);
}


int InitSimplex(int seed)
{
    int i;
    Seed = seed;
    srand(Seed);
    
    for (i = 0; i < PERM_LENGTH; i++)
        perm[i] = (byte)((double)(rand() / RAND_MAX) * 255); 
	return 0;
}


float Generate1D(float x)
{
    int i0 = FastFloor(x);
    int i1 = i0 + 1;
    float x0 = x - i0;
    float x1 = x0 - 1.0f;
    float n0, n1;
    float t0 = 1.0f - x0 * x0;
    float t1;

    t0 *= t0;
    n0 = t0 * t0 * grad1D(perm[i0 & 0xff], x0);
    t1 = 1.0f - x1 * x1;
    t1 *= t1;
    n1 = t1 * t1 * grad1D(perm[i1 & 0xff], x1);

    return 0.395f * (n0 + n1);
}

float Generate2D(float x, float y)
{
    const float F2 = 0.366025403f;
    const float G2 = 0.211324865f;

    float n0, n1, n2;

    float s = (x + y) * F2;
    float xs = x + s;
    float ys = y + s;
    int i = FastFloor(xs);
    int j = FastFloor(ys);

    float t = (float)(i + j) * G2;
    float X0 = i - t;
    float Y0 = j - t;
    float x0 = x - X0;
    float y0 = y - Y0;

    float x1;
    float y1;
    float x2;
    float y2;
    int ii;
    int jj;
    float t0;
    float t1;
    float t2;

    int i1, j1;
    if (x0 > y0) { i1 = 1; j1 = 0; }
        else { i1 = 0; j1 = 1; }     

    x1 = x0 - i1 + G2; 
    y1 = y0 - j1 + G2;
    x2 = x0 - 1.0f + 2.0f * G2;
    y2 = y0 - 1.0f + 2.0f * G2;

    ii = i % 256;
    jj = j % 256;

    t0 = 0.5f - x0 * x0 - y0 * y0;
    if (t0 < 0.0f) n0 = 0.0f;
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * grad2D(perm[ii + perm[jj]], x0, y0);
    }

    t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 < 0.0f) n1 = 0.0f;
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * grad2D(perm[ii + i1 + perm[jj + j1]], x1, y1);
    }

    t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t2 < 0.0f) n2 = 0.0f;
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * grad2D(perm[ii + 1 + perm[jj + 1]], x2, y2);
    }

    return 40.0f * (n0 + n1 + n2);
}

float Generate3D(float x, float y, float z)
{
    const float F3 = 1/3.0f;
    const float G3 = 1/6.0f;

    float n0, n1, n2, n3;

    float s = (x + y + z) * F3;
    float xs = x + s;
    float ys = y + s;
    float zs = z + s;
    int i = FastFloor(xs);
    int j = FastFloor(ys);
    int k = FastFloor(zs);

    float t = (float)(i + j + k) * G3;
    float X0 = i - t;
    float Y0 = j - t;
    float Z0 = k - t;
    float x0 = x - X0;
    float y0 = y - Y0;
    float z0 = z - Z0;

    int i1, j1, k1;
    int i2, j2, k2;

    float x1;
    float y1;
    float z1;
    float x2;
    float y2;
    float z2;
    float x3;
    float y3;
    float z3;

    int ii;
    int jj;
    int kk;

    float t0;
    float t1;
    float t2;
    float t3;

    if (x0 >= y0)
    {
        if (y0 >= z0)
        { i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0; }
        else if (x0 >= z0) { i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1; }
        else { i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1; }
    }
    else
    {
        if (y0 < z0) { i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1; }
        else if (x0 < z0) { i1 = 0; j1 = 1; k1 = 0; i2 = 0; j2 = 1; k2 = 1; }
        else { i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0; }
    }

    x1 = x0 - i1 + G3;
    y1 = y0 - j1 + G3;
    z1 = z0 - k1 + G3;
    x2 = x0 - i2 + 2.0f * G3;
    y2 = y0 - j2 + 2.0f * G3;
    z2 = z0 - k2 + 2.0f * G3;
    x3 = x0 - 1.0f + 3.0f * G3;
    y3 = y0 - 1.0f + 3.0f * G3;
    z3 = z0 - 1.0f + 3.0f * G3;

    ii = i % 256;
    jj = j % 256;
    kk = k % 256;

    t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
    if (t0 < 0.0f) n0 = 0.0f;
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * grad3D(perm[ii + perm[jj + perm[kk]]], x0, y0, z0);
    }

    t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
    if (t1 < 0.0f) n1 = 0.0f;
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * grad3D(perm[ii + i1 + perm[jj + j1 + perm[kk + k1]]], x1, y1, z1);
    }

    t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
    if (t2 < 0.0f) n2 = 0.0f;
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * grad3D(perm[ii + i2 + perm[jj + j2 + perm[kk + k2]]], x2, y2, z2);
    }

    t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
    if (t3 < 0.0f) n3 = 0.0f;
    else
    {
        t3 *= t3;
        n3 = t3 * t3 * grad3D(perm[ii + 1 + perm[jj + 1 + perm[kk + 1]]], x3, y3, z3);
    }

    return 32.0f * (n0 + n1 + n2 + n3);
}

double findnoise2(double x, double y)
{
	int n = (int) x + (int) y * 57;
	
	n = (n << 13) ^ n;
	
	int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	
	return 1.0 - ((double) nn / 1073741824.0);
}

double interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1.0 - glm::cos(ft))* 0.5;
	return a*(1.0 - f) + b*f;
}


double noise(double x, double y)
{
	double floorx = (double) ((int) x);//This is kinda a cheap way to floor a double integer.
	double floory = (double) ((int) y);
	double s, t, u, v;//Integer declaration
	s = findnoise2(floorx, floory);
	t = findnoise2(floorx + 1, floory);
	u = findnoise2(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.
	v = findnoise2(floorx + 1, floory + 1);
	double int1 = interpolate(s, t, x - floorx);//Interpolate between the values.
	double int2 = interpolate(u, v, x - floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
	return interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
}
