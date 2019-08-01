#include <stdio.h>
#include <math.h>
#define HEI 128
#define WID 128

int main(void) {

  int i,n;
  n = HEI * WID;

  for (i=0; i<n; i++) {
    printf("q_I[%d] = I[%d];\n", i, i);
  }

  printf("\n");

  for (i=0; i<n; i++) {
    printf("q_II[%d] = exp(0.0010644 * q_I[%d]);\n", i, i);
  }

  printf("\n");

  for (i=0; i<n; i++) {
    printf("II[%d] = q_II[%d];\n", i, i);
  }

  return 0;

}
