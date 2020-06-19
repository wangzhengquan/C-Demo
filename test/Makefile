ROOT=..
LDLIBS+=-Wl,-rpath=$(ROOT)/common

PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	 test_properties_config test_logger

build: $(PROGS)

test_properties_config: test_properties_config.c

clean:
	rm -f $(PROGS) $(TEMPFILES)

include $(ROOT)/Make.common.inc
