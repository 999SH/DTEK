#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6


int counter = 0;

void print_number(int a){  
  if (counter >= COLUMNS){
    printf("\n");
    counter = 0;
  }
  printf("%10d ", a);
  counter++;
}


void print_sieves(int n){
    char *arr = (char*) malloc(sizeof(char)*n);
    int i = 2;
    int sqrtn = sqrt((int)n);
    while (i < n){ //fill array
        arr[i] = i;
        i++;
    }
    //choose increment 
    int j = 2;
    int increment;    
    while (j < sqrtn){  //sieve 
        if(arr[j] != 0){
            increment = j;
            while (increment < n){ 
                increment = increment+arr[j];
                if (increment < n){
                  arr[increment] = 0;
                }
            }
        }
        j++;
    }
    for (int y = 2; y < n; y++){
        if(arr[y] != 0){
            print_number(y);
        }
    }
    free (arr);   
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.

int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
