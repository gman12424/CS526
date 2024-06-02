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

#define N 10000


long         wins = 0;                       /* total amount player has won */


/* ============================== */
    long Equilikely(long a, long b)          /* use a<b                  */
/* ============================== */
{
    return(a + (long) ((b - a + 1) * Random()));
}


    long Integers (long n)
{
    long arr[n*(n-1)];
    long i = 1;
    long j = 0;
    long place = 0;
    long temp;
    SelectStream(0);
    for(i = 1; i < n; i++){
      temp = ((n-i)*2);
      for(j = 0; j < temp; j++){
        arr[place] = i;
        place++;
      }
    }
//    for(i=0; i < n*(n-1); i++){
//      printf("%d ", arr[i]);
//    }
    temp = Equilikely(0, n*(n-1)-1);
//    printf("%ld ", temp);
    return arr[temp];

    

}



/* =============== */
    int main(void)
/* =============== */
{

    PlantSeeds(123456789);
    int k;
    for (k = 0; k < N; k++){
//        Integers(5);
      printf("%ld\n", Integers(11));

    }


  /* because of the unlikelyhood to come across a perfect play, we factor this
     in here by gaurenteeing it */
//  p = ((double) wins) / (double) (N);
//  printf("\nfor %d replications, with a buy-in of %li\n", N, buyIn);
//  printf("\n and init seed of %li and %i jackpots\n", seed, jackpot);
//  printf("the estimated player earnings is %5.3lf\n\n",p);








}
