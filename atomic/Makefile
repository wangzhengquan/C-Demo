ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	test_atomic

all: $(PROGS)
 

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.common.inc
