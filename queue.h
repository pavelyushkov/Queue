#ifndef QUEUE_H
#define QUEUE_H

#include "airport.h"

#ifdef LIST

 typedef struct Item {
   Passanger* pass;
   struct Item* next;
 } Item;

  typedef struct Queue {
    Item* head;
    Item* tail;
    int len;
  } Queue;

#else

  typedef struct Queue {
    Passanger* passangers;
    int start;
    int end;
    int len;
    int max_len;
  } Queue;

#endif

Queue* create_queues(int stands, int max_len);
void push(Queue* queue, Passanger* pass);
void pop(Queue* queue);
void output_queue(Queue* queue);
int check_moment(Airport* airport, int moment);

#endif //QUEUE_H
