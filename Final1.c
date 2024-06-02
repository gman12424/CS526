/* ------------------------------------------------------------------------- 
 * This program is a next-event simulation of a single-server FIFO service
 * node using Exponentially distributed interarrival times and Erlang 
 * distributed service times (i.e., a M/E/1 queue).  The service node is 
 * assumed to be initially idle, no arrivals are permitted after the 
 * terminal time STOP, and the node is then purged by processing any 
 * remaining jobs in the service node.
 *
 * It has been modified to answer problem 1 for Final Exam 2017
 *
 * Name            : Final1.c  (Single Server Queue, version 4)
 * Author          : Geoffrey Ringlee
 * Language        : ANSI C
 * Latest Revision : 12-18-2017
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"                      /* the multi-stream generator */
#include "rvgs.h"                      /* random variate generators  */

#define START         0.0              /* initial time                   */
#define STOP      20000.0              /* terminal (close the door) time */
#define INFINITY   (100.0 * STOP)      /* must be much larger than STOP  */

struct LinkedList{

  double data;
  struct LinkedList *next;

};

typedef struct LinkedList* node;

node createNode(){
//  printf("create node\n");
  node temp;
  temp = (node)malloc(sizeof(struct LinkedList));
//  printf("node created\n");
  temp->next = NULL;
//  printf("next set\n");
  return temp;

}


node addNode(node head, double value){
  node temp,p;
//  printf("adding node\n");
  temp = createNode();
//  printf("adding data\n");
  temp->data = value;
//  printf("data added\n");
  if(head==NULL){
//    printf("head null\n");
    head = temp;
//    printf("head filled\n");
  }else{
//    printf("head filled\n");
    p = head;
    while(p->next != NULL){
      p = p->next;
    }
    p->next = temp;
    }
//  printf("node added\n");
  return head;
}

double getTime(node head){
  double start = head->data;
  return start;
}

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


   double GetArrival()
