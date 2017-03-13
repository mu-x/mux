#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <time.h>

typedef float massiv[53];
typedef struct tm* time_p;

float opros(int kanal);
void  uprav(int kanal,float upr,massiv wspom );
float initdat(void);
void  izmer7(int j);
void  randd(float * dxx,float * rr);
float gauss(float a,float b);



