
#include <stdio.h>
#include <stdint.h>

void print_bits(uint64_t n)
{
  int i;
  for(i=63;i>=0;i--) {
    if (n & ((uint64_t) 1 << i))  // if there's a 1 in the current position
      printf("1");
    else 
      printf("0");
    if ((i%8) == 0) printf(" ");
  }
  printf("\n");
}

void print_bits_no_newline(uint64_t n)
{
  int i;
  for(i=63;i>=0;i--) {
    if (n & ((uint64_t) 1 << i))  // if there's a 1 in the current position
      printf("1");
    else 
      printf("0");
    if ((i%8) == 0) printf(" ");
  }
}
