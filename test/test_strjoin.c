#include "usg_common.h"
int main() {
	char *path = str_join(",", 5, "aaaaa", "bbbb", "c", "d", "eeeeee" 	);
	printf("%s\n", path);
	free(path);

	path = path_join(5, "/aaaaa", "/bbbb", "/c/", "d/", "eeeeee"	);
	printf("%s\n", path);
	free(path);

	char *strarr[] = {
		"aaaa",
		"bbbbb",
		"ccccc"
	};

	path = str_join2(strarr, 3, "   ");
	printf("%s\n", path);

	char **arr2;
	size_t len = str_split(path, BLANK, &arr2);
	for(int i = 0; i< len; i++) {
		printf("%d)%s.\n", i, arr2[i]);
		free(arr2[i]);
	}
	free(arr2);
}