#
# Makefile for common library.
#
ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LIBCOMMON = libcommon.a
DLIBCOMMON = libcommon.so

OBJS   = common.o

all: $(LIBCOMMON)


#static lib
$(LIBCOMMON):	$(OBJS)
	$(AR) rv $@ $?
	$(RANLIB) $@

#dynamic lib
$(DLIBCOMMON):	$(OBJS)
	$(CC) -fPIC -shared -o $@ $^

clean:
	rm -f *.o a.out core temp.* *.a *.so

# include $(ROOT)/Make.libapue.inc
