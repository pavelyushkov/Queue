#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
extern char* strdup(const char*);
#include <string.h>
#include <readline/readline.h>
#include "queue.h"

void output_queue(Queue* queue){
  Item* item = queue->head;
  for(int j = 0; j < (queue->len); ++j){
    printf("%s  ", item->pass->id);
    item = item->next;
  }
}

Queue* create_queues(int stands, int max_len){
  Queue* queues = (Queue*) malloc(stands * sizeof(Queue));
  for(int i = 0; i < stands; ++i){
    Item* item = NULL;
    queues[i].head = item;
    queues[i].tail = item;
    queues[i].len = 0;
  }
  return queues;
}

void push(Queue* queue, Passanger* pass){
  Item* item = (Item*) malloc(sizeof(Item));
  item->pass = (Passanger*) malloc(sizeof(Passanger));
  item->pass->id = strdup(pass->id);
  item->pass->arrive_time = pass->arrive_time;
  item->pass->service_time = pass->service_time;
  if(queue->head == NULL){
    item->pass->start_service = pass->arrive_time;
    item->next = NULL;
    queue->head = item;
    queue->tail = item;
  }
  else{
    queue->tail->next = item;
    queue->tail = queue->tail->next;
    queue->tail->next = NULL;
  }
  ++queue->len;
}

void pop(Queue* queue){
  Item* item = queue->head;
  queue->head = queue->head->next;
  free(item->pass->id);
  free(item->pass);
  free(item);
  --queue->len;
}
int check_moment(Airport* airport, int moment){
    int pops = 0;
    Item* item;
    for(int i = 0; i < (airport->stands); i++){
      for(int count = 0; count < (airport->queues[i].len); count++){
        item = airport->queues[i].head;
        if((item->pass->start_service + item->pass->service_time) <= moment){
          pop(airport->queues + i);
          pops++;
          if(airport->queues[i].len != 0)
            airport->queues[i].head->pass->start_service = moment;
        }
      }
    }
    return pops;
}

void freeAirport(Airport* airport){
  free(airport->queues);
  free(airport);
}
