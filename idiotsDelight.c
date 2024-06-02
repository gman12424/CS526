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

#define SIZE 52                              /* array size               */
#define N    100000                         /* number of replications   */


typedef long permutation[SIZE];






long         wins = 0;                       /* total amount player has won */


/* ============================== */
    long Equilikely(long a, long b)          /* use a<b                  */
/* ============================== */
{
    return(a + (long) ((b - a + 1) * Random()));
}

/* ============================== */
    void Initialize (permutation a, permutation b)
/* ============================== */
{
    int j;
    for(j = 0; j < SIZE; j++){
      a[j] = j;
      b[j] = -1;
    }
}

/* ============================== */
    void Shuffle(permutation a)
/* ============================== */
{
    int j;
    int t;
    int hold;
    
    for(j = 0; j < (SIZE - 1); j++) {          /* shuffle an array         */
      t = Equilikely(j, (SIZE - 1));           /* in such a way that all   */
      hold = a[j];                             /* permutations are equally */
      a[j] = a[t];                             /* likely to occur          */
      a[t] = hold;
    }
}

/* ============================= */
    int getCard(int card)
/* ============================= */
{

   return card % 13;
}

/* ============================= */
    int getSuit(int card)
/* ============================= */
{

   return card/13;
}


/* =============== */
    int main(void)
/* =============== */
{
    long seed = 0;
    PlantSeeds(seed);
    long wins = 0;                              /* total amount of winnings */
    long buyIn = -115;                             /* amount to buy in (neg number) */
    permutation hand;
    permutation arr;
    long play = 0;                              /* winning per play */
    long top = -1;                               /* top of hand */
    long next = 0;                              /* next card in deck */
    int i, j;
    int jackpot = 0;
    int temp;

    int done = 0;
    double p;
    for(i = 0; i < N; i++){                    /* do N Monte Carlo Reps   */

        SelectStream(0);                       /* for stream to set up random deal */
        Initialize (arr, hand);
        Shuffle (arr);
        top = -1;
        next = 0;
        play = buyIn;                           /* all to initialize */
        for(next = 0; next < SIZE; next++){ /*iterate threw deck */
            top++;

              
            hand[top] = arr[next];        /* draw card */
            for(j=0; j < 52; j++){

            }
            if(top>2){                    /* meaning fewer than 4 cards in hand */
              done = 0;
              while(top > 2 && !done ){   //more than 3 cards

                if(getCard(hand[top]) == getCard(hand[top-3])){

                  for(j = 0; j < 4; j++){
                    hand[top] = -1; 
                    top--;
                    play++;
                  }

                }else if(getSuit(hand[top]) == getSuit(hand[top-3])){

                  temp = hand[top];
                  hand[top] = -1;
                  top--;
                  play++;
                  hand[top] = -1;
                  top --;
                  play++;
                  hand[top] = temp;

                }else{
                  done = 1;

                }

              }
           }
       }
       
       if(top <0 ){             /* all cards discarded */

         wins += 10000;
         jackpot++; 
       }else{
         wins += play;
    }
  }
  /* because of the unlikelyhood to come across a perfect play, we factor this
     in here by gaurenteeing it */
  p = ((double) wins) / (double) (N);
  printf("\nfor %d replications, with a buy-in of %li\n", N, buyIn);
  printf("\n and init seed of %li and %i jackpots\n", seed, jackpot);
  printf("the estimated player earnings is %5.3lf\n\n",p);








}
