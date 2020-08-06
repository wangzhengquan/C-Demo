ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LDLIBS+=-Wl,-rpath=${DEST}/lib
# 开源工具包路径
LDDIR += -L${DEST}/lib

# 开源工具包
LDLIBS += -lusgcommon

INCLUDE += -I${DEST}/include

PROGS =	${DEST}/usestock1 ${DEST}/usetime3 ${DEST}/usebrass2 ${DEST}/vegnews ${DEST}/stdmove ${DEST}/typecast

all:	${PROGS}

# class
${DEST}/usestock1: usestock1.c stock10.c

# class: overload member operator
${DEST}/usetime3: usetime3.c mytime3.c mytime3.h

# class inheritance: polymorphic public inheritance
${DEST}/usebrass2: usebrass2.c brass.c brass.h

# class: copy constructor, copy assigment
${DEST}/vegnews:  string1.c string1.h

# class: copy constructors, move constructors, copy assignment operators, and move assignment operators
${DEST}/stdmove: stdmove.c

${DEST}/typecast: typecast.c

clean:
	rm -f $(PROGS) $(TEMPFILES)

${DEST}/%:	%.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

include $(ROOT)/Make.common.inc
