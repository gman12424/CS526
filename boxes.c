/* -------------------------------------------------------------------------
 * A Monte Carlo simulation of the Boxes experiment from problem 2.3.8. 
 * 
 * Name              : boxes.c
 * Author            : Geoffrey Ringlee
			modified from Buffon.c by Steve Park & Dave Geyer 
 * Language          : ANSI C
 * Latest Revision   : 9-29-17 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "rngs.h"

#define N       10000L                     /* number of replications */
#define HALF_PI (2.0 * atan(1.0))          /* 1.5707963...           */
#define R       1.0                        /* length of the needle   */


   double Uniform(double a, double b)      
/* --------------------------------------------
 * generate a Uniform random variate, use a < b 
 * --------------------------------------------
 */
{
  return (a + (b - a) * Random());
}

long Equilikely(long a, long b) /* use a < b */{
  return (a + (long) ((b-a+1) * Random()));
}
  int main(void)
{ 
  long   i;                                /* replication index     */
  long   pick;                             /* placeholder for pick of number*/
  long   tens = 0;                      /* number of first tens drawn     */
  long   pairs = 0;                        /* number of second tens drawn */
  double p;                                /* estimated probability */
  long   seed;                             /* the initial rng seed  */   
  PlantSeeds(21212);                 /* any negative integer will do      */
  GetSeed(&seed);              /* trap the value of the intial seed */

  //for (i = 0; i < N; i++) {                
    while( tens < N){
    /* 0 = feed for picking box*/
    /* 1 = feed for picking first compartment */
    SelectStream(0);
    pick = Equilikely(1, 3);
    if (pick == 1){ /* first box, two $10 bills, gaurenteed tens and pairs*/
      tens++;
      pairs++;
    }else if(pick == 3){ /*third box, one $10 and one $5*/
      SelectStream(1);
      pick = Equilikely(1,2);
      if (pick == 2){ /*$10 bill drawn first*/
	tens++;
      }
    } /* $5 bill */
    i++;
  }

  p = (double) pairs / tens;                /* estimate the probability */

  printf("\nbased on %ld replications and a total number of  %ld $10 bills drawn first\n", i, tens);
  printf("with an initial seed of %ld\n", seed);
  printf("the estimated probability of a $10 bill being drawn after a $10 bill was drawn from the other compartment is %5.3f\n\n", p);

  return (0);
}