/* ---------------------------------------------
 * generate the next arrival time, with rate 1/2
 * ---------------------------------------------
 */ 
{
  static double arrival = START;

  SelectStream(0); 
  arrival += Exponential(0.25); //Uses definition 7.3.2 and THeorem 7.3.3
                                // to create a Stationary Poisson Proceses
                                //with Lambda = 4.0
  return (arrival);
}

   double GetService1()
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */ 
{
  SelectStream(2);
  return (Erlang(4, 0.04));
}  

 
   double GetService2()
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */ 
{
  SelectStream(3);
  return (Erlang(6, 0.05));
} 


 
   double GetService3()
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */ 
{
  SelectStream(4);
  return (Erlang(5, 0.1));
} 


 
   double GetService4()
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */ 
{
  SelectStream(5);
  return (Erlang(3, 0.08));
}  

   int main(void)
{
  struct {
    double arrival;                 /* next arrival time                   */
    double completion1;             /* next completion time for first      */
    double completion2;             /* next completion time for second     */
    double completion3;             /* next completion time for third      */
    double completion4;            /* next completion time for fourth node*/
    double current;                 /* current time                        */
    double next;                    /* next (most imminent) event time     */
    double last;                    /* last arrival time                   */
  } t;
  struct {
    double node1;                   /* time integrated number in the node1 */
    double node2;                   /* time integrated number in the node2 */
    double node3;                   /* time integrated number in the node3 */
    double node4;                   /* time integrated number in the node4 */
    double waitTotal;               /* time integrated number in the system*/


    double queue1;                  /* time integrated number in the queue1*/
    double queue2;                  /* time integrated number in the queue2*/
    double queue3;                  /* time integrated number in the queue3*/
    double queue4;                  /* time integrated number in the queue4*/

    double service1;                /* time integrated number in service1  */
    double service2;                /* time integrated number in service2  */ 
    double service3;                /* time integrated number in service3  */
    double service4;                /* time integrated number in service4  */
  } area      = {0.0, 0.0, 0.0};
  long index  = 0;                  /* used to count departed jobs         */
  long indexIn = 0;                 /* used to count number of jobs in     */
  long index1 = 0;
  long index2 = 0;
  long index3 = 0;
  long index4 = 0;
  long number1 = 0;                  /* number in the node                  */
  long number2 = 0;
  long number3 = 0;
  long number4 = 0;
  long number = 0;
  
  node head1 = NULL;
  node head2 = NULL;
  node head3 = NULL;
  node head4 = NULL;
  node temp = NULL;

  PlantSeeds(121212121);
  t.current    = START;           /* set the clock                         */
  t.arrival    = GetArrival();    /* schedule the first arrival            */
  t.completion1 = INFINITY;        /* the first event can't be a completion */
  t.completion2 = INFINITY; 
  t.completion3 = INFINITY;
  t.completion4 = INFINITY;

  while ((t.current < STOP) || (number > 0)) {
    t.next          = Min(t.arrival, t.completion1);  /* next event time   */
    t.next = Min(t.next, t.completion2);
    t.next = Min(t.next, t.completion3);
    t.next = Min(t.next, t.completion4);
    if (number1 > 0)  {                               /* update integrals  */
      area.node1    += (t.next - t.current) * number1;
      area.waitTotal += (t.next - t.current) * number1;
      area.queue1   += (t.next - t.current) * (number1 - 1);
      area.service1 += (t.next - t.current);
    }
    if (number2 > 0){
      area.node2 +=(t.next - t.current) * number2;
      area.waitTotal += (t.next - t.current) * number2;
      area.queue2 += (t.next -t.current) * (number2 - 1);
      area.service2 += (t.next - t.current);
    }
    if (number3 > 0){
      area.node3 += (t.next - t.current) * number3;
      area.waitTotal += (t.next - t.current) * number3;
      area.queue3 += (t.next - t.current) * (number3 - 1);
      area.service3 += (t.next - t.current);
    }
    if (number4 > 0){
      area.node4 += (t.next -t.current) * number4;
      area.waitTotal += (t.next - t.current) * number4;
      area.queue4 += (t.next - t.current) * (number4-1);
      area.service4 += (t.next - t.current);
    }
    t.current       = t.next;                    /* advance the clock */

    if (t.current == t.arrival)  {               /* process an arrival */
//      printf("newarrival\n");
      number1++;
      number++;
      indexIn++;
      head1 = addNode(head1, t.current);
      t.arrival     = GetArrival();
      if (t.arrival > STOP)  {
        t.last      = t.current;
        t.arrival   = INFINITY;
      }
      if (number1 == 1)
        t.completion1 = t.current + GetService1();
    }

    else if (t.current == t.completion1){        /* process a completion */
      index1++;
      number1--;
      if (number1 > 0)
        t.completion1 = t.current + GetService1();
      else
        t.completion1 = INFINITY;
      if(Uniform(0, 1) < 0.6){
        number2++;
        head2 = addNode(head2, getTime(head1));
        if(number2 == 1)
          t.completion2 = t.current + GetService2();
      }else{
        number3++;
        head3 = addNode(head3, getTime(head1));
        if(number3 ==1)
          t.completion3 = t.current + GetService3();
      }
//      printf("exit1\n");
      temp = head1;
      head1 = head1->next;
      free(temp);
    }else if(t.current == t.completion2){
      number2--;
      index2++;
      if(number2 > 0)
        t.completion2 = t.current+GetService2();
      else
        t.completion2 = INFINITY;
      if(Uniform(0,1) < 0.8){
        number4++;
        head4 = addNode(head4, getTime(head2));
        if(number4 == 1)
          t.completion4 = t.current + GetService4();
      }else{
        index++;
        number--;
        printf("%f\n", t.current-getTime(head2));
      }
//      printf("exit2\n");
      temp = head2;
      head2 = head2->next;
      free(temp);
//      printf("exit2\n");
    }else if (t.current == t.completion3){
      number3--;
      index3++;
      if(number3 > 0)
        t.completion3 = t.current+GetService3();
      else
        t.completion3 = INFINITY;
      if(Uniform(0,1) < 0.7){
        number4++;
        head4 = addNode(head4, getTime(head3));
        if(number4 ==1)
          t.completion4 = t.current + GetService4();
      }else{
        index++;
        number--;
        printf("%f\n", t.current-getTime(head3));
      }
//      printf("exit3\n");
      temp = head3;
      head3 = head3->next;
      free(temp);
//      printf("exit3\n");
    }else{    //for completing 4
//      printf("exit4\n");
      number4--;
      number--;
      index4++;
      index++;
      printf("%f\n", t.current-getTime(head4));
      temp = head4;
      head4 = head4->next;
      free(temp);
//      printf("exit4\n");
      if(number4 > 0)
        t.completion4 = t.current+GetService4();
      else
        t.completion4 = INFINITY;
    }
//    printf("Time:  %6.2f  Number: %d\n", t.current, number);
  } 

//  printf("\nfor %ld jobs\n", index);
//  printf("   average interarrival time = %6.2f\n", t.last / index);
//  printf("   averat wait   ............ = %6.2f\n", area.waitTotal/ index);
//  printf("   average wait1 ............ = %6.2f\n", area.node1 / index1);
//  printf("   average wait2 ............ = %6.2f\n", area.node2 / index2);
//  printf("   average wait3 ............ = %6.2f\n", area.node3 / index3);
//  printf("   average wait4 ............ = %6.2f\n", area.node4 / index4);
//  printf("   average delay ........... =  %6.2f\n", area.queue1 / index);
//  printf("   average service time .... = %6.2f\n", area.service1 / index);
//  printf("   average # in the node ... = %6.2f\n", area.node1 / t.current);
//  printf("   average # in the queue1 .. = %6.2f\n", area.queue1 / t.current);
//  printf("   average # in the queue2 .. = %6.2f\n", area.queue2 / t.current);
//  printf("   average # in the queue3 .. = %6.2f\n", area.queue3 / t.current);
//  printf("   average # in the queue4 .. = %6.2f\n", area.queue4 / t.current);
//  printf("   utilization1 ............. = %6.2f\n", area.service1 / t.current);
//  printf("   utilizaiton2 ............. = %6.2f\n", area.service2 / t.current);
//  printf("   utilization3 ............. = %6.2f\n", area.service3 / t.current);
//  printf("   utilization4 ............. = %6.2f\n", area.service4 / t.current);

  return (0);
}
