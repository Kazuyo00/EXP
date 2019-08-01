#include <stdio.h>
#include <math.h>
#define HEI 1
#define WID 128

int main(void) {

  int i,n;
  n = HEI * WID;

  for (i=0; i<n; i++) {
    printf("q_II[i * WID + %d] = exp(0.0010644 * q_I[i * WID + %d]);\n", i, i);
  }

  return 0;

}
