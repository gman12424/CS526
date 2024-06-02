/* ------------------------------------------------------------------------- 
 * A Monte Carlo simulation to confirm pdf of algorithm
 * 
 * Name              : pdf.c 
 * Author            : Geoffrey Ringlee
 * Language          : ANSI C
 * Latest Revision   : 11-6-2017
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include "rng.h"
#include <math.h>

#define N 1000000L                          /* number of replications */



  int main(void)
{
  long   i;                              
  double   x;                               

  PutSeed(123456789);

  for (i = 0; i < N; i++) {
    x = Random(); 
    printf("%f\n", ceil(3.0+2.0*x*x));
  }

  return (0);
}
