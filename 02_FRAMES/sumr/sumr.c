// Compute sum of consecutive integers from 1 to N (inclusive)
// git will track everything else!

#include <stdio.h>

long cumulative_sum(int N);

int main(int argc, char *argv[])
{
  int N;
  long result;

  // Ask for number
  printf("Enter a number:\n");
  scanf("%d", &N);

  // Compute sum of consecutive integers from 1 to that number (inclusive)
  result = cumulative_sum(N);

  // Display result
  printf("The sum from 1 to %d is %ld\n", N, result);

  return 0;
}

long cumulative_sum(int N)
{
  long accumulator = 0;

  if (N == 0)
      accumulator = 0;
  else
      accumulator = N + cumulative_sum(N-1);
  
  return accumulator;
}
