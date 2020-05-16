ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	usestock1 usetime3 usebrass2

all:	$(PROGS)

# class
usestock1: usestock1.c stock10.c

# class: overload member operator
usetime3: usetime3.c mytime3.c mytime3.h

# class inheritance: polymorphic public inheritance
usebrass2: usebrass2.c brass.c brass.h

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.common.inc
