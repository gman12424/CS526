/* --------------------------------------------------------------------- *
* A Monte Carlo simulation of the Idiot's Delight problem, as outlined   *
* Exam 1                                                                 *
*                                                                        *
* Name               : idiotsDelight.c                                   *
* Authos             : Geoffrey Ringlee                                  *
* Lanugage           : ANSI C                                            *
* Latest Revision    : 10-17-17                                          *
* Compile with       : gcc idiotsDelight.c rng.c                         *
* ---------------------------------------------------------------------- */

#include <stdio.h>
#include "rngs.h"
#include "rvgs.h"

#define SIZE 52                              /* array size               */
#define N    100000                         /* number of replications   */
  

/* =============== */
    int main(void)
/* =============== */
{
  int i;
  double temp, max;
  max = 2.0;

  SelectStream(0);                       /* for stream to set up random deal */
  for(i = 0; i < N; i++){
    temp = Random();
    if(max > temp)
      max = temp;
  }

printf("%f\n", max);


}
