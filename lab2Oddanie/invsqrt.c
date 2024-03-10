#include <math.h>
#include <stdint.h>
//
float reverse_sqrtf(float number){
    float result = 1 / sqrtf(number);
    return result;
}

//source https://en.wikipedia.org/wiki/Fast_inverse_square_root
float q_rsqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration

  return y;
}
