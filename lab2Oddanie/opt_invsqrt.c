#include <math.h>
float optymalized_invsqrt(float number) {
    float sqrt_1 = sqrtf(number);
    float result = 1.0f / sqrt_1;
    return result;
}

