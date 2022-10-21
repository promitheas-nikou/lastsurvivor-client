#pragma once
#define _USE_MATH_DEFINES
#include <math.h>


int util_floor(float f);

bool util_rect_includes_point(float x1, float y1, float x2, float y2, float x, float y);

long long int util_floor(double f);

int util_ceil(float f);

long long int util_ceil(double f);

int positive_modulo(int i, int n);