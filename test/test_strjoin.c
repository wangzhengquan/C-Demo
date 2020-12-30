#include "usg_common.h"
void test1() {
	char *path = str_join(",", "aaaaa", "bbbb", "c", "d", "eeeeee", NULL	);
	printf("str_join\n%s\n", path);
	free(path);

	path = path_join( "/aaaaa", "/bbbb", "/c/", "d/", "eeeeee", NULL	);
	printf("path_join\n%s\n", path);
	free(path);



	char *strarr[] = {
		"aaaa",
		"bbbbb",
		"ccccc",
		NULL
	};

	path = array_join(strarr, "   ");
	printf("array_join:\n%s\n", path);

	char **arr2;
	int len = str_split(path, BLANK, &arr2);
	printf("str_split\n");
	for(int i = 0; i< len; i++) {
		printf("%d) %s.\n", i, arr2[i]);
		free(arr2[i]);
	}
	free(arr2);
}

void test2() {
  
	char **arr2;
	int len = str_split(" : : ",":", &arr2);
	printf("str_split len=%d\n", len);
	for(int i = 0; i< len; i++) {
		printf("%d) %s\n", i, arr2[i]);
		free(arr2[i]);
	}
	free(arr2);

}

int main() {
  test1();
  test2();
}
