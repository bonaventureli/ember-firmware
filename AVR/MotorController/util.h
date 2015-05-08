#ifndef util_h
#define util_h

float min3(float x1, float x2, float x3);
float min4(float x1, float x2, float x3, float x4);
void copy_axis_vector(float dst[], const float src[]);

#ifndef EPSILON
#define EPSILON   0.00001         // rounding error for floats
#endif

#ifndef fp_ZERO
#define fp_ZERO(a) (fabs(a) < EPSILON)    // requires math.h to be included in each file used
#endif

#ifndef fp_NOT_ZERO
#define fp_NOT_ZERO(a) (fabs(a) > EPSILON)  // requires math.h to be included in each file used
#endif

#ifndef max
#define max(a,b) \
   ({ __typeof__ (a) termA = (a); \
      __typeof__ (b) termB = (b); \
    termA>termB ? termA:termB; })
#endif

#ifndef min
#define min(a,b) \
   ({ __typeof__ (a) termA = (a); \
      __typeof__ (b) termB = (b); \
      termA<termB ? termA:termB; })
#endif

#define MICROSECONDS_PER_MINUTE ((float)60000000)
#define uSec(a) ((float)(a * MICROSECONDS_PER_MINUTE))

#endif
