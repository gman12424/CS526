/* -------------------------------------------------------------------------
 * A Monte Carlo simulation of 2.3.2 triangle experiment. 
 * 
 * Name              : triangle.c 
 * Author            : Geoffrey Ringlee
	                	modified from Buffon.c by Steve Park & Dave Geyer 
 * Language          : ANSI C
 * Latest Revision   : 9-24-2017 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "rng.h"

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

    int Triangle (double a, double b, double c)
/* --------------------------------------------
 * determine whether the three sides form a  
 * legal triangle.
 * --------------------------------------------
 */
{
  return (((a + b) > c) && ((b + c) > a) && ((a + c ) > b));
}

  int main(void)
{ 
  long   i;                                /* replication index     */
  long   triangles = 0;                    /* number of triangles   */
  double p;                                /* estimated probability */
  double u, v;                             /* points of division    */
  long   seed;                             /* the initial rng seed  */   
  double a,b,c;				   /* length of each division*/

  PutSeed(2121212);                 /* any negative integer will do      */
  GetSeed(&seed);              /* trap the value of the intial seed */

  for (i = 0; i < N; i++) {           
    do {     
      u     = Random();                                   
      v     = Random();
    } while (u == v);	       /* accept - reject method to ensure  
				* u never is equal to v and thus not
				* into less than three parts        */
      if (u < v){                 /* break up the rod so               */
        a = u;                   /* a = length furthest left section  */
        b = v - u;               /* b = length middle section         */ 
        c = 1 - v;               /* c = length last section           */
      }else{
        a = v;
        b = u - v;
        c = 1-u;
      }
    
  
      if (Triangle(a,b,c)){
        triangles++;
      }
  }

    p = (double) triangles / N;                /* estimate the probability */

  printf("\nbased on %ld replications and a rod of length %5.2f\n", N, R);
  printf("with an initial seed of %ld\n", seed);
  printf("the estimated probability of a triangle is %5.3f\n\n", p);

  return (0);
}
