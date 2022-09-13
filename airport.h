#ifndef AIRPORT_H
#define AIRPORT_H

 typedef struct Passanger{
    char* id;
    int arrive_time;
    int service_time;
    int start_service;
  }Passanger;

typedef struct Queue Queue;

typedef struct Airport{
  Queue* queues;
  int stands;
  int a_len;
}Airport;

void output(Airport* airport, int moment);
Airport* create_airport(int stands, int max_len);
Passanger* input(Airport* airport, Passanger* array);
int get_status(Airport* airport, int index);
int get_shortest(Airport* airport);
int empty(Airport* airport);
int check_integer();
int check_input(char* duplicate, int len);
void distribution(Airport* airport, Passanger* array);
void freeAirport(Airport* airport);

#endif //AIRPORT_H
