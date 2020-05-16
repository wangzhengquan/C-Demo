#
# Makefile for misc library.
#
ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# LIBMISC	= libcommon.a
LIBCOMMON = libcommon.a
OBJS   = common.o

all:	$(LIBCOMMON)

$(LIBCOMMON):	$(OBJS)
	$(AR) rv $(LIBMISC) $?
	$(RANLIB) $(LIBMISC)


clean:
	rm -f *.o a.out core temp.* $(LIBCOMMON)

# include $(ROOT)/Make.libapue.inc
