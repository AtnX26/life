long cumulative_sum(int N)
{
  long accumulator = 0;

  for (int n = 1; n <= N; n++)
    accumulator = accumulator + n;

  //return 6;
  return accumulator;
}
