#include <stdio.h>

int is_prime(int n){
  int *i;
  i = &n;
  printf("%p is the adress of i\n",&i);
  printf("%p is the adress in i\n",i);
  printf("%p is the adress of n\n",&n);
  printf("%d is the value of i\n",*i);
  return 0;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  //printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  //printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
