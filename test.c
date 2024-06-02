/* --------------------------------------------------------------------- *
* A Monte Carlo simulation of the Test problem, as outlined              *
* Exam 1 problem 2                                                       *
*                                                                        *
* Name               : test.c                                            *
* Authos             : Geoffrey Ringlee                                  *
* Lanugage           : ANSI C                                            *
* Latest Revision    : 10-17-17                                          *
* Compile with       : gcc test.c rng.c                                  *
* ---------------------------------------------------------------------- */

#include <stdio.h>
#include "rngs.h"

#define N    100000                         /* number of replications   */
#define SIZE 120
#define numClass1 90

typedef int bank[SIZE];

/* ============================== */
    long Uniform(double a, double b)          /* use a<b                  */
/* ============================== */
{
    return (a + (b-a) * Random());
}

/* ============================== */
    long Equilikely(long a, long b)          /* use a<b                  */
/* ============================== */
{
    return (a + (long) ((b - a + 1) * Random()));
}

/* ============================= */
    int getOne()
/* ============================= */
{
   SelectStream(1);
   double seed = Random();  //returns in distribution A .6 of the time
   if(seed < 0.6){
     return 4;
   }else if (seed < 0.9){         // B on .3 of the time
     return 3;
   }else{
     return 2;                    //and C .1 of the time.
   }
}


/* ============================= */
    int getTwo()
/* ============================= */
{
   SelectStream(2);
   double seed = Random();  //returns in distribution B .1 of the time
   if(seed < 0.1){
     return 3;
   }else if (seed < 0.5){         // C on .4 of the time
     return 2;
   }else if (seed < 0.9){         // D on .4 of the time
     return 1;
   }else{
     return 0;                    //and F .1 of the time.
   }
}

/* ========================= */
    void Initialize(bank a)
/* ========================= */
{

    int j;
    for(j = 0; j < SIZE; j++){
      a[j] = 2;
    }
    for(j = 0; j < numClass1; j++){
      a[j] = 1;
    }
}

/* ==================== */
   void Shuffle(bank a)               /* used because it nicely creats a */
/* ===================== */           /* random order of 90 class1 and 50 */
{                                     /* class2 problems without replacement */
  int j;
  int t;
  int hold;
  
  SelectStream(0);
  for(j = 0; j < (SIZE -1); j++) {
    t = Equilikely(j, SIZE -1);
    hold = a[j];
    a[j] = a[t];
    a[t] = hold;
  }
}

/* =============== */
    int main(void)
/* =============== */
{
    long seed = 98765432;
    PlantSeeds(seed);
    int i, j, index, score;                           /* index is point question drawn from, score the score for that test run */
    bank testBank;
    long scores[49];
    for(i = 0; i < 49; i++){
      scores[i] = 0;  
    }
    for(i = 0; i < N; i++){                    /* do N Monte Carlo Reps   */
        Initialize(testBank);                  /* fill test bank with questions in right concentration */
        Shuffle(testBank);                     /* randomize test bank */
        index = 0;
        score = 0;

        for(j = 0; j < 12; j++){
          
            if(testBank[index] == 1){
              score += getOne(); 
            }else{
              score += getTwo();
            }
            index++;

        }
          scores[score]++;
        printf("%i\n", score);
    }

}
