#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <string.h>
#include "airport.h"


int main(){
  int n = 1, stands, max_len;
  while(n != 0){
    Airport* airport;
    Passanger* array;
    printf("\nEnter number of stands:  ");
    stands = check_integer();
    if(stands == 0)
      break;
    printf("\nEnter max length of one queue:  ");
    max_len = check_integer();
    if(max_len == 0)
      break;
    airport = create_airport(stands, max_len);
    array = input(airport, array);
    n = airport->a_len;
    distribution(airport, array);
    free(array);
    freeAirport(airport);
  }
  printf("\nFinished!\n");
  return 0;
}
