#
# Makefile for common library.
#
ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# LIBMISC	= libcommon.a
# LIBCOMMON = libcommon.a
LIBCOMMON = libcommon.so

OBJS   = common.o

all: $(LIBCOMMON)


#static lib
#$(LIBCOMMON):	$(OBJS)
#	$(AR) rv $@ $?
#	$(RANLIB) $@

#dynamic lib
$(LIBCOMMON):	$(OBJS)
	$(CC) -fPIC -shared -o $@ $^

clean:
	rm -f *.o a.out core temp.* $(LIBCOMMON)

# include $(ROOT)/Make.libapue.inc
