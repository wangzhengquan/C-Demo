#include <stdio.h>
#include <string.h>
int main() {
 	int len = strspn("geek for you", "you");
 	printf("%d\n", len);
}
