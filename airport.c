#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
extern char* strdup(const char*);
#include <string.h>
#include "queue.h"
#include <readline/readline.h>

#define DELIM " /"

void output(Airport* airport, int moment){
  printf("\nTime: %d", moment);
  for(int i = 0; i < (airport->stands); i++){
    printf("\nNo %d: ", (i+1));
    output_queue(airport->queues + i);
  }
  printf("\n\n");
}

int check_integer(){
  int q, i, flag = 1, res = 0;
  char* input = NULL;
  while(flag == 1){
   if(input != NULL)
      free(input);
    input = readline("");
    if(input == NULL)
      return 0;
    q = strlen(input);
    for(i = 0; i < q; i++){
      if(!isdigit(input[i])){
        printf("\nWrong input. Try again:   ");
        flag = 1;
        break;
      }
      if(i == (q - 1))
        flag = 0;
    }
  }
  res = atoi(input);
  free(input);
  return res;
}
int check_input(char* duplicate, int len){
  char* word;
  int iteration = 0, slash = 0, space = 1, digit = 0, din_len = 0, len_digit = 0;
  for(int i = 0; i < len; i++){
    if(duplicate[i] == '/')
      slash++;
    else if (isdigit(duplicate[i]) != 0)
      digit++;
    else if(duplicate[i] == ' ')
      space++;
  }
  space *= 2;
  if((space != slash) || ((space == 1) && (slash == 0))){
    printf("\nWrong input. Try again:   ");
    free(duplicate);
    return 0;
  }
  if(digit < 2){
    printf("\nWrong input. Try again:   ");
    free(duplicate);
    return 0;
  }
  word = strtok(duplicate, DELIM);
  din_len += strlen(word);
  while(1){
    if(iteration > 0){
      din_len++;
      word = strtok(NULL, DELIM);
      din_len += strlen(word);
    }
    din_len++;
    word = strtok(NULL, DELIM);
    din_len += strlen(word);
    len_digit = strlen(word);
    for(int k = 0; k < len_digit; k++){
      if(!isdigit(word[k])){
        printf("\nWrong input. Try again:   ");
        free(duplicate);
        return 0;
      }
    }
    din_len++;
    word = strtok(NULL, DELIM);
   din_len += strlen(word);
   len_digit = strlen(word);
   for(int k = 0; k < len_digit; k++){
     if(!isdigit(word[k])){
       printf("\nWrong input. Try again:   ");
       free(duplicate);
       return 0;
     }
   }
   iteration++;
   if(din_len == len){
     free(duplicate);
     return 1;
   }
 }
 free(duplicate);
 return 1;
}
Airport* create_airport(int stands, int max_len){
  Airport* airport = (Airport*) malloc(sizeof(Airport));
  airport->stands = stands;
  airport->queues = create_queues(stands, max_len);
  for(int i = 0; i < stands; ++i)
    airport->queues[i].max_len = max_len;
  return airport;
}
Passanger* input(Airport* airport, Passanger* array){
  int len, correct = 0, din_len, count = 0, at, st, space = 0;
  char* input, *id, *ta, *ts, *duplicate;
  printf("\nEnter information about arriving passangers:    ");
  while(correct != 1){
    input = readline("");
    if(input == NULL){
      return 0;
    }
    len = strlen(input);
    duplicate = strdup(input);
    correct = check_input(duplicate, len);
    if(correct == 0)
      free(input);
  }
  len = strlen(input);
  for(int i = 0; i < len; ++i){
    if(input[i] == ' ')
      ++space;
  }
  array = (Passanger*) malloc((space + 1) * sizeof(Passanger));
  din_len = 0;
  id = strtok(input, DELIM);
  din_len += strlen(id);
  din_len++;
  ta = strtok(NULL, DELIM);
  din_len += strlen(ta);
  din_len++;
  ts = strtok(NULL, DELIM);
  din_len += strlen(ts);
  ++count;
  airport->a_len = 1;
  array[count - 1].id = strdup(id);
  array[count - 1].arrive_time = atoi(ta);
  array[count - 1].service_time = atoi(ts);
  while(din_len != len){
    din_len++;
    id = strtok(NULL, DELIM);
    din_len += strlen(id);
    din_len++;
    ta = strtok(NULL, DELIM);
    din_len += strlen(ta);
    din_len++;
    ts = strtok(NULL, DELIM);
    din_len += strlen(ts);
    ++count;
    airport->a_len++;
    array[count - 1].id = strdup(id);
    array[count - 1].arrive_time = atoi(ta);
    array[count - 1].service_time = atoi(ts);
  }
  for(int i = 0; i < count; ++i){
   for(int j = 0; j < count; ++j){
     if(array[i].arrive_time < array[j].arrive_time){
       id = strdup(array[i].id);
       at = array[i].arrive_time;
       st = array[i].service_time;
       free(array[i].id);
       array[i].id = strdup(array[j].id);
       array[i].arrive_time = array[j].arrive_time;
       array[i].service_time = array[j].service_time;
       free(array[j].id);
       array[j].id = strdup(id);
       array[j].arrive_time = at;
       array[j].service_time = st;
       free(id);
     }
   }
 }
 free(input);
 return array;
}

int get_status(Airport* airport, int index){
 if(airport->queues[index].len == 0)
   return 0;
 else if(airport->queues[index].len == (airport->queues[index].max_len))
   return -1;
 else
   return 1;
} // 0 - пустая, 1 - есть элементы,
int get_shortest(Airport* airport){
  int status, len, index, stands_full = 0, pass = 0, statuses, min_len;
  for(int i = 0; i < (airport->stands); i++){
    statuses = get_status(airport, i);
    if(statuses != -1){
      stands_full = 1;
      break;
    }
  }
  if(stands_full == 0){
    return -1;
  }
  index = 0;
  for(int i = 0; i < (airport->stands); i++){
    status = get_status(airport, i);
    if(status == 0){
      return i;
    }
  }
  min_len = (airport->queues[0].max_len) + 1;
  for(int i = 0; i < (airport->stands); i++){
    len = airport->queues[i].len;
    if((len < min_len) && (get_status(airport, i) == 1)){
      min_len = len;
      index = i;
    }
  }
  return index;
}
int empty(Airport* airport){
  for(int i = 0; i < airport->stands; i++){
    if(get_status(airport, i) != 0)
      return 0;
  }
  return 1;
}// 0 - есть элементы, 1 - все очереди пусты
void distribution(Airport* airport, Passanger* array){
  int moment = 0, change = 0, pass_count = 0, check = 0, index = 0;
  while((empty(airport) != 1) || (pass_count < airport->a_len)){
    check = check_moment(airport, moment);
    for(int c = pass_count; c < airport->a_len; c++){
      change = 0;
      if(array[c].arrive_time == moment){
        index = get_shortest(airport);
        if(index == -1){
          for(int i = pass_count; i < airport->a_len; i++)
            free(array[i].id);
          pass_count = airport->a_len;
          printf("\nAll queues are full!\n");
        }
        else{
          push(airport->queues + index, array + c);
          pass_count++;
          free(array[c].id);
          change++;
          check += change;
        }
      }
    }
    if(check != 0)
      output(airport, moment);
    moment += 1;
  }
  return;
}
