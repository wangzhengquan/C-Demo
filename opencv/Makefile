#
# Makefile for common library.
#
ROOT=..
#LDLIBS+=-Wl,-rpath=$(ROOT)/common:$(ROOT)/lib/jsoncpp
# 开源工具包路径
#LDDIR += -L$(ROOT)/lib/jsoncpp -L$(ROOT)/lib/nng

# 开源工具包
LDLIBS += -ljsoncpp  -lnng  -lpthread

#INCLUDE += -I$(ROOT)/device/include

PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

 
PROGS = 


build: $(PROGS)


 

clean:
	rm -f $(TEMPFILES) $(PROGS)


include $(ROOT)/Make.common.inc
