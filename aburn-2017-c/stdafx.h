//#define OPENGL_RENDER
//#undef OPENGL_RENDER

#ifdef OPENGL_RENDER
//#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef OPENGL_RENDER
/* If using gl3.h */
/* Ensure we are using opengl's core profile only */
#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>
#endif

#undef main

#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>

#undef min
#undef max

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned char UCHAR;

using namespace vmml;
typedef vector<3, float> vector3f;
typedef vector<3, int> vector3i;
typedef vector<2, int> vector2i;
typedef matrix<4, 4, float> matrix3f;

// Hacky utils
static float GetRandFloat()
{
	return float(rand() % RAND_MAX) / float(RAND_MAX);
}

static float GetRandFloatNeg()
{
	return GetRandFloat() * 2.0f - 1.0f;
}

inline static float Sqr(float x)
{
	return x*x;
}
