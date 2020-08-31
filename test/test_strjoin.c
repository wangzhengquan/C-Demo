#include "usg_common.h"
int main() {
	char *path = str_join(",", 5, "aaaaa", "bbbb", "c", "d", "eeeeee" 	);
	printf("%s\n", path);
	free(path);

	path = path_join(5, "/aaaaa", "/bbbb", "/c/", "d/", "eeeeee"	);
	printf("%s\n", path);
	free(path);
}