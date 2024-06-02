/* --------------------------------------------------------------------- *
* A Monte Carlo simulation of the Idiot's Delight problem, as outlined   *
* Exam 1                                                                 *
*                                                                        *
* Name               : pick3.c                                   *
* Authos             : Geoffrey Ringlee                                  *
* Lanugage           : ANSI C                                            *
* Latest Revision    : 12/19/2017                                          *
* Compile with       :                          *
* ---------------------------------------------------------------------- */

#include <stdio.h>
#include "rngs.h"


#define N    100000                         /* number of replications   */








long         wins = 0;                       /* total amount player has won */





/* =============== */
    int main(void)
/* =============== */
{
  long seed = 123456789;
  PlantSeeds(seed);
  long X = 365;                              /* total amount of winnings */
  long buyIn = -1;                             /* amount to buy in (neg number) */
  int i, j, day, win, winner, run;
  int jackpot = 80;
  int temp;
  long pick[3];
  long state[3];
  double p;
  for(run = 0; run < N; run++){                    /* do N Monte Carlo Reps   */

    SelectStream(0);
    X = 365;

    for(day = 0; day < 365; day++){ /*iterate through a year*/
      X--;
      win = 0;
      pick[0] = Equilikely(0,9);
      pick[1] = Equilikely(0,9);
      pick[2] = Equilikely(0,9);
      state[0] = Equilikely(0,9);
      state[1] = Equilikely(0,9);
      state[2] = Equilikely(0,9);

      if((pick[0] == state[0] && pick[1] == state[1] && pick[2] == state[2])|| (pick[0]==state[0] && pick[1] == state[2] && pick[2] == state[1])||(pick[0] == state[1] && pick[1] == state[2] && pick[2] == state[0])|| (pick[0] == state[1] && pick[1] == state[0] && pick [2] == state[2]) || (pick[0] == state[2] && pick[1] == state [1] && pick[2] == state[1]) || (pick[2] == state[0] && pick[1] == state[0] && pick[2] == state[1])){
        X+=80;
      }

    }
  
//    printf("%d\n", run);
    printf("%d\n", X); //wins
    if (X > 365){
      winner = 1;
    }else{
      winner = 0;
    }
//    printf("%d\n", winner); //winner
//    printf("the estimated player earnings is %5.3lf\n\n",p);
  }
}


