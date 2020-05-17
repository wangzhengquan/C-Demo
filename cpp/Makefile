ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	usestock1 usetime3 usebrass2 vegnews stdmove typecast

all:	$(PROGS)

# class
usestock1: usestock1.c stock10.c

# class: overload member operator
usetime3: usetime3.c mytime3.c mytime3.h

# class inheritance: polymorphic public inheritance
usebrass2: usebrass2.c brass.c brass.h

# class: copy constructor, copy assigment
vegnews:  string1.c string1.h

# class: copy constructors, move constructors, copy assignment operators, and move assignment operators
stdmove: stdmove.c

typecast: typecast.c

clean:
	rm -f $(PROGS) $(TEMPFILES)

include $(ROOT)/Make.common.inc
