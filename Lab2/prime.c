#include <stdio.h>

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

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(4));  // 11 is a prime.      Should print 0.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}

