#include "usg_common.h"

int main() {
	if(mkdirat_r("/home/wzq/wk/Basic-Common/test/tmp", "a5/b/c/d/", DIR_MODE) != 0) {
		err_msg(errno, "usg_common mkdirr");
	}
	if(mkdir_r("a5/b/c/d/", DIR_MODE) != 0) {
		err_msg(errno, "usg_common mkdirr");
	}
}