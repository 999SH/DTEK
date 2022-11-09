#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6


int counter = 0;

int is_prime(int n){
  int i = 2;
  while (i < n){
    if (n%i == 0){
      return 0;
    }
    i++;
  }
  return 1;
}

void print_number(int a){  
  if (counter >= COLUMNS){
    printf("\n");
    counter = 0;
  }
  printf("%10d ", a);
  counter++;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  int i = 2;
  while (i < n){
    if(is_prime(i)){
      print_number(i);
    }
    i++;
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 