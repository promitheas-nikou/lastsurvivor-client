#include "MathUtils.h"

int util_floor(float f)
{
    return ((int)f) - (f < 0);
}

long long int util_floor(double f)
{
    return ((long long int)f) - (f < 0);
}

int util_ceil(float f)
{
    return ((int)f) + (f > 0);
}

long long int util_ceil(double f)
{
    return ((long long int)f) + (f > 0);
}
