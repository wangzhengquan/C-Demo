#include "usg_common.h"

#ifdef __cplusplus
#include <atomic>
using namespace std;
#else
#include <stdatomic.h>
#endif

int main() {
	int a = 0;
	int b = 1;

	atomic_compare_exchange_strong((std::atomic<int>*)&a, &b, 1);

	printf("a=%d\n", a);
}