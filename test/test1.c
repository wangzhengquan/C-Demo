#include <stdio.h>
#include <string.h>
int test() {
  int i,  n = 10;
  int total = 0;
  for(i = 0; i<n; i++) {
    total += i;
    if(i == 5)
      break;
  }
  printf("%d\n", i);
  return total;
}
int main() {
 	printf("%d\n", test());
}
