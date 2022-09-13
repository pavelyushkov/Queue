#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
extern char* strdup(const char*);
#include <string.h>
#include <readline/readline.h>
#include "queue.h"

Queue* create_queues(int stands, int max_len){
  Queue* queues = (Queue*) malloc(stands * sizeof(Queue));
  for(int i = 0; i < stands; ++i){
    queues[i].passangers = (Passanger*) malloc(max_len * sizeof(Passanger));
    queues[i].start = 0;
    queues[i].end = 0;
    queues[i].len = 0;
  }
  return queues;
}

void push(Queue* queue, Passanger* pass){
  queue->passangers[queue->end].id = strdup(pass->id);
  queue->passangers[queue->end].arrive_time = pass->arrive_time;
  queue->passangers[queue->end].service_time = pass->service_time;
  if(queue->len == 0)
    queue->passangers[queue->end].start_service = queue->passangers[queue->end].arrive_time;
  queue->end += 1;
  if(queue->end == queue->max_len)
    queue->end = 0;
  queue->len++;
}

void pop(Queue* queue){
  free(queue->passangers[queue->start].id);
  queue->start += 1;
  if(queue->start == queue->max_len)
    queue->start = 0;
  queue->len--;
}

void output_queue(Queue* queue){
  int k = queue->start;
  for(int j = 0; j < (queue->len); ++j){
    printf("%s  ", queue->passangers[k].id);
    ++k;
    if(k == queue->max_len)
      k = 0;
  }
}
int check_moment(Airport* airport, int moment){
    int j, pops = 0;
    for(int i = 0; i < (airport->stands); i++){
      for(int count = 0; count < (airport->queues[i].len); count++){
        j = airport->queues[i].start;
        if((airport->queues[i].passangers[j].start_service + airport->queues[i].passangers[j].service_time) <= moment){
          pop(airport->queues + i);
          pops++;
          if(airport->queues[i].len != 0){
            j++;
            if(j == airport->queues[i].max_len)
              j = 0;
            airport->queues[i].passangers[j].start_service = moment;
          }
        }
      }
    }
    return pops;
}

void freeAirport(Airport* airport){
  for(int i = 0; i < airport->stands; ++i)
    free(airport->queues[i].passangers);
  free(airport->queues);
  free(airport);
}
