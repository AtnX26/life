#include <stdio.h>
#include <stdlib.h>
struct qw{
  int *oo;
};

int main() {
  struct qw *po;
  po->oo = (int *) malloc(sizeof(int)*6);
  int kk[6] = {1,2,3,4,5,6};
  po->oo[0] = kk[0];
  //int zx[6] = {0,0,0,0,0,0};
  //zx[1] = po->oo[0];
  printf("%d", po->oo[0]);
  return 0;
}
