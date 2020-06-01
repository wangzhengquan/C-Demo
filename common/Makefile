#
# Makefile for common library.
#
ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
INCLUDE+=-I./include
include $(ROOT)/Make.defines.$(PLATFORM)

LIBCOMMON = libusgcommon.a
DLIBCOMMON = libusgcommon.so

OBJS   = usg_common.o

all: $(LIBCOMMON)

test: test.c 

#static lib
$(LIBCOMMON):	$(OBJS)
	$(AR) rv $@ $?
	$(RANLIB) $@

#dynamic lib
$(DLIBCOMMON):	$(OBJS)
	$(CC) -fPIC -shared -o $@ $^

#PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

# 使用方式： g++ test1.c  -lcommon
install: $(DLIBCOMMON) $(LIBCOMMON)
	sudo install -d $(PREFIX)/lib/
	sudo install -m 644 $^ $(PREFIX)/lib/
	sudo install -d $(PREFIX)/include/
	sudo install -m 644 include/* $(PREFIX)/include/

clean:
	rm -f *.o a.out core temp.* *.a *.so

# include $(ROOT)/Make.libapue.inc
