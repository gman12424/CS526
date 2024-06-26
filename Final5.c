/* ------------------------------------------------------------------------- 
 * This program is a next-event simulation of a single-server FIFO service
 * node using Exponentially distributed interarrival times and Erlang 
 * distributed service times (i.e., a M/E/1 queue).  The service node is 
 * assumed to be initially idle, no arrivals are permitted after the 
 * terminal time STOP, and the node is then purged by processing any 
 * remaining jobs in the service node.
 *
 * Name            : Final5.c  (Single Server Queue, version 4)
 * Author          : Geoffrey Ringlee
 * Language        : ANSI C
 * Latest Revision : 12-19-2017
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "rngs.h"                      /* the multi-stream generator */
#include "rvgs.h"                      /* random variate generators  */

#define START         0.0              /* initial time                   */
#define STOP      200.0              /* terminal (close the door) time */
#define INFINITY   (100.0 * STOP)      /* must be much larger than STOP  */


   double Min(double a, double c)
/* ------------------------------
 * return the smaller of a, b
 * ------------------------------
 */
{ 
  if (a < c)
    return (a);
  else
    return (c);
} 


   double GetArrival(double time)
/* ---------------------------------------------
 * generate the next arrival time, with rate 1/2
 * ---------------------------------------------
 */ 
{
  static double arrival = START;  //arlgorithm generated based on 7.5.4 along with definition 7.3.2 and Theorem 7.3.3

  SelectStream(0); 
  if(time <=200)
    arrival += Exponential(2.0);
  else if(time <= 600)
    arrival += Exponential(1.0/(.5+0.001*(time-200)));
  else if (time <= 1000)
    arrival += Exponential(1.0/9);
  else if (time <= 1200)
    arrival += Exponential(1.0/(0.9+0.0015*(time-1000)));
  else if (time <= 1500)
    arrival += Exponential(1.0/(1.2 - 0.001*(time - 1200)));
  else
    arrival += Exponential(1.0/(0.9 - 0.0008 * (time - 1500)));
  return (arrival);
} 


   double GetService()
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */ 
{
  SelectStream(1);
  return (Erlang(4, 0.25));
}  


   int sim(void)
{
  struct {
    double arrival;                 /* next arrival time                   */
    double completion;              /* next completion time                */
    double current;                 /* current time                        */
    double next;                    /* next (most imminent) event time     */
    double last;                    /* last arrival time                   */
  } t;
  struct {
    double node;                    /* time integrated number in the node  */
    double queue;                   /* time integrated number in the queue */
    double service;                 /* time integrated number in service   */
  } area      = {0.0, 0.0, 0.0};

long index = 0;
long number = 0;
//PlantSeeds(0);



//  PlantSeeds(0);
  t.current    = START;           /* set the clock                         */
  t.arrival    = GetArrival(t.current);    /* schedule the first arrival            */
  t.completion = INFINITY;        /* the first event can't be a completion */
  



//int run;
//for (run = 0; run < 64; run ++){

  while ((t.arrival < STOP) || (number > 0)) {
    t.next          = Min(t.arrival, t.completion);  /* next event time   */
    if (number > 0)  {                               /* update integrals  */
      area.node    += (t.next - t.current) * number;
      area.queue   += (t.next - t.current) * (number - 1);
      area.service += (t.next - t.current);
    }
    t.current       = t.next;                    /* advance the clock */

    if (t.current == t.arrival)  {               /* process an arrival */
      number++;
      t.arrival     = GetArrival(t.current);
      if (t.arrival > STOP)  {
        t.last      = t.current;
        t.arrival   = INFINITY;
      }
      if (number == 1)
        t.completion = t.current + GetService();
    }

    else {                                        /* process a completion */
      index++;
      number--;
      if (number > 0)
        t.completion = t.current + GetService();
      else
        t.completion = INFINITY;
    }
  } 
//  printf("\n run %d\n", run);
  printf("\nfor %ld jobs\n", index);
  printf("   average interarrival time = %6.2f\n", t.last / index);
  printf("   average wait ............ = %6.2f\n", area.node / index);
  printf("   average delay ........... = %6.2f\n", area.queue / index);
  printf("   average service time .... = %6.2f\n", area.service / index);
  printf("   average # in the node ... = %6.2f\n", area.node / t.current);
  printf("   average # in the queue .. = %6.2f\n", area.queue / t.current);
  printf("   utilization ............. = %6.2f\n", area.service / t.current);
//  area.node = 0.0;
//  area.queue = 0.0;
//  area.service = 0.0;
//  index = 0;
//  number = 0;
  

  return (0);
}

int main(void){
  int run;
  PlantSeeds(0);
  for (run = 0; run < 64; run++){
    printf("\nrun: %d\n", run);
    sim();
}
}
