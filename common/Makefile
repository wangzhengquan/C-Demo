#
# Makefile for common library.
#
ROOT=..

PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)
  
LIBCOMMON = libusgcommon.a
DLIBCOMMON = libusgcommon.so

SOURCES := $(wildcard *.c)
OBJS   = $(patsubst %.c, %.o, $(SOURCES)) 

MYLIBS = $(LIBCOMMON)

all: build
 

build: $(MYLIBS)

#static lib
$(LIBCOMMON): $(OBJS)
	$(AR) rv $@ $?
	$(RANLIB) $@

#dynamic lib
$(DLIBCOMMON): $(SOURCES)
	rm -f *.o
	$(CC) -fPIC -shared $(CFLAGS) $^ -o $@ $(LDFLAGS)


#PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

# 使用方式： g++ test1.c  -lcommon
install: $(MYLIBS)
	install -d $(PREFIX)/lib/
	install -m 644 $^ $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install -m 644 include/* $(PREFIX)/include/

clean:
	rm -f $(TEMPFILES)

.PHONY: build clean install
# include $(ROOT)/Make.libapue.inc
