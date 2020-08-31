ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

#LDLIBS+=-Wl,-rpath=${DEST}/lib
# 开源工具包路径
LDDIR += -L${DEST}/lib

# 开源工具包
LDLIBS += -lusgcommon

INCLUDE += -I${DEST}/include -I${DEST}/include/usgcommon

PROGS =	${DEST}/test_strjoin

all:	${PROGS}
 

clean:
	rm -f $(PROGS) $(TEMPFILES)

${DEST}/%:	%.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

include $(ROOT)/Make.common.inc
