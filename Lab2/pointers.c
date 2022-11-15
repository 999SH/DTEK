#include <stdio.h>

char *text1 = "This is a string.";
char *text2 = "Yet another thing.";

int *list1[20]; // 80 bytes = 20 ints
int *list2[20]; //

int count = 0; // counter declared here

void printlist(const int *lst)
{
  printf("ASCII codes and corresponding characters.\n");
  while (*lst != 0)
  {
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char *c)
{
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c, (int)*(c + 1), (int)*(c + 2), (int)*(c + 3));
}

void copycodes(char *text, int *list, int *count)
{
  while (*text != NULL)
  {
    *list = *text; // load byte from text(dereference), then store word (dereference) into list
    text = text + 1; // Increment adress by 1 byte due to char size
    list = list + 1; // Increment adress by 4 bytes due to int size
    *count = *count + 1; // lw(dereference), increment counter by 1, sw(dereference)
  }
}

void work()
{
  copycodes(text1, list1, &count); // JAL copycodes
  copycodes(text2, list2, &count); // JAL copycodes
}

int main(void)
{
  work();
  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char *)&count);
}
